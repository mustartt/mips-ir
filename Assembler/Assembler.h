//
// Created by henry on 2022-02-20.
//

#ifndef MIPS_IR_ASSEMBLER_ASSEMBLER_H_
#define MIPS_IR_ASSEMBLER_ASSEMBLER_H_

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

#include "Instruction.h"

namespace assembler {

class Assembler {
    size_t m_instrOffset = 0;
    std::vector<std::unique_ptr<Instruction>> m_program;
    std::unordered_map<std::string, size_t> m_symbolTable;
    void incrementOffset();
  public:
    Assembler() = default;
    Assembler(const Assembler &) = delete;
    Assembler(Assembler &&) = default;

    void emit(std::ostream &ostream);
    void print(std::ostream &ostream);
    void printLabels(std::ostream &ostream);

    void insertLabel(const std::string &label);
    void emitWord(int64_t val);
    void emitWord(const std::string &label);

    void emitJr(Register val);
    void emitJalr(Register val);

    void emitJ(std::string label);
    void emitJal(std::string label);

    void emitAdd(Register d, Register s, Register t);
    void emitSub(Register d, Register s, Register t);

    void emitSlt(Register d, Register s, Register t);
    void emitSltu(Register d, Register s, Register t);

    void emitBeq(Register d, Register s, int t);
    void emitBeq(Register d, Register s, std::string label);
    void emitBne(Register d, Register s, int t);
    void emitBne(Register d, Register s, std::string label);

    void emitAddi(Register t, Register s, int i);

    void emitLis(Register d);
    void emitMflo(Register d);
    void emitMfhi(Register d);

    void emitMult(Register s, Register t);
    void emitMultu(Register s, Register t);
    void emitDiv(Register s, Register t);
    void emitDivu(Register s, Register t);

    void emitLw(Register s, Register t, int i);
    void emitSw(Register s, Register t, int i);
};

}

#endif //MIPS_IR_ASSEMBLER_ASSEMBLER_H_
