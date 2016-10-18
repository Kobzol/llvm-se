#include "branch.h"

#include <llvm/IR/Instructions.h>

#include "path.h"
#include "program/function.h"
#include "expression/ExprBuilder.h"

void Branch::handle(Function* function, llvm::Instruction* instruction)
{
    llvm::BranchInst* branch = static_cast<llvm::BranchInst*>(instruction);
    Path* path = function->getActivePath();

    if (branch->isConditional())
    {
        ExprBuilder builder(path);
        Expression* condition = builder.build(branch->getCondition());
        std::unique_ptr<Solver> solver = path->createSolver();
        solver->addConstraint(condition->createConstraint(path));
        std::cerr << solver->isSatisfiable() << std::endl;
    }
}
