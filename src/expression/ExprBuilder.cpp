#include "ExprBuilder.h"

#include <llvm/IR/Constants.h>

#include "IntConstant.h"
#include "UnknownExpression.h"
#include "AddExpression.h"
#include "path/Path.h"
#include "LoadExpression.h"
#include "util/Logger.h"
#include "util/DebugUtil.h"
#include "CmpExpression.h"
#include "Variable.h"

ExprBuilder::ExprBuilder(ISymbolicState* state) : state(state)
{

}

Expression* ExprBuilder::build(llvm::Value* value)
{
    if (value == nullptr) return nullptr;
    if (this->state->hasExpr(value)) return this->state->getExpr(value);
    if (this->state->hasExpr(value)) return this->state->getExpr(value);

    Logger::get().line("Building value %", value);

    if (auto* constant = llvm::dyn_cast<llvm::Constant>(value))
    {
        Logger::get().line("Constant");
        return this->buildConstant(constant);
    }
    else if (auto* inst = llvm::dyn_cast<llvm::Instruction>(value))
    {
        return this->buildInstruction(inst);
    }

    Logger::get().line("Unknown value");

    return this->add(new UnknownExpression(value));
}

void ExprBuilder::createVariable(llvm::AllocaInst* alloc)
{
    uint64_t size = 1;
    if (alloc->isArrayAllocation())
    {
        size = alloc->getAllocatedType()->getArrayNumElements();
    }

    Variable* var = new Variable(alloc, size);
    DebugInfo* di = DebugUtil::get().getDebugInfo(var->getValue());

    if (di->hasName())
    {
        var->setIdentifier(di->getName());
    }

    this->state->addExpr(alloc, var);
}

Expression* ExprBuilder::buildConstant(llvm::Constant* constant)
{
    constant = constant->stripPointerCasts();

    while (auto* constantPtr = llvm::dyn_cast<llvm::ConstantExpr>(constant))
    {
        assert(constantPtr->getNumOperands() == 1);
        constant = constantPtr->getOperand(0);
    }

    if (auto* intConstant = llvm::dyn_cast<llvm::ConstantInt>(constant))
    {
        return this->add(new IntConstant(constant, this->createIntConstant(intConstant)));
    }
    else if (llvm::isa<llvm::ConstantPointerNull>(constant))
    {
        return this->add(new IntConstant(constant, 0));
    }

    Logger::get().line("Unknown constant");

    return this->add(new UnknownExpression(constant));
}
Expression* ExprBuilder::buildInstruction(llvm::Instruction* instruction)
{
    if (auto* bin = llvm::dyn_cast<llvm::BinaryOperator>(instruction))
    {
        Logger::get().line("BinOp");
        return this->buildBinaryOperator(bin);
    }
    else if (auto* cmp = llvm::dyn_cast<llvm::CmpInst>(instruction))
    {
        Logger::get().line("Cmp");
        return this->buildCmp(cmp);
    }
    else if (auto* load = llvm::dyn_cast<llvm::LoadInst>(instruction))
    {
        assert(0);
        /*Logger::get().line("Load");
        llvm::Value* loadExpr = load->getPointerOperand();
        if (this->state->hasExpr(loadExpr))
        {
            return this->add(new LoadExpression(instruction, this->state->getExpr(loadExpr)));
        }*/
    }

    Logger::get().line(Logger::Prio::WARNING, "Unknown instruction %", instruction->getOpcodeName());

    return this->add(new UnknownExpression(instruction));
}
Expression* ExprBuilder::buildBinaryOperator(llvm::BinaryOperator* oper)
{
    llvm::Instruction::BinaryOps opcode = oper->getOpcode();

    switch (opcode)
    {
        case llvm::Instruction::BinaryOps::Add:
        {
            return this->add(new AddExpression(oper,
                                               this->build(oper->getOperand(0)),
                                               this->build(oper->getOperand(1))));
        }
    }

    Logger::get().line("Unknown binary op");

    return this->add(new UnknownExpression(oper));
}
Expression* ExprBuilder::buildCmp(llvm::CmpInst* cmp)
{
    llvm::Instruction::OtherOps opcode = cmp->getOpcode();

    switch (opcode)
    {
        case llvm::Instruction::OtherOps::ICmp:
        {
            return this->add(new CmpExpression(cmp,
                                               this->build(cmp->getOperand(0)),
                                               this->build(cmp->getOperand(1)),
                                               cmp->getPredicate()));
        }
    }

    Logger::get().line("Unknown cmp op");

    return this->add(new UnknownExpression(cmp));
}

int64_t ExprBuilder::createIntConstant(llvm::ConstantInt* intConstant)
{
    return intConstant->getSExtValue();
}

Expression* ExprBuilder::add(Expression* expression)
{
    llvm::Value* addr = expression->getValue();
    if (!this->state->hasExpr(addr))
    {
        this->state->addExpr(addr, expression);
    }

    return expression;
}
