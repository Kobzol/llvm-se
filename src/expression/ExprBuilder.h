#pragma once

#include <memory>
#include <llvm/IR/Instructions.h>

namespace llvm {
    class Constant;
    class Instruction;
    class BinaryOperator;
    class CmpInst;
    class ConstantInt;
    class Value;
}

class Expression;
class ISymbolicState;

class ExprBuilder
{
public:
    ExprBuilder(ISymbolicState* state);

    Expression* build(llvm::Value* value);

    void createVariable(llvm::AllocaInst* alloc);

private:
    Expression* buildConstant(llvm::Constant* constant);
    Expression* buildInstruction(llvm::Instruction* instruction);
    Expression* buildBinaryOperator(llvm::BinaryOperator* oper);
    Expression* buildCmp(llvm::CmpInst* cmp);

    int64_t createIntConstant(llvm::ConstantInt* intConstant);

    Expression* add(Expression* expression);

    ISymbolicState* state;
};