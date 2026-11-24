#pragma once
#include "parser/Driver.hpp"
#include "semantic/TypeChecker.hpp"
#include "ir/TACGenerator.hpp"
#include "optimizer/Optimizer.hpp"
#include "VirtualMachine.hpp"
#include <string>

namespace banglascript {

class REPL {
public:
    static void start();

private:
    static void printHelp();
    static void printKeywords();
};

} // namespace banglascript
