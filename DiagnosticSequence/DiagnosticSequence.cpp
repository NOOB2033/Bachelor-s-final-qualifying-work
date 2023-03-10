#include "DiagnosticSequence.hpp"


void DiagnosticSequence::set_table(std::vector<std::vector<std::pair<size_t, size_t>>> table) {
    this->table = std::move(table);
}

std::vector<size_t> DiagnosticSequence::get_Diagnostic_Sequence(const std::vector<size_t>& inputs) {
    
}