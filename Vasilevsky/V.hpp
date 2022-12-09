#ifndef BACHELOR_S_FINAL_QUALIFYING_WORK_V_HPP
#define BACHELOR_S_FINAL_QUALIFYING_WORK_V_HPP


#include "../dependencies/dependencies.hpp"


class V {
public:

    void set_table(std::vector<std::vector<std::pair<size_t, size_t>>> table);
    std::vector<std::vector<size_t>> get_V();

private:

    void search_setOfReachability(std::vector<std::vector<size_t>>& result,
                                          std::vector<size_t>& path,
                                          std::vector<bool>& check);

    void search_recursive_setOfReachability(std::vector<std::vector<size_t>>& result,
                                                    std::vector<size_t>& path,
                                                    std::vector<bool>& check,
                                                    long long depth);

    std::vector<std::vector<std::pair<size_t, size_t>>> table;
};


#endif //BACHELOR_S_FINAL_QUALIFYING_WORK_V_HPP
