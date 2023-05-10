#include "Vasilevsky.hpp"


std::vector<std::vector<size_t>> Vasilevsky::get_VW(const std::vector<std::vector<size_t>>& V,
                                                    const std::vector<std::vector<size_t>>& W) {
    auto result = concatenation(V, W);
    return result;
}

std::vector<std::vector<size_t>> Vasilevsky::get_VIW(const std::vector<std::vector<size_t>>& V,
                                                     const std::vector<std::vector<size_t>>& W,
                                                     size_t inputs) {
    auto copyV = V;
    for (size_t i = 1; i < inputs; ++i) {
        copyV.insert(copyV.end(), V.begin(), V.end());
    }

    for (size_t i = 0; i < inputs; ++i) {
        for (size_t j = i * V.size(); j < (i + 1) * V.size(); ++j) {
            copyV[j].push_back(i);
        }
    }
    auto result = concatenation(copyV, W);
    return result;
}

std::vector<std::vector<size_t>> Vasilevsky::get_T(const std::vector<std::vector<size_t>>& VW,
                                                   const std::vector<std::vector<size_t>>& VIW,
                                                   size_t threadCount = 1) {
    assert(threadCount > 0);
    assert(threadCount <= std::thread::hardware_concurrency());
    auto result = VW;
    result.insert(result.end(), VIW.begin(), VIW.end());
    result = optimization(result, threadCount);
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


std::vector<std::vector<size_t>> Vasilevsky::optimization(std::vector<std::vector<size_t>>& T,
                                                          size_t threadCount) {
    std::vector<std::vector<size_t>> result;
    std::vector<std::vector<size_t>> erase_indexes(12);
    std::sort(T.begin(), T.end(), [](std::vector<size_t>& f, std::vector<size_t>& s) {
        return f[0] < s[0];
    });
    std::vector<size_t> indexes;
    size_t it = 0;
    size_t iv = T[it][0];
    indexes.push_back(it);
    for (++it; it < T.size(); ++it) {
        if (iv != T[it][0]) {
            indexes.push_back(it);
            iv = T[it][0];
        }
    }
    indexes.push_back(it);

#pragma omp parallel for num_threads(threadCount)
    for (size_t i = 0; i < indexes.size() - 1; ++i) {
        std::sort(T.begin() + indexes[i], T.begin() + indexes[i + 1],
                  [](std::vector<size_t>& f, std::vector<size_t>& s) {
                      return f.size() < s.size();
                  });

        for (size_t j = indexes[i]; j < indexes[i + 1] - 1; ++j) {
            for (size_t k = j + 1; k < indexes[i + 1]; ++k) {
                bool equality = true;
                for (size_t e = 0; e < T[j].size(); ++e) {
                    if (T[j][e] != T[k][e]) {
                        equality = false;
                        break;
                    }
                }

                if (equality) {
                    erase_indexes[omp_get_thread_num()].push_back(j);
                    break;
                }
            }
        }
    }

    for (size_t i = 1; i < erase_indexes.size(); ++i) {
        erase_indexes[0].insert(erase_indexes[0].end(), erase_indexes[i].begin(), erase_indexes[i].end());
    }
    if (erase_indexes[0].size() > 0) {
        for (size_t i = 0, erase_counter = 0; i < T.size(); ++i) {
            if (i != erase_indexes[0][erase_counter]) {
                result.push_back(std::move(T[i]));
            } else {
                ++erase_counter;
            }
        }
    }

    return result;
}
