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

    while (state->hasMemoryLoc(sourceAddr))
    {
        MemoryLocation* source = state->getMemoryLoc(sourceAddr);
        if (source->isUndefined())
        {
            DebugInfo* di = DebugUtil::get().getDebugInfo(source->getValue());
            path->getGroup()->getContext()->addError(UndefinedLoadError(di));
            break;
        }

        if (source->getContent()->isMemoryLocation())
        {
            sourceAddr = source->getContent()->getValue();
        }
        else break;
    }
}
