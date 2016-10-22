#include "NullPointerChecker.h"

#include <memory>
#include <llvm/IR/Instructions.h>

#include "path/Path.h"
#include "expression/IntConstant.h"
#include "expression/MemoryLocation.h"
#include "util/Logger.h"
#include "util/DebugInfo.h"
#include "util/DebugUtil.h"

void NullPointerChecker::check(llvm::LoadInst* load, Path* path)
{
    ISymbolicState* state = path->getState();
    llvm::Value* sourceAddr = load->getPointerOperand();

    MemoryLocation* source = state->getMemoryLoc(sourceAddr);

    if (source->isConstant())
    {
        IntConstant* constant = static_cast<IntConstant*>(source->getContent());
        if (constant->getConstant() == 0)
        {
            Logger::get().line(Logger::Prio::ERROR, "Null pointer dereference");
        }
    }
}
