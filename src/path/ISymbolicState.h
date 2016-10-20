#pragma once

namespace llvm {
    class Value;
}

class Expression;
class MemoryLocation;

class ISymbolicState
{
public:
    virtual bool hasMemoryLoc(llvm::Value* address) const = 0;
    virtual MemoryLocation* getMemoryLoc(llvm::Value* address) const = 0;
    virtual void addMemoryLoc(llvm::Value* address, MemoryLocation* memoryLocation) = 0;

    virtual bool hasExpr(llvm::Value* address) const = 0;
    virtual Expression* getExpr(llvm::Value* address) const = 0;
    virtual void addExpr(llvm::Value* address, Expression* expression) = 0;

    virtual void dump(int priority) = 0;
};
