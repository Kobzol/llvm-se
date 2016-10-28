#include "GetElementPtr.h"

#include <llvm/IR/Module.h>

#include "check/OutOfBoundsChecker.h"
#include "expression/ExprBuilder.h"
#include "expression/IndexExpression.h"
#include "program/Function.h"
#include "path/Path.h"

void GetElementPtr::handle(Path* path, llvm::Instruction* instruction)
{
    /*llvm::GetElementPtrInst* gep = static_cast<llvm::GetElementPtrInst*>(instruction);

    ISymbolicState* state = path->getState();
    int64_t constantIndex = 0;

    if (this->getConstantIndex(gep, &constantIndex))
    {
        llvm::Value* baseAddr = gep->getPointerOperand();
        MemoryLocation* base = static_cast<MemoryLocation*>(state->getExpr(baseAddr));
        assert(base->isMemoryLocation());
        IndexExpression* index = new IndexExpression(gep, base, constantIndex);

        OutOfBoundsChecker oobChecker;
        oobChecker.check(gep, base, constantIndex, path);

        state->addExpr(gep, index);
    }
    else
    {
        assert(0);
    }*/

    path->moveToNextInstruction();
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
