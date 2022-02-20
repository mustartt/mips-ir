cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

add_library(registeralloc
        InterferenceGraph.cpp InterferenceGraph.h LivenessAnalyzer.cpp LivenessAnalyzer.h)

target_include_directories(registeralloc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(registeralloc PROPERTIES LINKER_LANGUAGE CXX)
