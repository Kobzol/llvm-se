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

    virtual z3::expr createConstraint(Path* path) override;

    virtual void markAddresses(ExprTracker* tracker) const override;

    virtual bool isMemoryLocation() const override;

    virtual std::unique_ptr<Expression> clone() override = 0;

    virtual void dump(int priority = 0, int indent = 0) override;
    virtual std::string getIdentifier() = 0;

protected:
    z3::expr createConstExpr(Path* path);

private:
    Expression* content;
    uint64_t count;
};