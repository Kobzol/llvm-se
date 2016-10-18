#pragma once

#include <string>

#include <llvm/IR/Module.h>

#include "util/singleton.h"

class MemoryCompiler : public Singleton<MemoryCompiler>
{
    friend class Singleton<MemoryCompiler>;

public:
    std::unique_ptr<llvm::Module> compile(std::string code);

private:
    MemoryCompiler();
};