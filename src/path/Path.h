#pragma once

#include <memory>

#include "state/ISymbolicState.h"

#include "program/Function.h"
#include "solver/Solver.h"
#include "state/StateWrapper.h"

namespace llvm {
    class Instruction;
}

class PathGroup;

class Path
{
public:
    Path(std::vector<ISymbolicState*> parentStates, PathGroup* pathGroup, llvm::Instruction* start);
    Path(std::vector<ISymbolicState*> parentStates, std::unique_ptr<ISymbolicState> localState,
         PathGroup* pathGroup, llvm::Instruction* start);

    bool isFinished() const;
    z3::context& getContext();
    StateWrapper* getState() const;
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

    void mergeGlobalsTo(Path* path);

private:
    static z3::context CTX;

    bool finished = false;
    llvm::Instruction* instruction;
    PathGroup* pathGroup;
    Expression* returnValue;

    std::vector<Expression*> pathConditions;
    std::unique_ptr<ISymbolicState> localState;
    std::unique_ptr<StateWrapper> state;
};
