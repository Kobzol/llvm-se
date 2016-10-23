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
    MemoryLocation* source = static_cast<MemoryLocation*>(state->getExpr(sourceAddr));

    UndefinedLoadChecker undefChecker;
    undefChecker.check(load, path);

    NullPointerChecker nullChecker;
    nullChecker.check(load, path);

    state->addExpr(load, source->getContent());

    path->moveToNextInstruction();
}
