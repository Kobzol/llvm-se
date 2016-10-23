#pragma once

#include "MemoryLocation.h"

class LoadExpression : public MemoryLocation
{
public:
    LoadExpression(llvm::Value* value, MemoryLocation* source);

    virtual bool isLoad() const override;
    MemoryLocation* getSource() const;

    virtual void dump(int priority) override;

    virtual z3::expr createConstraint(Path* path) override;
    virtual std::string getIdentifier() const override;

private:
    MemoryLocation* source;
};