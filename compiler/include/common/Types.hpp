#pragma once
#include <string>
#include <ostream>

namespace banglascript {

enum class DataType {
    Unknown,
    Sonkha,   // 64-bit signed integer
    Dosomik,  // 64-bit IEEE-754 float (double)
    Bakya,    // UTF-8 string
    Sotti,    // Boolean (true/false)
    Shunno    // Void / no return value
};

inline std::string dataTypeToString(DataType type) {
    switch (type) {
        case DataType::Sonkha:  return "sonkha";
        case DataType::Dosomik: return "dosomik";
        case DataType::Bakya:   return "bakya";
        case DataType::Sotti:   return "sotti";
        case DataType::Shunno:  return "shunno";
        default:                return "unknown";
    }
}

inline DataType stringToDataType(const std::string& name) {
    if (name == "sonkha" || name == "সংখ্যা") return DataType::Sonkha;
    if (name == "dosomik" || name == "দশমিক") return DataType::Dosomik;
    if (name == "bakya" || name == "বাক্য") return DataType::Bakya;
    if (name == "sotti" || name == "সত্যি") return DataType::Sotti;
    if (name == "shunno" || name == "শূন্য") return DataType::Shunno;
    return DataType::Unknown;
}

inline bool isNumericType(DataType t) {
    return t == DataType::Sonkha || t == DataType::Dosomik;
}

} // namespace banglascript
