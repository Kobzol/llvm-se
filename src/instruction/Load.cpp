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

    MemoryLocation* source = static_cast<MemoryLocation*>(path->getState()->getExpr(sourceAddr));

    UndefinedLoadChecker undefChecker;
    undefChecker.check(load, path);

    NullPointerChecker nullChecker;
    nullChecker.check(load, path);

    if (!source->isUndefined() && source->isLoad())
    {
        source = static_cast<MemoryLocation*>(static_cast<LoadExpression*>(source)->getSource()->getContent());
    }

    path->getState()->addExpr(load, new LoadExpression(load, source));

    path->moveToNextInstruction();
}
