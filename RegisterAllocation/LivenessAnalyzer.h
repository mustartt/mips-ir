//
// Created by henry on 2022-02-20.
//

#ifndef MIPS_IR_REGISTERALLOCATION_LIVENESSANALYZER_H_
#define MIPS_IR_REGISTERALLOCATION_LIVENESSANALYZER_H_

#include <unordered_map>

#include "InterferenceGraph.h"

namespace mipsir {

class Function;
class Value;
class LivenessAnalyzer {
  public:
    using Line = uint32_t;
    using Register = uint32_t;

    static std::unordered_map<Value *, Register> getVirtualRegisterAssignment(Function *function);
    static std::unordered_map<Value *, std::pair<Line, Line>> analyzeMergedLiveRange(Function *function);
    static InterferenceGraph constructRegisterInterferenceGraph(Function *function);
};

}

#endif //MIPS_IR_REGISTERALLOCATION_LIVENESSANALYZER_H_
