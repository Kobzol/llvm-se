#pragma once

#include "CallHandler.h"

class SEMarkCallHandler : public CallHandler
{
public:
    virtual bool shouldHandle(const CallInfo& info) const override;
    virtual void handle(const CallInfo& info) const override;
};
