#include "Branch.h"

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Constants.h>

#include "expression/ExprBuilder.h"
#include "expression/Expression.h"
#include "path/Path.h"

void Branch::handle(Path* path, llvm::Instruction* instruction)
{
    llvm::BranchInst* branch = static_cast<llvm::BranchInst*>(instruction);

    if (branch->isConditional())
    {
        ExprBuilder builder(path->getState());
        Expression* trueCondition = builder.build(branch->getCondition());
        Expression* falseCondition = /*builder.build(
                llvm::CmpInst::Create(
                        llvm::Instruction::OtherOps::ICmp,
                        llvm::CmpInst::Predicate::ICMP_EQ,
                        branch->getCondition(),
                        llvm::ConstantInt::get(llvm::Type::getInt32Ty(instruction->getContext()), 0)
                )
        );*/trueCondition;

        std::vector<Expression*> conditions = { trueCondition, falseCondition };
        std::vector<bool> targets = {
                this->checkSatisfiability(path, trueCondition),
                this->checkSatisfiability(path, falseCondition)
        };

        if (targets[0])
        {
            path->jumpTo(this->getFirstInstruction(branch->getSuccessor(0)));
        }
        else path->jumpTo(this->getFirstInstruction(branch->getSuccessor(1)));
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

    assert(0);

    return nullptr;
}

bool Branch::checkSatisfiability(Path* path, Expression* condition)
{
    std::unique_ptr<Solver> solver = path->createSolver();
    solver->addConstraint(condition->createConstraint(path));

    path->getState()->setConstraints(path, *solver);

    return solver->isSatisfiable();
}
