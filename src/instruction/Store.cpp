#include "Store.h"

#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <expression/ExprBuilder.h>

#include "util/DebugUtil.h"

void Store::handle(Path* path, llvm::Instruction* instruction)
{
    llvm::StoreInst* st = static_cast<llvm::StoreInst*>(instruction);

    llvm::Value* target = st->getPointerOperand();
    llvm::Value* value = st->getValueOperand();

    /*if (DebugUtil::get().getDebugInfo(target)) // TODO
    {
        ExprBuilder builder(path);
        Expression* assignment = builder.build(value);
        path->storeIntoAlloc(target, assignment);
    }*/
}
