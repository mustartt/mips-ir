//
// Created by henry on 2022-02-20.
//

#include "Instruction.h"

namespace assembler {

void convert_to_binary(int i, std::ostream &ostream) {
    unsigned char c = i >> 24;
    ostream << c;
    c = i >> 16;
    ostream << c;
    c = i >> 8;
    ostream << c;
    c = i;
    ostream << c;
}

void Word::emit(std::ostream &ostream, const LabelTable &table) {
    if (-2147483648 <= val && val <= 4294967295) {
        convert_to_binary(val, ostream);
    } else {
        throw std::runtime_error(".word value out of range!");
    }
}

void WordLabel::emit(std::ostream &ostream, const LabelTable &table) {
    if (table.count(val)) {
        convert_to_binary(table.at(val), ostream);
    } else {
        throw std::runtime_error("Label does not exist in symbol table!");
    }
}

void JrInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (val << 21) | (1 << 3);
    convert_to_binary(instr, ostream);
}

void JalrInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (val << 21) | (1 << 3) | 1;
    convert_to_binary(instr, ostream);
}

void AddiInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (1 << 29) | (s << 21) | (t << 16) | (i & 0xffff);
    convert_to_binary(instr, ostream);
}

void AddInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (0 << 26) | (s << 21) | (t << 16) | (dest << 11) | 32;
    convert_to_binary(instr, ostream);
}

void SubInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (0 << 26) | (s << 21) | (t << 16) | (dest << 11) | 34;
    convert_to_binary(instr, ostream);
}

void SltInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (0 << 26) | (s << 21) | (t << 16) | (dest << 11) | 42;
    convert_to_binary(instr, ostream);
}

void SltuInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (0 << 26) | (s << 21) | (t << 16) | (dest << 11) | 43;
    convert_to_binary(instr, ostream);
}

void BeqInstr::emit(std::ostream &ostream, const LabelTable &table) {
    if (label.empty()) {
        int instr = (1 << 28) | (s << 21) | (t << 16) | (i & 0xffff);
        convert_to_binary(instr, ostream);
    } else {
        if (table.count(label)) {
            int offset = (table.at(label) - (currOffset + 4)) / 4;
            int instr = (1 << 28) | (s << 21) | (t << 16) | (offset & 0xffff);
            convert_to_binary(instr, ostream);
        } else {
            throw std::runtime_error("Label does not exist!");
        }
    }
}

void BneInstr::emit(std::ostream &ostream, const LabelTable &table) {
    if (label.empty()) {
        int instr = (1 << 28) | (1 << 26) | (s << 21) | (t << 16) | (i & 0xffff);
        convert_to_binary(instr, ostream);
    } else {
        if (table.count(label)) {
            int offset = (table.at(label) - (currOffset + 4)) / 4;
            int instr = (1 << 28) | (1 << 26) | (s << 21) | (t << 16) | (offset & 0xffff);
            convert_to_binary(instr, ostream);
        } else {
            throw std::runtime_error("Label does not exist!");
        }
    }
}

void LisInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (d << 11) | (1 << 4) | (1 << 2);
    convert_to_binary(instr, ostream);
}

void MfloInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (d << 11) | (1 << 4) | (1 << 1);
    convert_to_binary(instr, ostream);
}

void MfhiInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (d << 11) | (1 << 4);
    convert_to_binary(instr, ostream);
}

void MultInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (s << 21) | (t << 16) | (1 << 4) | (1 << 3);
    convert_to_binary(instr, ostream);
}

void MultuInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (s << 21) | (t << 16) | (1 << 4) | (1 << 3) | 1;
    convert_to_binary(instr, ostream);
}

void DivInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (s << 21) | (t << 16) | (1 << 4) | (1 << 3) | 2;
    convert_to_binary(instr, ostream);
}

void DivuInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (s << 21) | (t << 16) | (1 << 4) | (1 << 3) | 3;
    convert_to_binary(instr, ostream);
}

void LwInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (1 << 31) | (1 << 27) | (1 << 26) | (s << 21) | (t << 16) | (i & 0xffff);
    convert_to_binary(instr, ostream);
}

void SwInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (1 << 31) | (1 << 29) | (1 << 27) | (1 << 26) | (s << 21) | (t << 16) | (i & 0xffff);
    convert_to_binary(instr, ostream);
}

}
