#pragma once

#include "CallHandler.h"

class LLVMCallHandler : public CallHandler
{
public:
    virtual bool shouldHandle(const CallInfo& info) const override;
};
