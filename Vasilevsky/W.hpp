#ifndef BACHELOR_S_FINAL_QUALIFYING_WORK_W_HPP
#define BACHELOR_S_FINAL_QUALIFYING_WORK_W_HPP


#include "../dependencies/dependencies.hpp"


class W {
public:

    void set_table(std::vector<std::vector<std::pair<size_t, size_t>>> table);
    std::vector<std::vector<size_t>> get_W();

private:

    void search_setOfDistinctiveness(std::vector<std::vector<size_t>>& vec,
                                     std::vector<bool>& check,
                                     size_t state);

    void compareTwoStates(std::vector<std::vector<size_t>>& vec,
                          std::vector<bool>& check,
                          size_t first_state,
                          size_t second_state,
                          size_t depth);

    std::vector<std::vector<size_t>> optimization_W(std::vector<std::vector<std::vector<size_t>>>& W);

    std::vector<std::vector<std::pair<size_t, size_t>>> table;
};


#endif //BACHELOR_S_FINAL_QUALIFYING_WORK_W_HPP
