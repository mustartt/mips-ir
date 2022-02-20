//
// Created by henry on 2022-02-20.
//

#ifndef MIPS_IR_ASSEMBLER_INSTRUCTION_H_
#define MIPS_IR_ASSEMBLER_INSTRUCTION_H_

#include <ostream>
#include <unordered_map>

namespace assembler {

using Register = uint32_t;
using LabelTable = std::unordered_map<std::string, size_t>;

class Instruction {
  public:
    size_t currOffset = 0;
    virtual ~Instruction() = default;
    virtual void emit(std::ostream &ostream, const LabelTable &table) = 0;
};

class Word : public Instruction {
    int64_t val;
  public:
    explicit Word(int64_t val) : val(val) {};
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class WordLabel : public Instruction {
    std::string val;
  public:
    explicit WordLabel(std::string val) : val(std::move(val)) {};
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class JrInstr : public Instruction {
    Register val;
  public:
    explicit JrInstr(Register val) : val{val} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class JalrInstr : public Instruction {
    Register val;
  public:
    explicit JalrInstr(Register val) : val{val} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class AddiInstr : public Instruction {
    Register t;
    Register s;
    int i;
  public:
    explicit AddiInstr(Register t, Register s, int i) : t{t}, s{s}, i{i} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class AddInstr : public Instruction {
    Register dest;
    Register s;
    Register t;
  public:
    explicit AddInstr(Register dest, Register s, Register t) : dest{dest}, s{s}, t{t} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class SubInstr : public Instruction {
    Register dest;
    Register s;
    Register t;
  public:
    explicit SubInstr(Register dest, Register s, Register t) : dest{dest}, s{s}, t{t} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class SltInstr : public Instruction {
    Register dest;
    Register s;
    Register t;
  public:
    explicit SltInstr(Register dest, Register s, Register t) : dest{dest}, s{s}, t{t} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class SltuInstr : public Instruction {
    Register dest;
    Register s;
    Register t;
  public:
    explicit SltuInstr(Register dest, Register s, Register t) : dest{dest}, s{s}, t{t} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class BeqInstr : public Instruction {
    Register s;
    Register t;
    int i = 0;
    std::string label;
  public:
    BeqInstr(Register s, Register t, int i) : s{s}, t{t}, i{i} {}
    BeqInstr(Register s, Register t, std::string label) : s{s}, t{t}, label{std::move(label)} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class BneInstr : public Instruction {
    Register s;
    Register t;
    int i = 0;
    std::string label;
  public:
    BneInstr(Register s, Register t, int i) : s{s}, t{t}, i{i} {}
    BneInstr(Register s, Register t, std::string label) : s{s}, t{t}, label{std::move(label)} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class LisInstr : public Instruction {
    Register d;
  public:
    explicit LisInstr(Register d) : d{d} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class MfloInstr : public Instruction {
    Register d;
  public:
    explicit MfloInstr(Register d) : d{d} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class MfhiInstr : public Instruction {
    Register d;
  public:
    explicit MfhiInstr(Register d) : d{d} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;

};

class MultInstr : public Instruction {
    Register s;
    Register t;
  public:
    MultInstr(Register s, Register t) : s{s}, t{t} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class MultuInstr : public Instruction {
    Register s;
    Register t;
  public:
    MultuInstr(Register s, Register t) : s{s}, t{t} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class DivInstr : public Instruction {
    Register s;
    Register t;
  public:
    DivInstr(Register s, Register t) : s{s}, t{t} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class DivuInstr : public Instruction {
    Register s;
    Register t;
  public:
    DivuInstr(Register s, Register t) : s{s}, t{t} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class LwInstr : public Instruction {
    Register s;
    Register t;
    int i;

  public:
    LwInstr(Register s, Register t, int i) : s{s}, t{t}, i{i} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

class SwInstr : public Instruction {
    Register s;
    Register t;
    int i;

  public:
    SwInstr(Register s, Register t, int i) : s{s}, t{t}, i{i} {}
    void emit(std::ostream &ostream, const LabelTable &table) override;
};

}

#endif //MIPS_IR_ASSEMBLER_INSTRUCTION_H_
