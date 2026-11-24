#include <iostream>
#include <string>
#include <cassert>
#include "parser/Driver.hpp"
#include "semantic/TypeChecker.hpp"
#include "ir/TACGenerator.hpp"
#include "optimizer/Optimizer.hpp"
#include "VirtualMachine.hpp"

using namespace banglascript;

void test_basic_arithmetic_and_vm() {
    std::cout << "[TEST] Running Basic Arithmetic & VM Execution... ";
    std::string code = R"(
        sonkha a = 15;
        sonkha b = 25;
        sonkha c = a + b * 2;
        dekhao(c);
    )";

    DiagnosticsEngine diag;
    Driver driver(diag);
    assert(driver.parseString(code, "test_arith.bs"));
    assert(!diag.hasErrors());

    TypeChecker tc(diag);
    assert(tc.check(*driver.getAST()));
    assert(!diag.hasErrors());

    TACGenerator tacGen;
    TACProgram tac = tacGen.generate(*driver.getAST());
    assert(!tac.empty());

    std::ostringstream out;
    VirtualMachine vm(std::cin, out, std::cerr);
    int exitCode = vm.execute(tac);
    assert(exitCode == 0);
    assert(out.str() == "65\n");
    std::cout << "PASSED\n";
}

void test_control_flow_and_loops() {
    std::cout << "[TEST] Running Control Flow & While Loop... ";
    std::string code = R"(
        sonkha sum = 0;
        sonkha i = 1;
        jotokhon (i <= 5) {
            sum = sum + i;
            i = i + 1;
        }
        dekhao(sum);
    )";

    DiagnosticsEngine diag;
    Driver driver(diag);
    assert(driver.parseString(code, "test_loop.bs"));

    TypeChecker tc(diag);
    assert(tc.check(*driver.getAST()));

    TACGenerator tacGen;
    TACProgram tac = tacGen.generate(*driver.getAST());

    std::ostringstream out;
    VirtualMachine vm(std::cin, out, std::cerr);
    int exitCode = vm.execute(tac);
    assert(exitCode == 0);
    assert(out.str() == "15\n"); // 1+2+3+4+5 = 15
    std::cout << "PASSED\n";
}

void test_functions_and_recursion() {
    std::cout << "[TEST] Running Recursive Factorial Function... ";
    std::string code = R"(
        kaj fact(sonkha n) {
            jodi (n <= 1) {
                ferot 1;
            }
            ferot n * fact(n - 1);
        }

        sonkha res = fact(5);
        dekhao(res);
    )";

    DiagnosticsEngine diag;
    Driver driver(diag);
    assert(driver.parseString(code, "test_recursion.bs"));

    TypeChecker tc(diag);
    assert(tc.check(*driver.getAST()));

    TACGenerator tacGen;
    TACProgram tac = tacGen.generate(*driver.getAST());

    std::ostringstream out;
    VirtualMachine vm(std::cin, out, std::cerr);
    int exitCode = vm.execute(tac);
    assert(exitCode == 0);
    assert(out.str() == "120\n"); // 5! = 120
    std::cout << "PASSED\n";
}

void test_bengali_unicode_keywords() {
    std::cout << "[TEST] Running Native Bengali Script Keywords... ";
    std::string code = R"(
        সংখ্যা ক = ১০;
        সংখ্যা খ = ২০;
        যদি (ক < খ) {
            দেখাও("সফল!");
        }
    )";

    DiagnosticsEngine diag;
    Driver driver(diag);
    assert(driver.parseString(code, "test_bengali.bs"));

    TypeChecker tc(diag);
    assert(tc.check(*driver.getAST()));

    TACGenerator tacGen;
    TACProgram tac = tacGen.generate(*driver.getAST());

    std::ostringstream out;
    VirtualMachine vm(std::cin, out, std::cerr);
    int exitCode = vm.execute(tac);
    assert(exitCode == 0);
    assert(out.str() == "সফল!\n");
    std::cout << "PASSED\n";
}

void test_semantic_errors_detection() {
    std::cout << "[TEST] Running Semantic Error Diagnostics... ";
    // 1. Undeclared variable
    {
        std::string badCode = "dekhao(undeclaredVar);";
        DiagnosticsEngine diag;
        Driver driver(diag);
        assert(driver.parseString(badCode));
        TypeChecker tc(diag);
        bool ok = tc.check(*driver.getAST());
        assert(!ok);
        assert(diag.hasErrors());
    }

    // 2. Type mismatch: assigning string to int
    {
        std::string badCode = "sonkha x = \"invalid\";";
        DiagnosticsEngine diag;
        Driver driver(diag);
        assert(driver.parseString(badCode));
        TypeChecker tc(diag);
        bool ok = tc.check(*driver.getAST());
        assert(!ok);
        assert(diag.hasErrors());
    }

    // 3. Duplicate variable in same scope
    {
        std::string badCode = "sonkha x = 1; sonkha x = 2;";
        DiagnosticsEngine diag;
        Driver driver(diag);
        assert(driver.parseString(badCode));
        TypeChecker tc(diag);
        bool ok = tc.check(*driver.getAST());
        assert(!ok);
        assert(diag.hasErrors());
    }
    std::cout << "PASSED\n";
}

void test_optimizer_constant_folding() {
    std::cout << "[TEST] Running TAC Optimizer (Constant Folding)... ";
    std::string code = "sonkha x = 10 + 20 * 3;";
    DiagnosticsEngine diag;
    Driver driver(diag);
    assert(driver.parseString(code));
    TypeChecker tc(diag);
    assert(tc.check(*driver.getAST()));

    TACGenerator tacGen;
    TACProgram rawTac = tacGen.generate(*driver.getAST());

    TACOptimizer opt;
    TACProgram optTac = opt.optimize(rawTac);

    // Verify optimized TAC folded the constant expression
    bool found70 = false;
    for (const auto& inst : optTac) {
        if (inst.arg1 == "70" || inst.result == "70") {
            found70 = true;
            break;
        }
    }
    assert(found70);
    std::cout << "PASSED\n";
}

int main() {
    std::cout << "\n============================================\n"
              << "   BanglaScript Automated Test Suite        \n"
              << "============================================\n\n";

    test_basic_arithmetic_and_vm();
    test_control_flow_and_loops();
    test_functions_and_recursion();
    test_bengali_unicode_keywords();
    test_semantic_errors_detection();
    test_optimizer_constant_folding();

    std::cout << "\n\033[1;32m>>> ALL 6 TEST SUITES PASSED CLEANLY! <<<\033[0m\n\n";
    return 0;
}
