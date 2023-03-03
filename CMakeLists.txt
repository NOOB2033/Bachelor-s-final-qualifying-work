cmake_minimum_required(VERSION 3.24)
project(Bachelor_s_final_qualifying_work)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(Bachelor_s_final_qualifying_work main.cpp
        dependencies/dependencies.hpp
        FSM/FSM.hpp
        Vasilevsky/V.hpp Vasilevsky/V.cpp
        Vasilevsky/W.hpp Vasilevsky/W.cpp
        Vasilevsky/Vasilevsky.hpp Vasilevsky/Vasilevsky.cpp)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
