#pragma once

#include <memory>

namespace llvm {
    class Constant;
    class Instruction;
    class BinaryOperator;
    class CmpInst;
    class ConstantInt;
}

#include "expression/Expression.h"

class Path;

class ExprBuilder
{
public:
    ExprBuilder(Path* path);

    Expression* build(llvm::Value* value);

private:
    Expression* buildConstant(llvm::Constant* constant);
    Expression* buildInstruction(llvm::Instruction* instruction);
    Expression* buildBinaryOperator(llvm::BinaryOperator* oper);
    Expression* buildCmp(llvm::CmpInst* cmp);

    int64_t createIntConstant(llvm::ConstantInt* intConstant);

    Expression* add(Expression* expression);

    Path* path;
};