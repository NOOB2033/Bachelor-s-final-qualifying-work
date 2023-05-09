#include "DiagnosticSequence.hpp"


void DiagnosticSequence::set_data(std::vector<std::vector<std::pair<size_t, size_t>>> table,
                                  size_t output_size) {
    this->table = std::move(table);
    this->output_size = output_size;
}

std::vector<size_t> DiagnosticSequence::get_Diagnostic_Sequence() {
    std::vector<std::vector<size_t>> paths(table.size());
    std::pair<std::atomic<bool>, std::atomic<size_t>> res{false, 0};

    sorted_list<size_t> sets;
    for (size_t i = 0; i < table[0].size(); ++i) {
        sets.push(i);
    }
    std::vector<size_t> result;
#pragma omp parallel for
    for (size_t input = 0; input < paths.size(); ++input) {
        std::vector<std::vector<sorted_list<size_t>>> history(1, std::vector<sorted_list<size_t>>(1, sets));
        std::vector<std::vector<size_t>> indexes(output_size);
        for (auto&& node : sets) {
            const auto& elem = table[input][node];
            indexes[elem.second].push_back(elem.first);
        }
        std::vector<sorted_list<size_t>> new_sets(output_size);
        for (size_t i = 0; i < indexes.size(); ++i) {
            for (size_t j = 0; j < indexes[i].size(); ++j) {
                new_sets[i].push(indexes[i][j]);
            }
        }
        paths[input].push_back(input);
        std::sort(new_sets.begin(), new_sets.end());
        if (recursive_search(paths[input], new_sets, res, history)) {
            result = paths[res.second.load()];
        }
        paths[input].pop_back();
    }

    return result;
}

bool DiagnosticSequence::recursive_search(std::vector<size_t>& path, std::vector<sorted_list<size_t>> sets,
                                          std::pair<std::atomic<bool>, std::atomic<size_t>>& res,
                                          std::vector<std::vector<sorted_list<size_t>>>& history) {
    if (res.first.load()) {
        return res.second.load() == path.front();
    }
    if (std::find(history.begin(), history.end(), sets) != history.end()) {
        return false;
    }
    bool end = true;
    for (auto&& list : sets) {
        if (list.size() != 1) {
            end = false;
            break;
        }
    }
    if (end) {
        res.second.store(path.front());
        res.first.store(true);
        return true;
    }

    if (!is_valid(sets)) {
        return false;
    }
    history.push_back(sets);
    for (size_t i = 0; i < table.size(); ++i) {
        std::vector<sorted_list<size_t>> new_sets;
        for (auto&& list : sets) {
            std::vector<std::vector<size_t>> indexes(output_size);
            for (auto&& node : list) {
                const auto& elem = table[i][node];
                indexes[elem.second].push_back(elem.first);
            }
            std::vector<sorted_list<size_t>> temp_new_sets(output_size);
            for (size_t j = 0; j < indexes.size(); ++j) {
                for (size_t k = 0; k < indexes[j].size(); ++k) {
                    temp_new_sets[j].push(indexes[j][k]);
                }
            }
            for (size_t j = 0; j < temp_new_sets.size(); ++j) {
                if (temp_new_sets[j].size() > 1) {
                    new_sets.push_back(std::move(temp_new_sets[j]));
                }
            }
        }
        std::sort(new_sets.begin(), new_sets.end());
        path.push_back(i);
        if (recursive_search(path, new_sets, res, history)) {
            return true;
        }
        path.pop_back();
    }
    return false;
}

bool DiagnosticSequence::is_valid(std::vector<sorted_list<size_t>> sets) {
    for (auto&& list : sets) {
        auto it1 = list.begin();
        auto it2 = list.begin();
        for (++it2; it2!= list.end(); it1++, it2++) {
            if (*it1 == *it2) {
                return false;
            }
        }
    }
    return true;
}
