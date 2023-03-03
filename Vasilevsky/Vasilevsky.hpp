#ifndef BACHELOR_S_FINAL_QUALIFYING_WORK_VASILEVSKY_HPP
#define BACHELOR_S_FINAL_QUALIFYING_WORK_VASILEVSKY_HPP


#include "V.hpp"
#include "W.hpp"


class Vasilevsky {
public:

    std::vector<std::vector<size_t>> get_VW(const std::vector<std::vector<size_t>>& V,
                                            const std::vector<std::vector<size_t>>& W);

    std::vector<std::vector<size_t>> get_VIW(const std::vector<std::vector<size_t>>& V,
                                             const std::vector<std::vector<size_t>>& W,
                                             size_t inputs);

    std::vector<std::vector<size_t>> get_T(const std::vector<std::vector<size_t>>& VW,
                                           const std::vector<std::vector<size_t>>& VIW);

private:

    std::vector<std::vector<size_t>> concatenation(const std::vector<std::vector<size_t>>& first,
                                                   const std::vector<std::vector<size_t>>& second);

    std::vector<std::vector<size_t>> optimization(std::vector<std::vector<size_t>>& T);
};


#endif //BACHELOR_S_FINAL_QUALIFYING_WORK_VASILEVSKY_HPP
