#pragma once

#include "CallHandler.h"

namespace llvm {
    class CallInst;
}

class StandardCallHandler : public CallHandler
{
public:
    virtual bool shouldHandle(const CallInfo& info) const override;

    virtual void handle(const CallInfo& info) const override;

    void addParameters(llvm::CallInst* call, Path* callingPath, Path* calledPath) const;
};
