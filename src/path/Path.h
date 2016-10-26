#pragma once

#include <memory>

#include "ISymbolicState.h"

#include "program/Function.h"
#include "solver/Solver.h"

namespace llvm {
    class Instruction;
}

class PathGroup;

class Path
{
public:
    Path(ISymbolicState* parentState, PathGroup* pathGroup, llvm::Instruction* start);

    bool isFinished() const;
    z3::context& getContext();
    ISymbolicState* getState() const;
    PathGroup* getGroup() const;

    std::unique_ptr<Solver> createSolver();

    void setFinished(Expression* value);
    Expression* getReturnValue() const;

    void moveToNextInstruction();
    void jumpTo(llvm::Instruction* instruction);
    void executeInstruction();
    llvm::Instruction* getInstruction() const;

    void dump(int priority);

    void addCondition(Expression* condition);
    void setConditions(Solver& solver);

    std::unique_ptr<Path> clone();

private:
    static z3::context CTX;

    bool finished = false;
    llvm::Instruction* instruction;
    PathGroup* pathGroup;
    Expression* returnValue;

    std::vector<Expression*> pathConditions;
    std::unique_ptr<ISymbolicState> state;
    std::unique_ptr<ISymbolicState> localState;
};
