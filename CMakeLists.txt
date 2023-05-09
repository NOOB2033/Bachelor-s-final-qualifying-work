cmake_minimum_required(VERSION 3.24)
project(Bachelor_s_final_qualifying_work)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(HEADERS
        dependencies/dependencies.hpp
        FSM/FSM.hpp
        Vasilevsky/V.hpp
        Vasilevsky/W.hpp
        Vasilevsky/Vasilevsky.hpp
        DiagnosticSequence/DiagnosticSequence.hpp
        DiagnosticSequence/Utils.hpp
        )

set(SOURCES
        main.cpp
        Vasilevsky/V.cpp
        Vasilevsky/W.cpp
        Vasilevsky/Vasilevsky.cpp
        DiagnosticSequence/DiagnosticSequence.cpp
        )

add_executable(Bachelor_s_final_qualifying_work ${HEADERS} ${SOURCES})

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(Bachelor_s_final_qualifying_work PUBLIC OpenMP::OpenMP_CXX)
endif()

