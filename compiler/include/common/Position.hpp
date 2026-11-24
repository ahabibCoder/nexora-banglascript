#pragma once
#include <string>
#include <cstdint>
#include <iostream>

namespace banglascript {

/**
 * @brief Represents precise source coordinates in a .bs file.
 * Handles line, column (character index), and absolute byte offset.
 */
struct SourcePosition {
    std::string filename{"<stdin>"};
    uint32_t line{1};
    uint32_t column{1};
    size_t byteOffset{0};

    SourcePosition() = default;
    SourcePosition(std::string file, uint32_t l, uint32_t c, size_t offset = 0)
        : filename(std::move(file)), line(l), column(c), byteOffset(offset) {}

    std::string toString() const {
        return filename + ":" + std::to_string(line) + ":" + std::to_string(column);
    }
};

struct SourceSpan {
    SourcePosition start;
    SourcePosition end;

    SourceSpan() = default;
    SourceSpan(SourcePosition s, SourcePosition e) : start(std::move(s)), end(std::move(e)) {}
    explicit SourceSpan(SourcePosition pos) : start(pos), end(pos) {}
};

} // namespace banglascript
