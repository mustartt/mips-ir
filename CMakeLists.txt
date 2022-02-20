cmake_minimum_required(VERSION 3.16)
project(MIPS_IR)

set(CMAKE_CXX_STANDARD 20)

add_executable(MIPS_IR library.h library.cpp RegisterAllocation/InterferenceGraph.cpp RegisterAllocation/InterferenceGraph.h MemoryIR/Value.h MemoryIR/Constant.h MemoryIR/Instruction.cpp MemoryIR/Instruction.h MemoryIR/IRContext.cpp MemoryIR/IRContext.h MemoryIR/Block.cpp MemoryIR/Block.h MemoryIR/Function.cpp MemoryIR/Function.h MemoryIR/Module.cpp MemoryIR/Module.h MemoryIR/IRbuilder.h RegisterAllocation/LivenessAnalyzer.cpp RegisterAllocation/LivenessAnalyzer.h)
