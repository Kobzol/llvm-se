#pragma once

#include "InstructionHandler.h"

namespace llvm {
    class BasicBlock;
    class Instruction;
}

class Expression;
class Path;
class Solver;

class Branch : public InstructionHandler
{
public:
    virtual void handle(Path* path, llvm::Instruction* instruction) override;

private:
    llvm::Instruction* getFirstInstruction(llvm::BasicBlock* block);
    bool checkSatisfiability(Path* path, Expression* expr);

    void setStateExpressions(Path& path, Solver& solver, Expression* condition) const;
};
