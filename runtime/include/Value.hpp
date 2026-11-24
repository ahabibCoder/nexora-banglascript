#pragma once
#include <variant>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace banglascript {

class RuntimeValue {
public:
    using ValueType = std::variant<std::monostate, int64_t, double, std::string, bool>;

    RuntimeValue() : value_(std::monostate{}) {}
    RuntimeValue(int64_t val) : value_(val) {}
    RuntimeValue(int val) : value_(static_cast<int64_t>(val)) {}
    RuntimeValue(double val) : value_(val) {}
    RuntimeValue(std::string val) : value_(std::move(val)) {}
    RuntimeValue(const char* val) : value_(std::string(val)) {}
    RuntimeValue(bool val) : value_(val) {}

    bool isNull() const { return std::holds_alternative<std::monostate>(value_); }
    bool isInt() const { return std::holds_alternative<int64_t>(value_); }
    bool isDouble() const { return std::holds_alternative<double>(value_); }
    bool isString() const { return std::holds_alternative<std::string>(value_); }
    bool isBool() const { return std::holds_alternative<bool>(value_); }
    bool isNumeric() const { return isInt() || isDouble(); }

    int64_t asInt() const {
        if (isInt()) return std::get<int64_t>(value_);
        if (isDouble()) return static_cast<int64_t>(std::get<double>(value_));
        if (isBool()) return std::get<bool>(value_) ? 1 : 0;
        throw std::runtime_error("Cannot convert value to integer");
    }

    double asDouble() const {
        if (isDouble()) return std::get<double>(value_);
        if (isInt()) return static_cast<double>(std::get<int64_t>(value_));
        if (isBool()) return std::get<bool>(value_) ? 1.0 : 0.0;
        throw std::runtime_error("Cannot convert value to double");
    }

    std::string asString() const {
        if (isString()) return std::get<std::string>(value_);
        return toString();
    }

    bool asBool() const {
        if (isBool()) return std::get<bool>(value_);
        if (isInt()) return std::get<int64_t>(value_) != 0;
        if (isDouble()) return std::get<double>(value_) != 0.0;
        if (isString()) return !std::get<std::string>(value_).empty();
        return false;
    }

    std::string toString() const {
        if (isNull()) return "shunno";
        if (isInt()) return std::to_string(std::get<int64_t>(value_));
        if (isDouble()) {
            std::ostringstream ss;
            ss << std::get<double>(value_);
            std::string s = ss.str();
            if (s.find('.') == std::string::npos) s += ".0";
            return s;
        }
        if (isString()) return std::get<std::string>(value_);
        if (isBool()) return std::get<bool>(value_) ? "true" : "false";
        return "";
    }

    // Arithmetic
    RuntimeValue operator+(const RuntimeValue& rhs) const {
        if (isString() || rhs.isString()) {
            return toString() + rhs.toString();
        }
        if (isDouble() || rhs.isDouble()) {
            return asDouble() + rhs.asDouble();
        }
        return asInt() + rhs.asInt();
    }

    RuntimeValue operator-(const RuntimeValue& rhs) const {
        if (isDouble() || rhs.isDouble()) {
            return asDouble() - rhs.asDouble();
        }
        return asInt() - rhs.asInt();
    }

    RuntimeValue operator*(const RuntimeValue& rhs) const {
        if (isDouble() || rhs.isDouble()) {
            return asDouble() * rhs.asDouble();
        }
        return asInt() * rhs.asInt();
    }

    RuntimeValue operator/(const RuntimeValue& rhs) const {
        if (isDouble() || rhs.isDouble()) {
            double divisor = rhs.asDouble();
            if (divisor == 0.0) throw std::runtime_error("Math Error: Division by zero");
            return asDouble() / divisor;
        }
        int64_t divisor = rhs.asInt();
        if (divisor == 0) throw std::runtime_error("Math Error: Division by zero");
        return asInt() / divisor;
    }

    RuntimeValue operator%(const RuntimeValue& rhs) const {
        int64_t divisor = rhs.asInt();
        if (divisor == 0) throw std::runtime_error("Math Error: Modulo by zero");
        return asInt() % divisor;
    }

    RuntimeValue operator-() const {
        if (isDouble()) return -asDouble();
        return -asInt();
    }

    RuntimeValue operator!() const {
        return !asBool();
    }

    // Relational
    bool operator==(const RuntimeValue& rhs) const {
        if (isNumeric() && rhs.isNumeric()) {
            if (isDouble() || rhs.isDouble()) return asDouble() == rhs.asDouble();
            return asInt() == rhs.asInt();
        }
        if (isString() && rhs.isString()) return asString() == rhs.asString();
        if (isBool() && rhs.isBool()) return asBool() == rhs.asBool();
        return false;
    }

    bool operator!=(const RuntimeValue& rhs) const { return !(*this == rhs); }

    bool operator<(const RuntimeValue& rhs) const {
        if (isDouble() || rhs.isDouble()) return asDouble() < rhs.asDouble();
        return asInt() < rhs.asInt();
    }

    bool operator<=(const RuntimeValue& rhs) const {
        if (isDouble() || rhs.isDouble()) return asDouble() <= rhs.asDouble();
        return asInt() <= rhs.asInt();
    }

    bool operator>(const RuntimeValue& rhs) const { return !(*this <= rhs); }
    bool operator>=(const RuntimeValue& rhs) const { return !(*this < rhs); }

private:
    ValueType value_;
};

} // namespace banglascript
