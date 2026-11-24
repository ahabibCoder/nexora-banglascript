#pragma once
#include "ast/Declarations.hpp"
#include "common/Diagnostics.hpp"
#include <string>
#include <memory>

namespace banglascript {

class Driver {
public:
    explicit Driver(DiagnosticsEngine& diagnostics)
        : diagnostics_(diagnostics) {}

    bool parseString(const std::string& source, const std::string& filename = "<string>");
    bool parseFile(const std::string& filepath);

    Program* getAST() const { return ast_.get(); }
    ProgramPtr releaseAST() { return std::move(ast_); }
    void setAST(ProgramPtr ast) { ast_ = std::move(ast); }

    DiagnosticsEngine& getDiagnostics() { return diagnostics_; }
    const std::string& getFilename() const { return filename_; }
    const std::string& getSource() const { return source_; }

    void updatePosition(uint32_t lines, uint32_t cols);
    SourcePosition getCurrentPosition() const;

private:
    DiagnosticsEngine& diagnostics_;
    ProgramPtr ast_;
    std::string filename_{"<stdin>"};
    std::string source_;
    uint32_t currentLine_{1};
    uint32_t currentColumn_{1};
    size_t byteOffset_{0};
};

} // namespace banglascript
