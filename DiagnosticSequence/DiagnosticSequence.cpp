#include "DiagnosticSequence.hpp"


void DiagnosticSequence::set_table(std::vector<std::vector<std::pair<size_t, size_t>>> table) {
    this->table = std::move(table);
}

std::vector<size_t> DiagnosticSequence::get_Diagnostic_Sequence() {
    std::vector<std::vector<std::vector<size_t>>> W(1, std::vector<std::vector<size_t>>(1, std::vector<size_t>(table[0].size())));
    for (size_t i = 0; i < table[0].size(); ++i) {
        W[0][0][i] = i;
    }
    std::atomic<long long> result_index = -1;
    std::vector<std::vector<size_t>> result(table.size());

    for (size_t i = 0; i < table.size(); ++i) {

    }

    result_index.store(0);
    return result[result_index.load()];
}

/*
 *  1 2 3 4 5 6 7 8
 *  0(1 2 3 4) 1(5 6 7 8)
 *  0(1 2 3) 1()
 */