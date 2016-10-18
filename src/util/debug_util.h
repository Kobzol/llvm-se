#pragma once

#include <iostream>
#include <unordered_map>

#include "singleton.h"
#include "debug_info.h"

namespace llvm {
    class Instruction;
    class Function;
    class MDNode;
    class Value;
    class DIVariable;
}

class DebugUtil : public Singleton<DebugUtil>
{
    friend class Singleton<DebugUtil>;

public:
    DebugInfo* getDebugInfo(llvm::Value* inst);

private:
    DebugUtil();

    const llvm::MDNode* findVarInFunction(const llvm::Function* function, const llvm::Value* value);
    const llvm::Function* findVarScope(const llvm::Value* value);
    std::unique_ptr<DebugInfo> getVarDebugInfo(const llvm::Value* value);

    DebugInfo* getFromCache(const llvm::Value* value);

    std::unordered_map<const llvm::Value*, std::unique_ptr<DebugInfo>> debugCache;
};