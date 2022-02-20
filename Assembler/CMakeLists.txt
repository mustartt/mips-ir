cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

add_library(assembler Assembler.h Assembler.cpp Instruction.cpp Instruction.h)

target_include_directories(assembler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(assembler PROPERTIES LINKER_LANGUAGE CXX)
