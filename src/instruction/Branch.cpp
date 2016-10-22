#include "Branch.h"

#include <llvm/IR/Instructions.h>

#include "expression/ExprBuilder.h"
#include "expression/Expression.h"
#include "path/Path.h"

void Branch::handle(Path* path, llvm::Instruction* instruction)
{
    llvm::BranchInst* branch = static_cast<llvm::BranchInst*>(instruction);

    if (branch->isConditional())
    {
        ExprBuilder builder(path->getState());
        Expression* condition = builder.build(branch->getCondition());
        std::unique_ptr<Solver> solver = path->createSolver();
        solver->addConstraint(condition->createConstraint(path));

        if (solver->isSatisfiable())
        {

        }
    }
    else
    {
        llvm::BasicBlock* jumpTarget = static_cast<llvm::BasicBlock*>(branch->getOperand(0));
        path->jumpTo(this->getFirstInstruction(jumpTarget));
    }
}

llvm::Instruction* Branch::getFirstInstruction(llvm::BasicBlock* block)
{
    for (llvm::Instruction& inst : block->getInstList())
    {
        return &inst;
    }
}
