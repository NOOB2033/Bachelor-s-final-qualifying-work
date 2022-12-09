#include "Vasilevsky.hpp"


std::vector<std::vector<size_t>> Vasilevsky::get_VW(const std::vector<std::vector<size_t>>& V,
                                                    const std::vector<std::vector<size_t>>& W) {
    auto result = concatenation(V, W);
    return result;
}

std::vector<std::vector<size_t>> Vasilevsky::get_VIW(const std::vector<std::vector<size_t>>& VW,
                                                     const std::vector<std::vector<size_t>>& W) {
    auto result = concatenation(VW, W);
    result = optimization(result);
    return result;
}

std::vector<std::vector<size_t>> Vasilevsky::concatenation(const std::vector<std::vector<size_t>>& first,
                                                           const std::vector<std::vector<size_t>>& second) {
    std::vector<std::vector<size_t>> result;

    for (size_t i = 0; i < first.size(); ++i) {
        for (size_t j = 0; j < second.size(); ++j) {
            std::vector<size_t> to_result;
            for (size_t k = 0; k < first[i].size(); ++k) {
                to_result.push_back(first[i][k]);
            }
            for (size_t k = 0; k < second[j].size(); ++k) {
                to_result.push_back(second[j][k]);
            }
            result.push_back(std::move(to_result));
        }
    }

    return result;
}

std::vector<std::vector<size_t>> Vasilevsky::optimization(std::vector<std::vector<size_t>>& T) {
    std::vector<std::vector<size_t>> result;
    std::vector<size_t> erase_indexes;

    for (size_t i = 0; i < T.size() - 1; ++i) {
        for (size_t j = i + 1; j < T.size(); ++j) {
            bool equality = true;
            for (size_t k = 0; k < T[i].size(); ++k) {
                if (T[i][k] != T[j][k]) {
                    equality = false;
                    break;
                }
            }
            if (equality) {
                erase_indexes.push_back(i);
                break;
            }
        }
    }

    for (size_t i = 0, erase_counter = 0; i < T.size(); ++i) {
        if (i != erase_indexes[erase_counter]) {
            result.push_back(std::move(T[i]));
        } else {
            ++erase_counter;
        }
    }
    return result;
}
