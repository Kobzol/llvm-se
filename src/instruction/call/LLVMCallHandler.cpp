#include "LLVMCallHandler.h"

#include <string>
#include <llvm/IR/Instructions.h>

bool LLVMCallHandler::shouldHandle(const CallInfo& info) const
{
    return info.getName().find("llvm.") == 0;
}
