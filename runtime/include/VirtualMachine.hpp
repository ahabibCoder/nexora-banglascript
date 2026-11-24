#pragma once
#include "ir/Instruction.hpp"
#include "Value.hpp"
#include <vector>
#include <unordered_map>
#include <stack>
#include <string>
#include <iostream>

namespace banglascript {

struct CallFrame {
    std::string functionName;
    size_t returnPC{0};
    std::string returnTarget;
    std::unordered_map<std::string, RuntimeValue> locals;
};

class VirtualMachine {
public:
    explicit VirtualMachine(std::istream& in = std::cin, std::ostream& out = std::cout, std::ostream& err = std::cerr)
        : in_(in), out_(out), err_(err) {}

    /**
     * @brief Executes a TAC program from start to finish.
     * @param program The compiled TAC instructions.
     * @return Exit code (0 for success, non-zero for runtime error).
     */
    int execute(const TACProgram& program);

    void setMaxInstructions(size_t maxInst) { maxInstructions_ = maxInst; }
    void setMaxRecursionDepth(size_t maxDepth) { maxRecursionDepth_ = maxDepth; }

    const std::unordered_map<std::string, RuntimeValue>& getGlobals() const { return globals_; }

private:
    std::istream& in_;
    std::ostream& out_;
    std::ostream& err_;

    size_t maxInstructions_{10000000}; // 10 million instruction limit
    size_t maxRecursionDepth_{10000};  // Recursion limit

    std::unordered_map<std::string, RuntimeValue> globals_;
    std::stack<CallFrame> callStack_;
    std::vector<RuntimeValue> paramQueue_;
    std::unordered_map<std::string, size_t> labelIndices_;
    std::unordered_map<std::string, size_t> functionIndices_;

    RuntimeValue resolveValue(const std::string& token);
    void assignValue(const std::string& varName, const RuntimeValue& val);
    RuntimeValue parseLiteral(const std::string& token);
};

} // namespace banglascript
