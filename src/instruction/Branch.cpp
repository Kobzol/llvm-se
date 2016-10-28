#include "Branch.h"

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Constants.h>
#include <cassert>

#include "expression/ExprBuilder.h"
#include "expression/Expression.h"
#include "path/Path.h"
#include "path/PathGroup.h"

static std::vector<std::unique_ptr<llvm::CmpInst>> cmpStorage;

void Branch::handle(Path* path, llvm::Instruction* instruction)
{
    llvm::BranchInst* branch = static_cast<llvm::BranchInst*>(instruction);

    if (branch->isConditional())
    {
        llvm::CmpInst* condition = llvm::dyn_cast<llvm::CmpInst>(branch->getCondition());
        assert(condition);

        std::unique_ptr<llvm::CmpInst> conditionReverse = std::unique_ptr<llvm::CmpInst>(llvm::CmpInst::Create(
                condition->getOpcode(),
                condition->getInversePredicate(),
                condition->getOperand(0),
                condition->getOperand(1)
        ));

        ExprBuilder builder(path->getState());
        std::vector<Expression*> conditions = {
                builder.build(condition),
                builder.build(conditionReverse.get())
        };
        std::vector<bool> targets = {
                this->checkSatisfiability(path, conditions[0]),
                this->checkSatisfiability(path, conditions[1])
        };

        if (targets[0] && targets[1])
        {
            path->getGroup()->forkPath(path, conditions[0], this->getFirstInstruction(branch->getSuccessor(0)));
            targets[0] = false;
        }
        else if (!targets[0] && !targets[1])
        {
            assert(0); // unreachable code
        }

        for (unsigned int i = 0; i < 2; i++)
        {
            if (targets.at(i))
            {
                path->addCondition(conditions[i]);
                path->jumpTo(this->getFirstInstruction(branch->getSuccessor(i)));
                break;
            }
        }

        cmpStorage.push_back(std::move(conditionReverse));  // TODO
    }
    else
    {
        path->jumpTo(this->getFirstInstruction(branch->getSuccessor(0)));
    }
}

llvm::Instruction* Branch::getFirstInstruction(llvm::BasicBlock* block)
{
    for (llvm::Instruction& inst : block->getInstList())
    {
        return &inst;
    }

    assert(0);

    return nullptr;
}

bool Branch::checkSatisfiability(Path* path, Expression* condition)
{
    std::unique_ptr<Solver> solver = path->createSolver();
    solver->addConstraint(condition->createConstraint(path));

    path->setConditions(*solver);
    // TODO

    return solver->isSatisfiable();
}
