#pragma once

#include "MemoryLocation.h"

class Variable : public MemoryLocation
{
public:
    Variable(llvm::Value* value, uint64_t count);
    Variable(llvm::Value* value, uint64_t count, Expression* content);

    virtual const std::string& getIdentifier() const override;
    void setIdentifier(std::string identifier);

private:
    std::string identifier;
};