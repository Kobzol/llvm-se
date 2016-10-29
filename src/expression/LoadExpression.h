#pragma once

#include "MemoryLocation.h"

class LoadExpression : public MemoryLocation
{
public:
    LoadExpression(llvm::Value* value, MemoryLocation* source);

    virtual bool isLoad() const override;
    MemoryLocation* getSource() const;

    virtual void dump(int priority = 0, int indent = 0) override;

    virtual z3::expr createConstraint(Path* path) override;
    virtual std::string getIdentifier() override;

    virtual std::unique_ptr<Expression> clone() override;
    virtual std::unique_ptr<Expression> deepClone(ISymbolicState* state) override;
};