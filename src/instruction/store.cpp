#include "store.h"

#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <expression/ExprBuilder.h>

#include "program/function.h"
#include "util/debug_util.h"

void Store::handle(Function* function, llvm::Instruction* instruction)
{
    /*llvm::StoreInst* st = static_cast<llvm::StoreInst*>(instruction);
    Path* path = function->getActivePath();

    llvm::Value* target = st->getPointerOperand();
    llvm::Value* value = st->getValueOperand();

    if (DebugUtil::get().getDebugInfo(target)) // TODO
    {
        ExprBuilder builder(path);
        Expression* assignment = builder.build(value);
        path->storeIntoAlloc(target, assignment);
    }*/
}
