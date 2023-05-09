#ifndef BACHELOR_S_FINAL_QUALIFYING_WORK_DIAGNOSTICSEQUENCE_HPP
#define BACHELOR_S_FINAL_QUALIFYING_WORK_DIAGNOSTICSEQUENCE_HPP


#include "Utils.hpp"


class DiagnosticSequence {
public:

    void set_data(std::vector<std::vector<std::pair<size_t, size_t>>> table, size_t output_size);

    std::vector<size_t> get_Diagnostic_Sequence();
private:
    bool recursive_search(std::vector<size_t>& path, std::vector<sorted_list<size_t>> sets,
                          std::pair<std::atomic<bool>, std::atomic<size_t>>& res,
                          std::vector<std::vector<sorted_list<size_t>>>& history);

    bool is_valid(std::vector<sorted_list<size_t>> sets);

    size_t output_size = 0;
    std::vector<std::vector<std::pair<size_t, size_t>>> table;
};


#endif //BACHELOR_S_FINAL_QUALIFYING_WORK_DIAGNOSTICSEQUENCE_HPP
