#include "REPL.hpp"
#include "ast/ASTPrettyPrinter.hpp"
#include <iostream>
#include <sstream>

#if defined(_WIN32)
#include <windows.h>
#endif

namespace banglascript {

void REPL::printHelp() {
    std::cout << "\033[1;36mBanglaScript Interactive REPL Commands:\033[0m\n"
              << "  .help       Display this help menu\n"
              << "  .keywords   Display list of all language keywords and types\n"
              << "  .clear      Clear screen\n"
              << "  .exit       Exit the REPL session\n\n";
}

void REPL::printKeywords() {
    std::cout << "\033[1;33m=== BanglaScript Keywords & Types ===\033[0m\n"
              << "  Data Types:  sonkha (সংখ্যা), dosomik (দশমিক), bakya (বাক্য), sotti (সত্যি), shunno (শূন্য)\n"
              << "  Condition:   jodi (যদি), nahole (নাহলে)\n"
              << "  Loops:       jotokhon (যতক্ষণ), bondho (বন্ধ), chaliyejao (চালিয়েযাও)\n"
              << "  Functions:   kaj (কাজ), ferot (ফেরত)\n"
              << "  I/O:         dekhao (দেখাও), nao (নাও)\n"
              << "  Booleans:    true (সত্য), false (মিথ্যা)\n"
              << "  Operators:   +, -, *, /, %, ==, !=, <, <=, >, >=, && (ebong), || (othoba), ! (na)\n\n";
}

void REPL::start() {
#if defined(_WIN32)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "\033[1;32m"
              << "BanglaScript Interactive REPL (v1.0.0)\n"
              << "Type '.help' for commands, '.exit' to quit.\033[0m\n\n";

    DiagnosticsEngine diagnostics;
    Driver driver(diagnostics);
    TypeChecker typeChecker(diagnostics);
    TACGenerator tacGen;
    TACOptimizer optimizer;
    VirtualMachine vm;

    std::string accumulatedCode;
    int braceDepth = 0;

    while (true) {
        if (braceDepth > 0) {
            std::cout << "\033[1;34m... \033[0m";
        } else {
            std::cout << "\033[1;32mbs> \033[0m";
        }

        std::string line;
        if (!std::getline(std::cin, line)) {
            break;
        }

        if (accumulatedCode.empty() && !line.empty() && line[0] == '.') {
            if (line == ".exit" || line == ".quit") {
                break;
            } else if (line == ".help") {
                printHelp();
                continue;
            } else if (line == ".keywords") {
                printKeywords();
                continue;
            } else if (line == ".clear") {
#if defined(_WIN32)
                system("cls");
#else
                system("clear");
#endif
                continue;
            } else {
                std::cout << "\033[1;31mUnknown command: " << line << "\033[0m\n";
                continue;
            }
        }

        for (char c : line) {
            if (c == '{') braceDepth++;
            else if (c == '}') braceDepth = std::max(0, braceDepth - 1);
        }

        accumulatedCode += line + "\n";

        if (braceDepth > 0) {
            continue;
        }

        std::string codeToRun = accumulatedCode;
        accumulatedCode.clear();

        if (codeToRun.find_first_not_of(" \t\n\r") == std::string::npos) {
            continue;
        }

        diagnostics.clear();
        if (!driver.parseString(codeToRun, "<repl>")) {
            diagnostics.printAll(std::cerr, true);
            continue;
        }

        if (!typeChecker.check(*driver.getAST())) {
            diagnostics.printAll(std::cerr, true);
            continue;
        }

        TACProgram rawTAC = tacGen.generate(*driver.getAST());
        TACProgram optTAC = optimizer.optimize(rawTAC);

        vm.execute(optTAC);
    }

    std::cout << "\n\033[1;33mবিদায়! (Goodbye!)\033[0m\n";
}

} // namespace banglascript
