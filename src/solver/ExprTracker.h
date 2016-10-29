#pragma once

#include <unordered_set>

namespace llvm {
    class Value;
}

class ExprTracker
{
public:
    void addAddress(llvm::Value* address);
    const std::unordered_set<llvm::Value*>& getAddresses() const;

private:
    std::unordered_set<llvm::Value*> addresses;
};
