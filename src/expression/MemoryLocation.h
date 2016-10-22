#pragma once

#include "Expression.h"

class MemoryLocation : public Expression
{
public:
    MemoryLocation(llvm::Value* value, Expression* content, uint64_t count);

    bool isUndefined() const;
    Expression* getContent() const;
    virtual void setContent(Expression* content);

    uint64_t getCount() const;

    MemoryLocation* getOrigin();

    virtual z3::expr createConstraint(Path* path) override;
    virtual bool isMemoryLocation() const override;

    virtual void dump(int priority) override;
    virtual std::string getIdentifier() const = 0;

protected:
    z3::expr createConstExpr(Path* path);

private:
    Expression* content;
    uint64_t count;
};