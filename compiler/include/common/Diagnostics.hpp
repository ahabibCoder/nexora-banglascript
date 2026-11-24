#pragma once
#include "common/Position.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace banglascript {

enum class DiagnosticLevel {
    Note,
    Warning,
    Error,
    Fatal
};

struct Diagnostic {
    DiagnosticLevel level{DiagnosticLevel::Error};
    SourceSpan span;
    std::string message;
    std::string sourceLineSnippet;

    Diagnostic(DiagnosticLevel lvl, SourceSpan sp, std::string msg, std::string snippet = "")
        : level(lvl), span(std::move(sp)), message(std::move(msg)), sourceLineSnippet(std::move(snippet)) {}
};

class DiagnosticsEngine {
public:
    DiagnosticsEngine() = default;

    void report(DiagnosticLevel level, const SourceSpan& span, const std::string& message, const std::string& snippet = "") {
        diagnostics_.emplace_back(level, span, message, snippet);
        if (level == DiagnosticLevel::Error || level == DiagnosticLevel::Fatal) {
            errorCount_++;
        } else if (level == DiagnosticLevel::Warning) {
            warningCount_++;
        }
    }

    void error(const SourceSpan& span, const std::string& message, const std::string& snippet = "") {
        report(DiagnosticLevel::Error, span, message, snippet);
    }

    void warning(const SourceSpan& span, const std::string& message, const std::string& snippet = "") {
        report(DiagnosticLevel::Warning, span, message, snippet);
    }

    void note(const SourceSpan& span, const std::string& message, const std::string& snippet = "") {
        report(DiagnosticLevel::Note, span, message, snippet);
    }

    bool hasErrors() const { return errorCount_ > 0; }
    size_t errorCount() const { return errorCount_; }
    size_t warningCount() const { return warningCount_; }
    const std::vector<Diagnostic>& getDiagnostics() const { return diagnostics_; }

    void clear() {
        diagnostics_.clear();
        errorCount_ = 0;
        warningCount_ = 0;
    }

    void printAll(std::ostream& out, bool colorize = true) const {
        for (const auto& diag : diagnostics_) {
            printDiagnostic(out, diag, colorize);
        }
    }

private:
    std::vector<Diagnostic> diagnostics_;
    size_t errorCount_{0};
    size_t warningCount_{0};

    static void printDiagnostic(std::ostream& out, const Diagnostic& diag, bool colorize) {
        // ANSI escape codes
        const std::string red = colorize ? "\033[1;31m" : "";
        const std::string yellow = colorize ? "\033[1;33m" : "";
        const std::string cyan = colorize ? "\033[1;36m" : "";
        const std::string bold = colorize ? "\033[1m" : "";
        const std::string reset = colorize ? "\033[0m" : "";

        std::string levelStr;
        switch (diag.level) {
            case DiagnosticLevel::Fatal:
            case DiagnosticLevel::Error:
                levelStr = red + "error" + reset;
                break;
            case DiagnosticLevel::Warning:
                levelStr = yellow + "warning" + reset;
                break;
            case DiagnosticLevel::Note:
                levelStr = cyan + "note" + reset;
                break;
        }

        out << bold << diag.span.start.toString() << ": " << reset
            << levelStr << bold << ": " << diag.message << reset << "\n";

        if (!diag.sourceLineSnippet.empty()) {
            std::string lineNumStr = std::to_string(diag.span.start.line);
            std::string padding(lineNumStr.length() + 1, ' ');
            out << cyan << lineNumStr << " | " << reset << diag.sourceLineSnippet << "\n";
            out << cyan << padding << "| " << reset;
            
            // Caret indicator
            uint32_t col = diag.span.start.column > 0 ? diag.span.start.column - 1 : 0;
            for (uint32_t i = 0; i < col; ++i) {
                out << (diag.sourceLineSnippet[i] == '\t' ? '\t' : ' ');
            }
            out << (diag.level == DiagnosticLevel::Warning ? yellow : red) << "^" << reset << "\n";
        }
    }
};

} // namespace banglascript
