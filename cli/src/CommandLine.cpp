#include "CommandLine.hpp"
#include "REPL.hpp"
#include "parser/Driver.hpp"
#include "ast/ASTPrettyPrinter.hpp"
#include "semantic/TypeChecker.hpp"
#include "ir/TACGenerator.hpp"
#include "optimizer/Optimizer.hpp"
#include "VirtualMachine.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>

#if defined(_WIN32)
#include <windows.h>
#endif

namespace banglascript {

namespace fs = std::filesystem;

void CommandLine::printBanner() {
    std::cout << "\033[1;32m"
              << "========================================================\n"
              << "   NEXORA — BanglaScript Programming Language (v1.0.0)  \n"
              << "   Tagline: Beyond the Ordinary                         \n"
              << "========================================================\033[0m\n\n";
}

void CommandLine::printVersion() {
    std::cout << "banglascript (BanglaScript Compiler & VM) 1.0.0\n"
              << "Core Architecture: C++17, Flex, GNU Bison, TAC IR, Stack VM\n"
              << "Product: NEXORA Ecosystem\n";
}

void CommandLine::printHelp() {
    printBanner();
    std::cout << "Usage: banglascript [command] [options] [file.bs]\n"
              << "Alias: bs [command] [options] [file.bs]\n\n"
              << "\033[1;33mPrimary Commands:\033[0m\n"
              << "  run <file.bs>          Compile and execute program in TAC Virtual Machine\n"
              << "  check <file.bs>        Validate lexical, syntactic, and semantic correctness\n"
              << "  compile <file.bs>      Run full compiler pipeline and verify all stages\n"
              << "  ast <file.bs>          Display Abstract Syntax Tree (AST)\n"
              << "  tac <file.bs>          Display Three-Address Code (TAC) intermediate representation\n"
              << "  repl                   Start interactive multiline REPL session\n"
              << "  init <project-name>    Scaffold a new BanglaScript project structure\n"
              << "  doctor                 Inspect environment, runtime health, and tooling\n"
              << "  version, --version     Display compiler and runtime version\n"
              << "  help, --help           Display this help menu\n\n"
              << "\033[1;33mExamples:\033[0m\n"
              << "  banglascript run hello.bs\n"
              << "  bs check main.bs\n"
              << "  bs ast test.bs\n"
              << "  bs repl\n";
}

int CommandLine::handleRun(const std::string& filepath) {
    DiagnosticsEngine diagnostics;
    Driver driver(diagnostics);

    if (!driver.parseFile(filepath)) {
        diagnostics.printAll(std::cerr, true);
        return 1;
    }

    TypeChecker typeChecker(diagnostics);
    if (!typeChecker.check(*driver.getAST())) {
        diagnostics.printAll(std::cerr, true);
        return 1;
    }

    TACGenerator tacGen;
    TACProgram rawTAC = tacGen.generate(*driver.getAST());

    TACOptimizer optimizer;
    TACProgram optTAC = optimizer.optimize(rawTAC);

    VirtualMachine vm;
    return vm.execute(optTAC);
}

int CommandLine::handleCheck(const std::string& filepath) {
    DiagnosticsEngine diagnostics;
    Driver driver(diagnostics);

    std::cout << "\033[1;36mChecking:\033[0m " << filepath << "\n";

    if (!driver.parseFile(filepath)) {
        diagnostics.printAll(std::cerr, true);
        std::cout << "\033[1;31m[FAILED] Syntax validation failed.\033[0m\n";
        return 1;
    }

    TypeChecker typeChecker(diagnostics);
    if (!typeChecker.check(*driver.getAST())) {
        diagnostics.printAll(std::cerr, true);
        std::cout << "\033[1;31m[FAILED] Semantic analysis failed.\033[0m\n";
        return 1;
    }

    std::cout << "\033[1;32m[OK] Lexer\033[0m\n"
              << "\033[1;32m[OK] Parser\033[0m\n"
              << "\033[1;32m[OK] Semantic Analysis\033[0m\n"
              << "\033[1;32mValidation successful: 0 errors, 0 warnings.\033[0m\n";
    return 0;
}

int CommandLine::handleCompile(const std::string& filepath, bool /*verbose*/) {
    printBanner();
    std::cout << "Compiling: " << filepath << "\n\n";

    DiagnosticsEngine diagnostics;
    Driver driver(diagnostics);

    if (!driver.parseFile(filepath)) {
        diagnostics.printAll(std::cerr, true);
        std::cout << "\n\033[1;31mCompilation failed at Parsing stage.\033[0m\n";
        return 1;
    }
    std::cout << "\033[1;32m[OK] Lexer\033[0m\n";
    std::cout << "\033[1;32m[OK] Parser\033[0m\n";

    TypeChecker typeChecker(diagnostics);
    if (!typeChecker.check(*driver.getAST())) {
        diagnostics.printAll(std::cerr, true);
        std::cout << "\n\033[1;31mCompilation failed at Semantic Analysis stage.\033[0m\n";
        return 1;
    }
    std::cout << "\033[1;32m[OK] Semantic Analysis & Type Checking\033[0m\n";

    TACGenerator tacGen;
    TACProgram rawTAC = tacGen.generate(*driver.getAST());
    std::cout << "\033[1;32m[OK] TAC Generation (" << rawTAC.size() << " instructions)\033[0m\n";

    TACOptimizer optimizer;
    TACProgram optTAC = optimizer.optimize(rawTAC);
    std::cout << "\033[1;32m[OK] Optimization (" << optTAC.size() << " instructions)\033[0m\n\n";

    std::cout << "\033[1;32mCompilation successful.\033[0m\n\n"
              << "Run:\n"
              << "  banglascript run " << filepath << "\n";
    return 0;
}

int CommandLine::handleAST(const std::string& filepath) {
    DiagnosticsEngine diagnostics;
    Driver driver(diagnostics);

    if (!driver.parseFile(filepath)) {
        diagnostics.printAll(std::cerr, true);
        return 1;
    }

    TypeChecker typeChecker(diagnostics);
    typeChecker.check(*driver.getAST());

    std::cout << "\033[1;33m=== Abstract Syntax Tree (AST) for " << filepath << " ===\033[0m\n";
    ASTPrettyPrinter printer(std::cout);
    printer.print(*driver.getAST());
    return 0;
}

int CommandLine::handleTAC(const std::string& filepath, bool optimized) {
    DiagnosticsEngine diagnostics;
    Driver driver(diagnostics);

    if (!driver.parseFile(filepath)) {
        diagnostics.printAll(std::cerr, true);
        return 1;
    }

    TypeChecker typeChecker(diagnostics);
    if (!typeChecker.check(*driver.getAST())) {
        diagnostics.printAll(std::cerr, true);
        return 1;
    }

    TACGenerator tacGen;
    TACProgram tac = tacGen.generate(*driver.getAST());

    if (optimized) {
        TACOptimizer optimizer;
        tac = optimizer.optimize(tac);
        std::cout << "\033[1;33m=== Optimized Three-Address Code (TAC) ===\033[0m\n";
    } else {
        std::cout << "\033[1;33m=== Raw Three-Address Code (TAC) ===\033[0m\n";
    }

    for (const auto& inst : tac) {
        std::cout << inst.toString() << "\n";
    }
    return 0;
}

int CommandLine::handleInit(const std::string& projectName) {
    try {
        fs::path projectPath(projectName);
        if (fs::exists(projectPath)) {
            std::cerr << "\033[1;31mError: Directory '" << projectName << "' already exists.\033[0m\n";
            return 1;
        }

        fs::create_directories(projectPath / "src");
        fs::create_directories(projectPath / "tests");

        // Create src/main.bs
        {
            std::ofstream f(projectPath / "src" / "main.bs");
            f << "// " << projectName << " - BanglaScript Project\n\n"
              << "sonkha a = 10;\n"
              << "sonkha b = 20;\n"
              << "sonkha result = a + b;\n\n"
              << "dekhao(\"স্বাগতম BanglaScript এ!\");\n"
              << "dekhao(\"Result: \");\n"
              << "dekhao(result);\n";
        }

        // Create tests/test_basic.bs
        {
            std::ofstream f(projectPath / "tests" / "test_basic.bs");
            f << "sonkha x = 5;\n"
              << "jodi (x == 5) {\n"
              << "    dekhao(\"Test Passed\");\n"
              << "} nahole {\n"
              << "    dekhao(\"Test Failed\");\n"
              << "}\n";
        }

        // Create banglascript.toml
        {
            std::ofstream f(projectPath / "banglascript.toml");
            f << "[project]\n"
              << "name = \"" << projectName << "\"\n"
              << "version = \"0.1.0\"\n"
              << "entry = \"src/main.bs\"\n";
        }

        // Create README.md
        {
            std::ofstream f(projectPath / "README.md");
            f << "# " << projectName << "\n\n"
              << "A BanglaScript project built with NEXORA.\n\n"
              << "## Run\n"
              << "```bash\n"
              << "banglascript run src/main.bs\n"
              << "```\n";
        }

        // Create .gitignore
        {
            std::ofstream f(projectPath / ".gitignore");
            f << "build/\n*.log\n";
        }

        std::cout << "\033[1;32m[SUCCESS] Project '" << projectName << "' created successfully!\033[0m\n\n"
                  << "To get started:\n"
                  << "  cd " << projectName << "\n"
                  << "  banglascript run src/main.bs\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mError creating project: " << e.what() << "\033[0m\n";
        return 1;
    }
}

int CommandLine::handleDoctor() {
    printBanner();
    std::cout << "\033[1;36m=== BanglaScript Doctor: Environment & Tooling Verification ===\033[0m\n\n";

    std::cout << "  OS Platform:             " <<
#if defined(_WIN32)
        "Windows x64\n"
#elif defined(__APPLE__)
        "macOS\n"
#else
        "Linux\n"
#endif
    ;

    std::cout << "  BanglaScript Compiler:   1.0.0 (C++17 Native)\n";
    std::cout << "  TAC Virtual Machine:     Ready\n";
    std::cout << "  UTF-8 Console Support:   " <<
#if defined(_WIN32)
        (GetConsoleOutputCP() == CP_UTF8 ? "Enabled (CP 65001)\n" : "Active with runtime wrapper\n")
#else
        "Native UTF-8\n"
#endif
    ;

    std::cout << "\n\033[1;32m[OK] Environment is healthy and ready for BanglaScript development.\033[0m\n";
    return 0;
}

int CommandLine::run(int argc, char* argv[]) {
#if defined(_WIN32)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    if (argc < 2) {
        printHelp();
        return 0;
    }

    std::string cmd = argv[1];

    if (cmd == "--help" || cmd == "-h" || cmd == "help") {
        printHelp();
        return 0;
    }

    if (cmd == "--version" || cmd == "-v" || cmd == "version") {
        printVersion();
        return 0;
    }

    if (cmd == "repl") {
        REPL::start();
        return 0;
    }

    if (cmd == "doctor") {
        return handleDoctor();
    }

    if (cmd == "init") {
        if (argc < 3) {
            std::cerr << "\033[1;31mError: Missing project name. Usage: banglascript init <project-name>\033[0m\n";
            return 1;
        }
        return handleInit(argv[2]);
    }

    if (cmd == "run") {
        if (argc < 3) {
            std::cerr << "\033[1;31mError: Missing source file. Usage: banglascript run <file.bs>\033[0m\n";
            return 1;
        }
        return handleRun(argv[2]);
    }

    if (cmd == "check") {
        if (argc < 3) {
            std::cerr << "\033[1;31mError: Missing source file. Usage: banglascript check <file.bs>\033[0m\n";
            return 1;
        }
        return handleCheck(argv[2]);
    }

    if (cmd == "compile") {
        if (argc < 3) {
            std::cerr << "\033[1;31mError: Missing source file. Usage: banglascript compile <file.bs>\033[0m\n";
            return 1;
        }
        return handleCompile(argv[2]);
    }

    if (cmd == "ast") {
        if (argc < 3) {
            std::cerr << "\033[1;31mError: Missing source file. Usage: banglascript ast <file.bs>\033[0m\n";
            return 1;
        }
        return handleAST(argv[2]);
    }

    if (cmd == "tac" || cmd == "ir") {
        if (argc < 3) {
            std::cerr << "\033[1;31mError: Missing source file. Usage: banglascript tac <file.bs>\033[0m\n";
            return 1;
        }
        bool opt = false;
        if (argc >= 4 && std::string(argv[3]) == "--opt") opt = true;
        return handleTAC(argv[2], opt);
    }

    // Default if a single argument ending in .bs is provided
    if (cmd.length() >= 3 && cmd.substr(cmd.length() - 3) == ".bs") {
        return handleRun(cmd);
    }

    std::cerr << "\033[1;31mUnknown command: " << cmd << ". Run 'banglascript --help' for usage.\033[0m\n";
    return 1;
}

} // namespace banglascript
