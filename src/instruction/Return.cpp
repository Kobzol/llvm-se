#include "Return.h"

#include <llvm/IR/Instructions.h>

#include "expression/ExprBuilder.h"
#include "path/Path.h"

void Return::handle(Path* path, llvm::Instruction* instruction)
{
    llvm::ReturnInst* ret = static_cast<llvm::ReturnInst*>(instruction);
    llvm::Value* returnValue = ret->getReturnValue();

    ExprBuilder builder(path->getState());
    path->setFinished(builder.build(returnValue));
    path->moveToNextInstruction();
}
