#include "Branch.h"

#include <llvm/IR/Instructions.h>

#include "path/Path.h"
#include "expression/ExprBuilder.h"

void Branch::handle(Path* path, llvm::Instruction* instruction)
{
    llvm::BranchInst* branch = static_cast<llvm::BranchInst*>(instruction);
    /*Path* path = function->getActivePath();

    if (branch->isConditional())
    {
        ExprBuilder builder(path);
        Expression* condition = builder.build(branch->getCondition());
        std::unique_ptr<Solver> solver = path->createSolver();
        solver->addConstraint(condition->createConstraint(path));
        std::cerr << solver->isSatisfiable() << std::endl;
    }*/
}
