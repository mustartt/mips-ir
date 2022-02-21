cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

add_library(allocation
        InterferenceGraph.cpp InterferenceGraph.h
        LivenessAnalyzer.cpp LivenessAnalyzer.h
        RegisterAllocator.cpp RegisterAllocator.h)

target_include_directories(allocation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(allocation PROPERTIES LINKER_LANGUAGE CXX)
