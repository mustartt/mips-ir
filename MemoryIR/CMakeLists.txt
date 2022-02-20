cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

add_library(memoryir
        Block.h Block.cpp Constant.h Function.h
        Function.cpp Instruction.h Instruction.cpp
        IRbuilder.h IRContext.h IRContext.cpp
        Module.h Module.cpp Value.h)

target_include_directories(memoryir PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(memoryir PROPERTIES LINKER_LANGUAGE CXX)
