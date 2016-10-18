#include "ExprBuilder.h"

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Constants.h>

#include "IntConstant.h"
#include "UnknownExpression.h"
#include "AddExpression.h"
#include "path.h"
#include "LoadExpression.h"
#include "util/logger.h"
#include "CmpExpression.h"

ExprBuilder::ExprBuilder(Path* path): path(path)
{

}

Expression* ExprBuilder::build(llvm::Value* value)
{
    if (this->path->hasExpr(value))
    {
        return this->path->getExpr(value);
    }

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

Expression* ExprBuilder::buildConstant(llvm::Constant* constant)
{
    if (auto* intConstant = llvm::dyn_cast<llvm::ConstantInt>(constant))
    {
        return this->add(new IntConstant(constant, this->createIntConstant(intConstant)));
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
        Logger::get().line("Load");
        llvm::Value* loadExpr = load->getPointerOperand();
        if (this->path->hasAlloc(loadExpr))
        {
            return this->add(new LoadExpression(instruction, this->path->getAlloc(loadExpr)));
        }
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
    if (!this->path->hasExpr(addr))
    {
        this->path->addExpr(addr, expression);
    }

    return expression;
}
