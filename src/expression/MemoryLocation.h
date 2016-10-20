#pragma once

#include "Expression.h"

class MemoryLocation : public Expression
{
public:
    MemoryLocation(llvm::Value* value, Expression* content, uint64_t count);

    bool isUndefined() const;
    Expression* getContent() const;
    void setContent(Expression* content);

    virtual void dump(int priority) override;
    const std::string& getIdentifier() const;
    void setIdentifier(std::string identifier);
    bool hasIdentifier() const;

protected:
    z3::expr createConstExpr(Path* path);

private:
    Expression* content;
    std::string identifier;
    uint64_t count;
};