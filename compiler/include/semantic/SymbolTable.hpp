#pragma once
#include "semantic/Symbol.hpp"
#include <unordered_map>
#include <vector>
#include <memory>
#include <optional>
#include <iostream>

namespace banglascript {

class Scope {
public:
    explicit Scope(uint32_t level, std::shared_ptr<Scope> parent = nullptr)
        : level_(level), parent_(parent) {}

    uint32_t getLevel() const { return level_; }
    std::shared_ptr<Scope> getParent() const { return parent_; }

    bool insert(const Symbol& sym) {
        if (symbols_.find(sym.name) != symbols_.end()) {
            return false; // Duplicate in current scope
        }
        symbols_[sym.name] = sym;
        orderedSymbols_.push_back(sym);
        return true;
    }

    void update(const Symbol& sym) {
        symbols_[sym.name] = sym;
        if (parent_) parent_->update(sym);
    }

    std::optional<Symbol> lookupCurrent(const std::string& name) const {
        auto it = symbols_.find(name);
        if (it != symbols_.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    std::optional<Symbol> lookup(const std::string& name) const {
        auto it = symbols_.find(name);
        if (it != symbols_.end()) {
            return it->second;
        }
        if (parent_) {
            return parent_->lookup(name);
        }
        return std::nullopt;
    }

    const std::vector<Symbol>& getOrderedSymbols() const { return orderedSymbols_; }

private:
    uint32_t level_;
    std::shared_ptr<Scope> parent_;
    std::unordered_map<std::string, Symbol> symbols_;
    std::vector<Symbol> orderedSymbols_;
};

class SymbolTable {
public:
    SymbolTable() {
        globalScope_ = std::make_shared<Scope>(0);
        currentScope_ = globalScope_;
        allScopes_.push_back(globalScope_);
    }

    void enterScope() {
        currentLevel_++;
        auto newScope = std::make_shared<Scope>(currentLevel_, currentScope_);
        currentScope_ = newScope;
        allScopes_.push_back(newScope);
    }

    void exitScope() {
        if (currentScope_->getParent()) {
            currentScope_ = currentScope_->getParent();
            currentLevel_--;
        }
    }

    bool insert(const Symbol& sym) {
        return currentScope_->insert(sym);
    }

    void update(const Symbol& sym) {
        currentScope_->update(sym);
    }

    std::optional<Symbol> lookup(const std::string& name) const {
        return currentScope_->lookup(name);
    }

    std::optional<Symbol> lookupCurrentScope(const std::string& name) const {
        return currentScope_->lookupCurrent(name);
    }

    uint32_t getCurrentLevel() const { return currentLevel_; }

    std::vector<Symbol> getAllSymbols() const {
        std::vector<Symbol> result;
        for (const auto& scope : allScopes_) {
            for (const auto& sym : scope->getOrderedSymbols()) {
                result.push_back(sym);
            }
        }
        return result;
    }

    void reset() {
        currentLevel_ = 0;
        allScopes_.clear();
        globalScope_ = std::make_shared<Scope>(0);
        currentScope_ = globalScope_;
        allScopes_.push_back(globalScope_);
    }

private:
    uint32_t currentLevel_{0};
    std::shared_ptr<Scope> globalScope_;
    std::shared_ptr<Scope> currentScope_;
    std::vector<std::shared_ptr<Scope>> allScopes_;
};

} // namespace banglascript
