#include "Load.h"

#include <llvm/IR/Instructions.h>

#include "check/NullPointerChecker.h"
#include "check/UndefinedLoadChecker.h"
#include "expression/LoadExpression.h"
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

    if (!source->isUndefined() && source->isLoad())
    {
        source = static_cast<MemoryLocation*>(static_cast<LoadExpression*>(source)->getSource()->getContent());
        //assert(source->isMemoryLocation());
    }

    state->addExpr(load, new LoadExpression(load, source));

    path->moveToNextInstruction();
}
