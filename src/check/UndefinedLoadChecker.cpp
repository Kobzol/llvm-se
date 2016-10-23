#include "UndefinedLoadChecker.h"

#include <llvm/IR/Instructions.h>

#include "Context.h"
#include "path/Path.h"
#include "path/PathGroup.h"
#include "util/DebugInfo.h"
#include "util/DebugUtil.h"

void UndefinedLoadChecker::check(llvm::LoadInst* load, Path* path)
{
    llvm::Value* sourceAddr = load->getPointerOperand();
    ISymbolicState* state = path->getState();

    if (state->hasExpr(sourceAddr))
    {
        MemoryLocation* source = static_cast<MemoryLocation*>(state->getExpr(sourceAddr));
        if (source->isMemoryLocation() && source->isUndefined())
        {
            path->getGroup()->getContext()->addError(UndefinedLoadError(DebugUtil::get().getInstructionLocation(load)));
        }
    }
    else assert(0);
}
