#ifndef BACHELOR_S_FINAL_QUALIFYING_WORK_DIAGNOSTICSEQUENCE_HPP
#define BACHELOR_S_FINAL_QUALIFYING_WORK_DIAGNOSTICSEQUENCE_HPP


#include "../dependencies/dependencies.hpp"


class DiagnosticSequence {
public:

    void set_table(std::vector<std::vector<std::pair<size_t, size_t>>> table);

    std::vector<size_t> get_Diagnostic_Sequence();

private:

    std::vector<std::vector<std::pair<size_t, size_t>>> table;
};


#endif //BACHELOR_S_FINAL_QUALIFYING_WORK_DIAGNOSTICSEQUENCE_HPP
