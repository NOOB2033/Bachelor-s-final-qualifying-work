#include "Vasilevsky/Vasilevsky.hpp"
#include "FSM/FSM.hpp"


#include <thread>
#include <chrono>


void test() {
    std::ifstream input("5000_1000_1000.fsm");

    auto vec = get_table_from_FSM(input);

    V v;
    v.set_table(vec);

    synchronous::W w;
    w.set_table(vec);

    Vasilevsky vas;

    auto s = std::chrono::high_resolution_clock::now();
    auto first = v.get_V();
    auto e = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> d = e - s;
    std::cout << "Последовательное Множество достижимости: " << std::chrono::duration_cast<std::chrono::microseconds>(d).count()/1000000.0 << " секунд\n";

    s = std::chrono::high_resolution_clock::now();
    auto second = w.get_W();
    e = std::chrono::high_resolution_clock::now();
    d = e - s;
    std::cout << "Параллельное Множество различимости: " << std::chrono::duration_cast<std::chrono::microseconds>(d).count()/1000000.0 << " секунд\n";

    s = std::chrono::high_resolution_clock::now();
    auto third = vas.get_VW(first, second);
    e = std::chrono::high_resolution_clock::now();
    d = e - s;
    std::cout << "Последовательный первый этап: " << std::chrono::duration_cast<std::chrono::microseconds>(d).count()/1000000.0 << " секунд\n";


    s = std::chrono::high_resolution_clock::now();
    auto four = vas.get_VIW(third, second);
    e = std::chrono::high_resolution_clock::now();
    d = e - s;
    std::cout << "Последовательный второй этап: " << std::chrono::duration_cast<std::chrono::microseconds>(d).count()/1000000.0 << " секунд\n";

//    for (auto x : four) {
//        for (auto y : x) {
//            std::cout << y << ' ';
//        }
//        std::cout << std::endl;
//    }
}


int main() {
    srand(time(0));
    test();
}
