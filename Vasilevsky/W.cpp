#include "W.hpp"


void W::set_table(std::vector<std::vector<std::pair<size_t, size_t>>> table) {
    this->table = std::move(table);
}

std::vector<std::vector<size_t>> W::get_W() {
    /*
     * Создаем вспомогательные множества. W[i] будет хранить множество, которое будет различать i-ое состояние
     * с состояниями i+1...size - 1.
     * result - возвращаемое оптимизированное множество различимости.
     */
    std::vector<std::vector<std::vector<size_t>>> W(12); // 12 - моё количество потоков
    std::vector<std::vector<size_t>> result;

#pragma omp parallel num_threads(12) // 12 - моё количество потоков
    {
#pragma parallel for
        /*
         * Создаем проверяющий вектор check. Если check[i] = true, значит нашли различающее множество
         * state и i - 1 - state состояний.
         * Передаем в функцию вектор который будем заполнять(относительно номера потока),
         * проверяющий массив и состояние.
         */
        for (size_t state = 0; state < table[0].size() - 1; ++state) {
            std::vector<bool> check(table[0].size() - 1 - state, false);
            search_setOfDistinctiveness(W[omp_get_thread_num()], check, state);
        }
    }

    result = optimization_W(W);
    return result;
}

void W::search_setOfDistinctiveness(std::vector<std::vector<size_t>>& result,
                                    std::vector<bool>& check,
                                    size_t state) {
    /*
     * Идем в цикле пока глубина не станет равна N или
     * разделяющее множество состояния не будет равно N - 1 (N это число состояний).
     * Ищем в ширину.
     */
    for (size_t depth = 0; depth < table[0].size() && result.size() < table[0].size() - 1; ++depth) {
        /* Идем в цикле сравнивая со следующими состоянием */
        for (size_t i = state + 1; i < table[0].size(); ++i) {
            /* Если мы не нашли различающее множества для state и i - 1 - state */
            if (!check[i - 1 - state]) {
                /*
                 *  Добавляем пустое множество и идем сравнивать эти 2 состояния
                 *  относительно заданной глубины. Если множество так и останется пустым, удаляем его.
                 */
                result.push_back({});
                compareTwoStates(result, check, state, i, depth);
                if (result.back().size() == 0) {
                    result.pop_back();
                }
            }
        }
    }
}

void W::compareTwoStates(std::vector<std::vector<size_t>>& result,
                         std::vector<bool>& check,
                         size_t first_state,
                         size_t second_state,
                         size_t depth) {
    /*
     * Сравниваем 2 состояния. i - входной символ, second - выходной символ.
     * Если нашли хоть один разный выходной символ, добавляем его в результирующее подмножество
     * для нашей проверяемой пары и ставим true в проверяющем массиве и выходим.
     */
    for (size_t i = 0; i < table.size(); ++i) {
        if (table[i][first_state].second != table[i][second_state].second) {
            result.back().push_back(i);
            check[second_state - 1 - first_state] = true;
            return;
        }
    }
    /* Если дошли до предельной глубины, выходим. */
    if (depth-- == 0) {
        return;
    }
    /*
     * Сравниваем 2 состояния. i - входной символ, first - переходное состояние
     */
    for (size_t i = 0; i < table.size(); ++i) {
        if (table[i][first_state].first != table[i][second_state].first) {
            /*
             * Если нашли разное переходное состояние, то запоминаем входной символ(путь),
             * Запоминаем нынешний размер. Идем рекурсивно сравнивать новые состояния.
             * Если не поменялся размер, который мы запомнили ранее, то удаляем нынешний входной символ из пути.
             */
            result.back().push_back(i);
            size_t last_size = result.back().size();
            compareTwoStates(result, check, table[i][first_state].first, table[i][second_state].first, depth);
            if (last_size == result.back().size()) {
                result.back().pop_back();
            }
        }
    }
}

std::vector<std::vector<size_t>> W::optimization_W(std::vector<std::vector<std::vector<size_t>>>& W) {
    std::set<size_t> one_element;
    std::set<std::vector<size_t>> multiple_elements;
    // Удаляем копии с помощью set-ов
    for (size_t i = 0; i < W.size(); ++i) {
        for (auto&& vec : W[i]) {
            if (vec.size() == 1) {
                one_element.insert(vec[0]);
            } else {
                std::vector<size_t> to_set;
                for (size_t k = 0; k < vec.size(); ++k) {
                    to_set.push_back(vec[k]);
                }
                multiple_elements.insert(std::move(to_set));
            }
        }
    }
    // Заполняем итоговый вектор после удаления всех копий
    std::vector<std::vector<size_t>> result;
    for (auto it : one_element) {
        result.push_back(std::vector(1, std::move(it)));
    }
    for (auto it : multiple_elements) {
        result.push_back(std::move(it));
    }
    return result;
}
