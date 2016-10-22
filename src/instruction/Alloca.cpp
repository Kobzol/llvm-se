#include "Alloca.h"

#include <llvm/IR/Instructions.h>

#include "util/DebugUtil.h"
#include "expression/Variable.h"
#include "path/Path.h"
#include "expression/ExprBuilder.h"


void Alloca::handle(Path* path, llvm::Instruction* instruction)
{
    llvm::AllocaInst* alloc = static_cast<llvm::AllocaInst*>(instruction);
    ExprBuilder builder(path->getState());
    builder.createVariable(alloc);

    path->moveToNextInstruction();
}
