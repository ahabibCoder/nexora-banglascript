#pragma once
#include <string>
#include <vector>

namespace banglascript {

class CommandLine {
public:
    static int run(int argc, char* argv[]);

private:
    static void printBanner();
    static void printHelp();
    static void printVersion();
    static int handleRun(const std::string& filepath);
    static int handleCheck(const std::string& filepath);
    static int handleCompile(const std::string& filepath, bool verbose = false);
    static int handleAST(const std::string& filepath);
    static int handleTAC(const std::string& filepath, bool optimized = false);
    static int handleInit(const std::string& projectName);
    static int handleDoctor();
    static int handleREPL();
};

} // namespace banglascript
