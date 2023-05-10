#include "Vasilevsky/Vasilevsky.hpp"
#include "FSM/FSM.hpp"
#include "DiagnosticSequence/DiagnosticSequence.hpp"


void test() {
    std::ofstream output("my.txt");
    auto start = std::chrono::high_resolution_clock::now();
    std::string str = "FSMS/200_100_100.fsm";
    std::ifstream input(str);
    size_t output_size;
    auto table = get_table_from_FSM(input, output_size);

    DiagnosticSequence ds;
    ds.set_data(table, output_size);
    auto res = ds.get_Diagnostic_Sequence(3);
//
//    for (size_t i = 0; i < res.size(); ++i) {
//        std::cout << res[i] << ' ';
//    }

//    V v;
//    v.set_table(table);
//    W w;
//    w.set_table(table);
//    Vasilevsky vas;
//
//    auto s1 = std::chrono::high_resolution_clock::now();
//    auto vv = v.get_V();
//    std::chrono::duration<double> d1;
//    d1 = std::chrono::high_resolution_clock::now() - s1;
//    output << "Множество достижимости: " <<
//    std::chrono::duration_cast<std::chrono::microseconds>(d1).count()/1000000.0 << std::endl;
//
//    auto s2 = std::chrono::high_resolution_clock::now();
//    auto ww = w.get_W();
//    std::chrono::duration<double> d2;
//    d2 = std::chrono::high_resolution_clock::now() - s2;
//    output << "Множество различимости: " <<
//    std::chrono::duration_cast<std::chrono::microseconds>(d2).count() / 1000000.0 << std::endl;
//
//    auto s3 = std::chrono::high_resolution_clock::now();
//    auto vvww = vas.get_VW(vv, ww);
//    std::chrono::duration<double> d3;
//    d3 = std::chrono::high_resolution_clock::now() - s3;
//    output << "Множество VW: " <<
//    std::chrono::duration_cast<std::chrono::milliseconds>(d3).count()/1000.0 << std::endl;
//
//    auto s4 = std::chrono::high_resolution_clock::now();
//    auto vviiww = vas.get_VIW(vv, ww, table.size());
//    std::chrono::duration<double> d4;
//    d4 = std::chrono::high_resolution_clock::now() - s4;
//    output << "Множество VIW: " <<
//    std::chrono::duration_cast<std::chrono::milliseconds>(d4).count()/1000.0 << std::endl;
//
//    auto s5 = std::chrono::high_resolution_clock::now();
//    auto T = vas.get_T(vvww, vviiww);
//    std::chrono::duration<double> d5;
//    d5 = std::chrono::high_resolution_clock::now() - s5;
//    output << "Множество T: " <<
//    std::chrono::duration_cast<std::chrono::milliseconds>(d5).count()/1000.0 << std::endl;
//
//    std::chrono::duration<double> sde;
//    sde = std::chrono::high_resolution_clock::now() - start;
//    output << "Время выполнения всей программы: " <<
//    std::chrono::duration_cast<std::chrono::milliseconds>(sde).count()/1000.0 << std::endl;
//
//    for (auto&& x : T) {
//        for (auto&& y : x) {
//            output << y;
//        }
//        output << std::endl;
//    }
}


int main() {
    test();
}
