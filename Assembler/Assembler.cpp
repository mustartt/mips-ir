//
// Created by henry on 2022-02-20.
//

#include "Assembler.h"

namespace assembler {

void Assembler::incrementOffset() {
    m_instrOffset += 4;
}

void Assembler::emit(std::ostream &ostream) {
    size_t pc = 0;
    for (auto &instr: m_program) {
        pc += 4;
        instr->emit(ostream, m_symbolTable);
    }
}

void Assembler::print(std::ostream &ostream) {
    std::unordered_map<size_t, std::string> labels;
    for (const auto&[label, offset]: m_symbolTable) {
        labels[offset] = label;
    }
    size_t offset = 0;
    for (auto &instr: m_program) {
        if (labels.count(offset)) ostream << labels[offset] << ": " << std::endl;
        instr->print(ostream, m_symbolTable);
        offset += 4;
    }
}

void Assembler::printLabels(std::ostream &ostream) {
    for (auto &pair: m_symbolTable) {
        ostream << pair.first << " " << pair.second << std::endl;
    }
}

void Assembler::insertLabel(const std::string &label) {
    if (m_symbolTable.count(label)) {
        throw std::runtime_error("Label does not exist");
    }
    m_symbolTable[label] = m_instrOffset;
}

void Assembler::emitWord(int64_t val) {
    auto WordInstr = std::make_unique<Word>(val);
    m_program.push_back(std::move(WordInstr));
    incrementOffset();
}

void Assembler::emitWord(const std::string &label) {
    auto WordInstr = std::make_unique<WordLabel>(label);
    m_program.push_back(std::move(WordInstr));
    incrementOffset();
}

void Assembler::emitJr(Register val) {
    auto JrIns = std::make_unique<JrInstr>(val);
    m_program.push_back(std::move(JrIns));
    incrementOffset();
}

void Assembler::emitJalr(Register val) {
    auto JalrIns = std::make_unique<JalrInstr>(val);
    m_program.push_back(std::move(JalrIns));
    incrementOffset();
}

void Assembler::emitAdd(Register d, Register s, Register t) {
    auto AddIns = std::make_unique<AddInstr>(d, s, t);
    m_program.push_back(std::move(AddIns));
    incrementOffset();
}

void Assembler::emitSub(Register d, Register s, Register t) {
    auto SubIns = std::make_unique<SubInstr>(d, s, t);
    m_program.push_back(std::move(SubIns));
    incrementOffset();
}

void Assembler::emitSlt(Register d, Register s, Register t) {
    auto SltIns = std::make_unique<SltInstr>(d, s, t);
    m_program.push_back(std::move(SltIns));
    incrementOffset();
}

void Assembler::emitSltu(Register d, Register s, Register t) {
    auto SltuIns = std::make_unique<SltuInstr>(d, s, t);
    m_program.push_back(std::move(SltuIns));
    incrementOffset();
}

void Assembler::emitBeq(Register d, Register s, int t) {
    auto BeqIns = std::make_unique<BeqInstr>(d, s, t);
    m_program.push_back(std::move(BeqIns));
    incrementOffset();
}

void Assembler::emitBeq(Register d, Register s, std::string label) {
    auto BeqIns = std::make_unique<BeqInstr>(d, s, std::move(label));
    BeqIns->currOffset = m_instrOffset;
    m_program.push_back(std::move(BeqIns));
    incrementOffset();
}

void Assembler::emitBne(Register d, Register s, int t) {
    auto BneIns = std::make_unique<BneInstr>(d, s, t);
    m_program.push_back(std::move(BneIns));
    incrementOffset();
}

void Assembler::emitBne(Register d, Register s, std::string label) {
    auto BneIns = std::make_unique<BneInstr>(d, s, std::move(label));
    BneIns->currOffset = m_instrOffset;
    m_program.push_back(std::move(BneIns));
    incrementOffset();
}

void Assembler::emitLis(Register d) {
    auto LisIns = std::make_unique<LisInstr>(d);
    m_program.push_back(std::move(LisIns));
    incrementOffset();
}

void Assembler::emitMflo(Register d) {
    auto MfloIns = std::make_unique<MfloInstr>(d);
    m_program.push_back(std::move(MfloIns));
    incrementOffset();
}

void Assembler::emitMfhi(Register d) {
    auto MfhiIns = std::make_unique<MfhiInstr>(d);
    m_program.push_back(std::move(MfhiIns));
    incrementOffset();
}

void Assembler::emitMult(Register s, Register t) {
    auto MultIns = std::make_unique<MultInstr>(s, t);
    m_program.push_back(std::move(MultIns));
    incrementOffset();
}

void Assembler::emitMultu(Register s, Register t) {
    auto MultuIns = std::make_unique<MultuInstr>(s, t);
    m_program.push_back(std::move(MultuIns));
    incrementOffset();
}

void Assembler::emitDiv(Register s, Register t) {
    auto DivIns = std::make_unique<DivInstr>(s, t);
    m_program.push_back(std::move(DivIns));
    incrementOffset();
}

void Assembler::emitDivu(Register s, Register t) {
    auto DivuIns = std::make_unique<DivuInstr>(s, t);
    m_program.push_back(std::move(DivuIns));
    incrementOffset();
}

void Assembler::emitLw(Register s, Register t, int i) {
    auto LwIns = std::make_unique<LwInstr>(s, t, i);
    m_program.push_back(std::move(LwIns));
    incrementOffset();
}

void Assembler::emitSw(Register s, Register t, int i) {
    auto SwIns = std::make_unique<SwInstr>(s, t, i);
    m_program.push_back(std::move(SwIns));
    incrementOffset();
}

void Assembler::emitAddi(Register t, Register s, int i) {
    auto AddiIns = std::make_unique<AddiInstr>(t, s, i);
    m_program.push_back(std::move(AddiIns));
    incrementOffset();
}

}
