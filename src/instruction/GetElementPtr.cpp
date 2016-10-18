#include "GetElementPtr.h"

#include <llvm/IR/Module.h>
#include <expression/ExprBuilder.h>

#include "expression/IndexExpression.h"
#include "program/function.h"

void GetElementPtr::handle(Function* function, llvm::Instruction* instruction)
{
    llvm::GetElementPtrInst* gep = static_cast<llvm::GetElementPtrInst*>(instruction);

    Path* path = function->getActivePath();
    ExprBuilder builder(path);

    std::shared_ptr<IndexExpression> index;
    int64_t constantIndex = 0;

    if (this->getConstantIndex(gep, &constantIndex))
    {
        index = std::make_shared<IndexExpression>(gep, gep->getPointerOperand(), constantIndex);
    }
    else
    {
        /*std::vector<std::shared_ptr<Expression>> indices;
        for (unsigned int i = 1; i < gep->getNumOperands(); i++)
        {
            llvm::Value* operand = gep->getOperand(i);
            indices.push_back(builder.build(operand));
        }

        index = std::make_shared<IndexExpression>(gep, gep->getPointerOperand(), indices);*/
    }

    path->setIndexer(index);
}

bool GetElementPtr::getConstantIndex(llvm::GetElementPtrInst* gep, int64_t* result)
{
    llvm::APInt apInt(64, 0, true);
    if (gep->accumulateConstantOffset(gep->getParent()->getParent()->getParent()->getDataLayout(), apInt))
    {
        *result = apInt.getSExtValue();
        return true;
    }

    return false;
}