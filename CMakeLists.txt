cmake_minimum_required(VERSION 3.16)
project(MIPS_IR)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Assembler)
add_subdirectory(MemoryIR)
add_subdirectory(RegisterAllocation)

add_executable(MIPS_IR library.h library.cpp)

target_link_libraries(MIPS_IR LINK_PUBLIC assembler)
target_link_libraries(MIPS_IR LINK_PUBLIC memoryir)
target_link_libraries(MIPS_IR LINK_PUBLIC registeralloc)
