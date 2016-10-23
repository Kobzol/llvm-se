#include "Call.h"

#include <llvm/IR/Instructions.h>

#include "Context.h"
#include "path/Path.h"
#include "path/PathGroup.h"
#include "util/DebugUtil.h"

void Call::handle(Path* path, llvm::Instruction* instruction)
{
    llvm::CallInst* call = static_cast<llvm::CallInst*>(instruction);

    std::string callName = call->getCalledFunction()->getName().str();
    if (callName.find("llvm.") == 0)
    {
        path->moveToNextInstruction();
        return;
    }

    if (path->getGroup()->getContext()->demangle(callName) == "se_mark()")
    {
        path->getGroup()->getContext()->addError(CheckError(CheckErrorType::SEMark,
                                                            DebugUtil::get().getInstructionLocation(call)));
    }

    path->moveToNextInstruction();
}
