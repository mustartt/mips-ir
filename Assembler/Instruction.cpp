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

void Word::print(std::ostream &ostream, const LabelTable &table) {
    ostream << ".word " << val << std::endl;
}

void WordLabel::emit(std::ostream &ostream, const LabelTable &table) {
    if (table.count(val)) {
        convert_to_binary(table.at(val), ostream);
    } else {
        throw std::runtime_error("Label does not exist in symbol table!");
    }
}

void WordLabel::print(std::ostream &ostream, const LabelTable &table) {
    ostream << ".word " << val << std::endl;
}

void JrInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (val << 21) | (1 << 3);
    convert_to_binary(instr, ostream);
}

void JrInstr::print(std::ostream &ostream, const LabelTable &table) {
    ostream << "jr $" << val << std::endl;
}

void JalrInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (val << 21) | (1 << 3) | 1;
    convert_to_binary(instr, ostream);
}

void JalrInstr::print(std::ostream &ostream, const LabelTable &table) {
    ostream << "jalr " << val << std::endl;
}

void AddiInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (1 << 29) | (s << 21) | (t << 16) | (i & 0xffff);
    convert_to_binary(instr, ostream);
}

void AddiInstr::print(std::ostream &ostream, const LabelTable &table) {
    ostream << "add $" << t << " $" << s << " " << i << std::endl;
}

void AddInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (0 << 26) | (s << 21) | (t << 16) | (dest << 11) | 32;
    convert_to_binary(instr, ostream);
}

void AddInstr::print(std::ostream &ostream, const LabelTable &table) {
    ostream << "add $" << dest << " $" << s << " $" << t << std::endl;
}

void SubInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (0 << 26) | (s << 21) | (t << 16) | (dest << 11) | 34;
    convert_to_binary(instr, ostream);
}

void SubInstr::print(std::ostream &ostream, const LabelTable &table) {
    ostream << "sub $" << dest << " $" << s << " $" << t << std::endl;
}

void SltInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (0 << 26) | (s << 21) | (t << 16) | (dest << 11) | 42;
    convert_to_binary(instr, ostream);
}

void SltInstr::print(std::ostream &ostream, const LabelTable &table) {
    ostream << "slt $" << dest << " $" << s << " $" << t << std::endl;
}

void SltuInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (0 << 26) | (s << 21) | (t << 16) | (dest << 11) | 43;
    convert_to_binary(instr, ostream);
}

void SltuInstr::print(std::ostream &ostream, const LabelTable &table) {
    ostream << "sltu $" << dest << " $" << s << " $" << t << std::endl;

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

void BeqInstr::print(std::ostream &ostream, const LabelTable &table) {
    if (label.empty()) {
        ostream << "beq $" << s << " $" << t << " " << i << std::endl;
    } else {
        ostream << "beq $" << s << " $" << t << " " << label << std::endl;
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

void BneInstr::print(std::ostream &ostream, const LabelTable &table) {
    if (label.empty()) {
        ostream << "bne $" << s << " $" << t << " " << i << std::endl;
    } else {
        ostream << "bne $" << s << " $" << t << " " << label << std::endl;
    }
}

void LisInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (d << 11) | (1 << 4) | (1 << 2);
    convert_to_binary(instr, ostream);
}

void LisInstr::print(std::ostream &ostream, const LabelTable &table) {
    ostream << "lis $" << d << std::endl;
}

void MfloInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (d << 11) | (1 << 4) | (1 << 1);
    convert_to_binary(instr, ostream);
}

void MfloInstr::print(std::ostream &ostream, const LabelTable &table) {
    ostream << "mflo $" << d << std::endl;

}

void MfhiInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (d << 11) | (1 << 4);
    convert_to_binary(instr, ostream);
}

void MfhiInstr::print(std::ostream &ostream, const LabelTable &table) {
    ostream << "mfhi $" << d << std::endl;
}

void MultInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (s << 21) | (t << 16) | (1 << 4) | (1 << 3);
    convert_to_binary(instr, ostream);
}

void MultInstr::print(std::ostream &ostream, const LabelTable &table) {
    ostream << "mult $" << s << " $" << t << std::endl;
}

void MultuInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (s << 21) | (t << 16) | (1 << 4) | (1 << 3) | 1;
    convert_to_binary(instr, ostream);
}

void MultuInstr::print(std::ostream &ostream, const LabelTable &table) {
    ostream << "multu $" << s << " $" << t << std::endl;
}

void DivInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (s << 21) | (t << 16) | (1 << 4) | (1 << 3) | 2;
    convert_to_binary(instr, ostream);
}

void DivInstr::print(std::ostream &ostream, const LabelTable &table) {
    ostream << "div $" << s << " $" << t << std::endl;
}

void DivuInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (s << 21) | (t << 16) | (1 << 4) | (1 << 3) | 3;
    convert_to_binary(instr, ostream);
}

void DivuInstr::print(std::ostream &ostream, const LabelTable &table) {
    ostream << "divu $" << s << " $" << t << std::endl;

}

void LwInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (1 << 31) | (1 << 27) | (1 << 26) | (s << 21) | (t << 16) | (i & 0xffff);
    convert_to_binary(instr, ostream);
}

void LwInstr::print(std::ostream &ostream, const LabelTable &table) {
    ostream << "lw $" << t << " $" << i << "($" << s << ")" << std::endl;
}

void SwInstr::emit(std::ostream &ostream, const LabelTable &table) {
    int instr = (1 << 31) | (1 << 29) | (1 << 27) | (1 << 26) | (s << 21) | (t << 16) | (i & 0xffff);
    convert_to_binary(instr, ostream);
}

void SwInstr::print(std::ostream &ostream, const LabelTable &table) {
    ostream << "sw $" << t << " $" << i << "($" << s << ")" << std::endl;
}

}
