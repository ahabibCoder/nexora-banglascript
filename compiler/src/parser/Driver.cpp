#include "parser/Driver.hpp"
#include "parser.tab.hpp"
#include <fstream>
#include <sstream>

// Forward declarations for Flex reentrant functions
typedef void* yyscan_t;
extern int yylex_init(yyscan_t* scanner);
extern int yylex_destroy(yyscan_t scanner);
extern struct yy_buffer_state* yy_scan_string(const char* str, yyscan_t scanner);
extern void yy_delete_buffer(struct yy_buffer_state* buffer, yyscan_t scanner);
extern int yyparse(banglascript::Driver& driver, yyscan_t yyscanner);

namespace banglascript {

bool Driver::parseString(const std::string& source, const std::string& filename) {
    filename_ = filename;
    source_ = source;
    currentLine_ = 1;
    currentColumn_ = 1;
    byteOffset_ = 0;
    ast_ = std::make_unique<Program>(SourceSpan(SourcePosition(filename_, 1, 1)));

    yyscan_t scanner;
    if (yylex_init(&scanner) != 0) {
        diagnostics_.error(SourceSpan(SourcePosition(filename_, 1, 1)), "Failed to initialize lexical scanner");
        return false;
    }

    struct yy_buffer_state* buf = yy_scan_string(source.c_str(), scanner);
    int parseResult = yyparse(*this, scanner);
    yy_delete_buffer(buf, scanner);
    yylex_destroy(scanner);

    return (parseResult == 0) && !diagnostics_.hasErrors();
}

bool Driver::parseFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        diagnostics_.error(SourceSpan(SourcePosition(filepath, 1, 1)), "Could not open file: " + filepath);
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return parseString(buffer.str(), filepath);
}

void Driver::updatePosition(uint32_t lines, uint32_t cols) {
    if (lines > 0) {
        currentLine_ += lines;
        currentColumn_ = cols;
    } else {
        currentColumn_ += cols;
    }
}

SourcePosition Driver::getCurrentPosition() const {
    return SourcePosition(filename_, currentLine_, currentColumn_, byteOffset_);
}

} // namespace banglascript
