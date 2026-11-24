#pragma once
#include "ir/Instruction.hpp"
#include <vector>
#include <unordered_map>
#include <string>

namespace banglascript {

class TACOptimizer {
public:
    TACOptimizer() = default;

    /**
     * @brief Runs optimization pipeline on input TAC program.
     * @param original Input unoptimized TAC.
     * @return Optimized TAC program guaranteed to have identical observable behavior.
     */
    TACProgram optimize(const TACProgram& original);

private:
    bool constantFoldingPass(TACProgram& program);
    bool constantPropagationPass(TACProgram& program);
    bool deadCodeEliminationPass(TACProgram& program);

    static bool isIntegerLiteral(const std::string& str, int64_t& outVal);
    static bool isDoubleLiteral(const std::string& str, double& outVal);
    static bool isBooleanLiteral(const std::string& str, bool& outVal);
};

} // namespace banglascript
