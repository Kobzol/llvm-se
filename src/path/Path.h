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
    Path(ISymbolicState* parentState, Function* function, PathGroup* pathGroup);
    Path(ISymbolicState* parentState, Function* function, PathGroup* pathGroup, llvm::Instruction* start);

    bool isFinished() const;
    z3::context& getContext();
    ISymbolicState* getState() const;

    std::unique_ptr<Solver> createSolver();

    llvm::Instruction* advance();

    void dump(int priority);

private:
    static z3::context CTX;

    bool finished = false;
    Function* function;
    llvm::Instruction* instruction;
    PathGroup* pathGroup;

    std::unique_ptr<ISymbolicState> state;
    std::unique_ptr<ISymbolicState> localState;
};
