#include "Load.h"

#include <llvm/IR/Instructions.h>

#include "check/NullPointerChecker.h"
#include "check/UndefinedLoadChecker.h"
#include "expression/MemoryLocation.h"
#include "path/Path.h"

void Load::handle(Path* path, llvm::Instruction* instruction)
{
    llvm::LoadInst* load = static_cast<llvm::LoadInst*>(instruction);
    llvm::Value* sourceAddr = load->getPointerOperand();

    ISymbolicState* state = path->getState();
    MemoryLocation* source = state->getMemoryLoc(sourceAddr);

    llvm::Type* type = load->getType();

    UndefinedLoadChecker undefChecker;
    undefChecker.check(load, path);

    if (type->isPointerTy())
    {
        state->addMemoryLoc(load, source);
    }
    else
    {
        NullPointerChecker nullChecker;
        nullChecker.check(load, path);
        state->addExpr(load, source->getContent());
    }

    path->moveToNextInstruction();
}
