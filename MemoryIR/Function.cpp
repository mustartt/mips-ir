//
// Created by henry on 2022-02-19.
//

#include "IRContext.h"

#include "Function.h"
#include "Block.h"
#include "Instruction.h"

namespace mipsir {

Function::Function(IRContext *ctx, std::string name, const std::vector<std::string> &args)
    : m_context(ctx), m_name(std::move(name)) {
    for (const auto &arg: args) {
        m_args.push_back(m_context->createArgument(name, arg));
    }
}

void Function::print(std::ostream &ostream) {
    ostream << "func " << m_name << "(";
    for (size_t i = 0; i < m_args.size(); ++i) {
        ostream << m_args[i]->getArgName() << ": %" << i + 1;
        if (i + 1 != m_args.size()) ostream << ", ";
    }
    ostream << ") {" << std::endl;
    using Register = uint32_t;
    using Label = uint32_t;

    std::unordered_map<Value *, Register> virtualAssignment;
    Register nextAvailable = 1;
    for (const auto &arg: m_args) {
        virtualAssignment[arg] = nextAvailable++;
    }

    for (const auto &block: m_blocks) {
        for (const auto &instr: block->getInstructions()) {
            if (instr->hasReturnValue()) virtualAssignment[instr] = nextAvailable++;
        }
    }

    Label nextLabel = 1;
    for (const auto &block: m_blocks) {
        ostream << "  label_" << nextLabel << ":" << std::endl;
        for (const auto &instr: block->getInstructions()) {
            if (virtualAssignment.count(instr)) {
                ostream << "    %" << virtualAssignment[instr] << " = ";
                instr->print(ostream);
                ostream << " ";
                for (const auto &operand: instr->getOperands()) {
                    if (virtualAssignment.count(operand)) {
                        ostream << "%" << virtualAssignment[operand];
                    } else {
                        operand->print(ostream);
                    }
                    ostream << " ";
                }
            }
            ostream << std::endl;
        }
    }

    ostream << "}";
}

}
