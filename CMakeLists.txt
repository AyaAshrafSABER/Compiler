cmake_minimum_required(VERSION 3.13)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(Compiler
    main.cpp Automata/DFA.cpp Automata/DFA.h Automata/MinimizeDFA.cpp Automata/MinimizeDFA.h)
