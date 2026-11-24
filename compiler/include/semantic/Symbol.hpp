#pragma once
#include "common/Types.hpp"
#include "common/Position.hpp"
#include <string>
#include <vector>

namespace banglascript {

enum class SymbolCategory {
    Variable,
    Function,
    Parameter
};

inline std::string symbolCategoryToString(SymbolCategory cat) {
    switch (cat) {
        case SymbolCategory::Variable:  return "Variable";
        case SymbolCategory::Function:  return "Function";
        case SymbolCategory::Parameter: return "Parameter";
    }
    return "Unknown";
}

struct Symbol {
    std::string name;
    DataType type{DataType::Unknown};
    SymbolCategory category{SymbolCategory::Variable};
    uint32_t scopeLevel{0};
    SourcePosition declaredPosition;
    
    // For function symbols:
    std::vector<DataType> parameterTypes;
    DataType returnType{DataType::Shunno};

    Symbol() = default;
    Symbol(std::string n, DataType t, SymbolCategory cat, uint32_t scope, SourcePosition pos)
        : name(std::move(n)), type(t), category(cat), scopeLevel(scope), declaredPosition(std::move(pos)) {}
};

} // namespace banglascript
