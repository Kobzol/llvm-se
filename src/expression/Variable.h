#pragma once

#include <string>

#include "MemoryLocation.h"

class Variable : public MemoryLocation
{
public:
    Variable(llvm::Value* value, uint64_t count);
    Variable(llvm::Value* value, uint64_t count, Expression* content);

    virtual std::string getIdentifier() override;
    void setIdentifier(std::string identifier);

private:
    std::string identifier;
};