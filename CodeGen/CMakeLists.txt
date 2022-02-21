cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

add_library(codegen
        CodeGen.h
        Targets/MipsCodegenTarget.cpp Targets/MipsCodegenTarget.h
        Targets/MipsIRTargetGen.cpp Targets/MipsIRTargetGen.h
        IRTargetGen.h IRTargetGen.cpp)

target_include_directories(codegen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(codegen PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(codegen LINK_PUBLIC allocation)
