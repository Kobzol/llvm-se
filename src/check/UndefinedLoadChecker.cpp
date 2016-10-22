#include "UndefinedLoadChecker.h"

#include <llvm/IR/Instructions.h>

#include "expression/MemoryLocation.h"
#include "path/ISymbolicState.h"
#include "path/Path.h"
#include "util/DebugInfo.h"
#include "util/DebugUtil.h"
#include "util/Logger.h"

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
            Logger::get().line(Logger::Prio::ERROR, "Undefined read of %", di->getName());
            break;
        }

        if (source->getContent()->isMemoryLocation())
        {
            sourceAddr = source->getContent()->getValue();
        }
        else break;
    }
}
