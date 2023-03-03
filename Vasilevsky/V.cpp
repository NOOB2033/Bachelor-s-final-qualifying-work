#include "V.hpp"


void V::set_table(std::vector<std::vector<std::pair<size_t, size_t>>> table) {
    this->table = std::move(table);
}

std::vector<std::vector<size_t>> V::get_V() {
    std::vector<std::vector<size_t>> result;
    std::vector<size_t> path{0};
    std::vector<bool> check(table[0].size(), false);

    search_setOfReachability(result, path, check);

    for (long long depth = 1; std::find(check.begin(), check.end(), false) != std::end(check); ++depth) {
        search_recursive_setOfReachability(result, path, check, depth);
    }
    result.push_back({});
    return result;
}

void V::search_setOfReachability(std::vector<std::vector<size_t>>& result,
                                 std::vector<size_t>& path,
                                 std::vector<bool>& check) {
    size_t state = path.back();
    check[state] = true;
    for (size_t i = 0; i < table.size(); ++i) {
        auto check_state = table[i][state].first;
        if (!check[check_state]) {
            check[check_state] = true;
            std::vector<size_t> to_result;
            for (size_t j = 1; j < path.size(); ++j) {
                for (size_t k = 0; k < table.size(); ++k) {
                    if (path[j] == table[k][path[j - 1]].first) {
                        to_result.push_back(k);
                        break;
                    }
                }
            }
            to_result.push_back(i);
            result.push_back(std::move(to_result));
        }
    }
}

void V::search_recursive_setOfReachability(std::vector<std::vector<size_t>>& result,
                                           std::vector<size_t>& path,
                                           std::vector<bool>& check,
                                           long long depth) {
    if (depth-- == 0) {
        return;
    }
    size_t state = path.back();
    for (size_t i = 0; i < table.size(); ++i) {
        auto check_state = table[i][state].first;
        if (std::find(path.begin(), path.end(), check_state) == std::end(path)) {
            path.push_back(std::move(check_state));
            if (depth == 0) {
                search_setOfReachability(result, path, check);
            } else {
                search_recursive_setOfReachability(result, path, check, depth);
            }
            path.pop_back();
        }
    }
}
