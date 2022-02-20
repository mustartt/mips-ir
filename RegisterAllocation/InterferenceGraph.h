//
// Created by henry on 2022-02-17.
//

#ifndef MIPS_IR_REGISTERALLOCATION_INTERFERENCEGRAPH_H_
#define MIPS_IR_REGISTERALLOCATION_INTERFERENCEGRAPH_H_

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>

namespace mipsir {

using RegisterID = uint32_t;
using Color = uint32_t;

class Register {
    RegisterID m_registerID;
    Color m_color;
  public:
    explicit Register(uint32_t registerID) : m_registerID(registerID), m_color(0) {};

    [[nodiscard]] RegisterID getRegisterId() const { return m_registerID; }
    [[nodiscard]] Color getColor() const { return m_color; }
    void setColor(Color newColor) { m_color = newColor; }
    bool operator==(const Register &rhs) const { return m_registerID == rhs.m_registerID; }
};

class InterferenceGraph final {
    bool m_colored = false;
    std::unordered_map<Register *, std::unordered_set<Register *>> m_graph;
    std::unordered_map<RegisterID, std::unique_ptr<Register>> m_registerContext;
  public:
    InterferenceGraph() = default;
    ~InterferenceGraph() = default;

    void addInterference(RegisterID a, RegisterID b);
    void color();
    std::unordered_map<RegisterID, Color> getColoring();
};

}

#endif //MIPS_IR_REGISTERALLOCATION_INTERFERENCEGRAPH_H_
