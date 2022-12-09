#include "W.hpp"


namespace synchronous {

void W::set_table(std::vector<std::vector<std::pair<size_t, size_t>>> table) {
    this->table = std::move(table);
}

std::vector<std::vector<size_t>> W::get_W() {
    std::vector<std::vector<std::vector<size_t>>> W;

    auto s = std::chrono::high_resolution_clock::now();
    for (size_t state = 0; state < table[0].size(); ++state) {
        std::vector<std::vector<size_t>> result;
        std::vector<bool> check(table[0].size(), false);
        check[state] = true;
        search_setOfDistinctiveness(result, check, state);
        W.push_back(std::move(result));
    }
    auto e = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> d = e - s;
    std::cout << "Последовательная область: " << std::chrono::duration_cast<std::chrono::microseconds>(d).count()/1000000.0 << " секунд\n";

    std::vector<std::vector<size_t>> result = optimization_W(W);
    return result;
}

void W::search_setOfDistinctiveness(std::vector<std::vector<size_t>>& result,
                                    std::vector<bool>& check,
                                    size_t state) {

    for (size_t depth = 1; result.size() < table[0].size() - 1; ++depth) {
        for (size_t i = 0; i < table[0].size(); ++i) {
            if (!check[i]) {
                result.push_back({});
                compareTwoStates(result, check, state, i, depth);
                if (result.back().size() == 0) {
                    result.pop_back();
                }
            }
        }
    }
}

void W::compareTwoStates(std::vector<std::vector<size_t>>& result,
                         std::vector<bool>& check,
                         size_t first_state,
                         size_t second_state,
                         size_t depth) {
    for (size_t i = 0; i < table.size(); ++i) {
        if (table[i][first_state].second != table[i][second_state].second) {
            result.back().push_back(i);
            check[second_state] = true;
            return;
        }
    }
    if (--depth == 0) {
        return;
    }
    for (size_t i = 0; i < table.size(); ++i) {
        if (table[i][first_state].first != table[i][second_state].first) {
            result.back().push_back(i);
            size_t last_size = result.back().size();
            compareTwoStates(result, check, table[i][first_state].first, table[i][second_state].first, depth);
            if (last_size == result.back().size()) {
                result.back().pop_back();
            }
        }
    }
}

std::vector<std::vector<size_t>> W::optimization_W(std::vector<std::vector<std::vector<size_t>>>& W) {
    std::set<size_t> one_element;
    std::set<std::vector<size_t>> multiple_elements;

    for (size_t i = 0; i < W.size(); ++i) {
        for (size_t j = 0; j < W[i].size(); ++j) {
            if (W[i][j].size() == 1) {
                one_element.insert(W[i][j][0]);
            } else {
                std::vector<size_t> to_set;
                for (size_t k = 0; k < W[i][j].size(); ++k) {
                    to_set.push_back(W[i][j][k]);
                }
                multiple_elements.insert(std::move(to_set));
            }
        }
    }

    std::vector<std::vector<size_t>> result;
    for (auto it : one_element) {
        result.push_back(std::vector(1, std::move(it)));
    }
    for (auto it : multiple_elements) {
        result.push_back(std::move(it));
    }
    return result;
}

}


namespace parallel {

void W::set_table(std::vector<std::vector<std::pair<size_t, size_t>>> table) {
    this->table = std::move(table);
}

std::vector<std::vector<size_t>> W::get_W() {
    std::vector<std::vector<std::vector<size_t>>> W;

        auto s = std::chrono::high_resolution_clock::now();
#pragma omp parallel for
    {
        for (size_t state = 0; state < table[0].size(); ++state) {
            std::vector<std::vector<size_t>> result;
            std::vector<bool> check(table[0].size(), false);
            check[state] = true;
            search_setOfDistinctiveness(result, check, state);
#pragma omp critical
            {
                W.push_back(std::move(result));
            }
        }
    }
    auto e = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> d = e - s;
    std::cout << "Параллельная область: " << std::chrono::duration_cast<std::chrono::microseconds>(d).count()/1000000.0 << " секунд\n";

    std::vector<std::vector<size_t>> result = optimization_W(W);
    return result;
}

void W::search_setOfDistinctiveness(std::vector<std::vector<size_t>>& result,
                                    std::vector<bool>& check,
                                    size_t state) {

    for (size_t depth = 1; depth < table[0].size() && result.size() < table[0].size() - 1; ++depth) {
        for (size_t i = 0; i < table[0].size(); ++i) {
            if (!check[i]) {
                result.push_back({});
                compareTwoStates(result, check, state, i, depth);
                if (result.back().size() == 0) {
                    result.pop_back();
                }
            }
        }
    }
}

void W::compareTwoStates(std::vector<std::vector<size_t>>& result,
                         std::vector<bool>& check,
                         size_t first_state,
                         size_t second_state,
                         size_t depth) {
    for (size_t i = 0; i < table.size(); ++i) {
        if (table[i][first_state].second != table[i][second_state].second) {
            result.back().push_back(i);
            check[second_state] = true;
            return;
        }
    }
    if (--depth == 0) {
        return;
    }
    for (size_t i = 0; i < table.size(); ++i) {
        if (table[i][first_state].first != table[i][second_state].first) {
            result.back().push_back(i);
            size_t last_size = result.back().size();
            compareTwoStates(result, check, table[i][first_state].first, table[i][second_state].first, depth);
            if (last_size == result.back().size()) {
                result.back().pop_back();
            }
        }
    }
}

std::vector<std::vector<size_t>> W::optimization_W(std::vector<std::vector<std::vector<size_t>>>& W) {
    std::set<size_t> one_element;
    std::set<std::vector<size_t>> multiple_elements;

    for (size_t i = 0; i < W.size(); ++i) {
        for (size_t j = 0; j < W[i].size(); ++j) {
            if (W[i][j].size() == 1) {
                one_element.insert(W[i][j][0]);
            } else {
                std::vector<size_t> to_set;
                for (size_t k = 0; k < W[i][j].size(); ++k) {
                    to_set.push_back(W[i][j][k]);
                }
                multiple_elements.insert(std::move(to_set));
            }
        }
    }

    std::vector<std::vector<size_t>> result;
    for (auto it: one_element) {
        result.push_back(std::vector(1, std::move(it)));
    }
    for (auto it: multiple_elements) {
        result.push_back(std::move(it));
    }
    return result;
}

}