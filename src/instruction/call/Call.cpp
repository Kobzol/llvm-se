#include "Call.h"

#include <llvm/IR/Instructions.h>

#include "Context.h"
#include "LLVMCallHandler.h"
#include "path/Path.h"
#include "path/PathGroup.h"
#include "util/DebugUtil.h"
#include "SEMarkCallHandler.h"
#include "StandardCallHandler.h"

Call::Call()
{
    this->handlers.push_back(std::make_unique<LLVMCallHandler>());
    this->handlers.push_back(std::make_unique<SEMarkCallHandler>());
    this->handlers.push_back(std::make_unique<StandardCallHandler>());
}

void Call::handle(Path* path, llvm::Instruction* instruction)
{
    llvm::CallInst* call = static_cast<llvm::CallInst*>(instruction);
    std::string functionName = call->getCalledFunction()->getName().str();
    CallInfo info(path, call, functionName, path->getGroup()->getContext()->demangle(functionName));

    for (auto& handler : this->handlers)
    {
        if (handler->shouldHandle(info))
        {
            handler->handle(info);
            break;
        }
    }
}
