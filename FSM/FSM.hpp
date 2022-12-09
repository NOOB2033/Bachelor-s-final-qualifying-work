#ifndef BACHELOR_S_FINAL_QUALIFYING_WORK_FSM_HPP
#define BACHELOR_S_FINAL_QUALIFYING_WORK_FSM_HPP


#include "../dependencies/dependencies.hpp"


std::vector<std::vector<std::pair<size_t, size_t>>> get_table_from_FSM(std::ifstream& file) {
    std::string buffer;

    std::getline(file, buffer);
    std::getline(file, buffer);
    size_t states = std::stoi(buffer.substr(2, buffer.size() - 1));
    std::getline(file, buffer);
    size_t inputs = std::stoi(buffer.substr(2, buffer.size() - 1));
    std::getline(file, buffer);
    std::getline(file, buffer);
    std::getline(file, buffer);

    std::vector<std::vector<std::pair<size_t, size_t>>> table(inputs);

    while (std::getline(file, buffer)) {
        size_t iter = 0;

        std::string str;
        for (; buffer[iter] != ' '; ++iter) {
            str.push_back(buffer[iter]);
        }
        size_t state = std::stoi(str);
        str.clear();
        for (++iter; buffer[iter] != ' '; ++iter) {
            str.push_back(buffer[iter]);
        }
        size_t input = std::stoi(str);
        if (table[input].size() == 0) {
            for (size_t j = 0; j < states; ++j) {
                table[input].push_back({});
            }
        }
        str.clear();
        for (++iter; buffer[iter] != ' '; ++iter) {
            str.push_back(buffer[iter]);
        }
        table[input][state].first = std::stoi(str);
        str.clear();
        for (++iter; buffer[iter] != '\r' && buffer[iter] != '\n'; ++iter) {
            str.push_back(buffer[iter]);
        }
        table[input][state].second = std::stoi(str);
    }

    return table;
}


#endif //BACHELOR_S_FINAL_QUALIFYING_WORK_FSM_HPP
