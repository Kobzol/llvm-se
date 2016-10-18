#include "debug_util.h"

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/DebugInfoMetadata.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IntrinsicInst.h>

#include "program/function.h"

DebugUtil::DebugUtil()
{

}

DebugInfo* DebugUtil::getDebugInfo(llvm::Value* inst)
{
    return this->getFromCache(inst);
}

const llvm::MDNode* DebugUtil::findVarInFunction(const llvm::Function* function, const llvm::Value* value)
{
    for (auto& block : function->getBasicBlockList())
    {
        for (auto& inst : block.getInstList())
        {
            if (const llvm::DbgDeclareInst* DbgDeclare = llvm::dyn_cast<llvm::DbgDeclareInst>(&inst))
            {
                if (DbgDeclare->getAddress() == value)
                {
                    return DbgDeclare->getVariable();
                }
            }
            else if (const llvm::DbgValueInst* DbgValue = llvm::dyn_cast<llvm::DbgValueInst>(&inst))
            {
                if (DbgValue->getValue() == value)
                {
                    return DbgValue->getVariable();
                }
            }
        }
    }

    return nullptr;
}

const llvm::Function* DebugUtil::findVarScope(const llvm::Value* value)
{
    if (const llvm::Argument* Arg = llvm::dyn_cast<llvm::Argument>(value))
    {
        return Arg->getParent();
    }
    if (const llvm::Instruction* I = llvm::dyn_cast<llvm::Instruction>(value))
    {
        return I->getParent()->getParent();
    }

    return nullptr;
}

std::unique_ptr<DebugInfo> DebugUtil::getVarDebugInfo(const llvm::Value* value)
{
    // TODO handle globals as well
    const llvm::Function* function = this->findVarScope(value);
    if (!function)
    {
        return std::make_unique<DebugInfo>(value->getName().str());
    }

    const llvm::MDNode* debugVar = this->findVarInFunction(function, value);
    if (!debugVar)
    {
        return std::make_unique<DebugInfo>();
    }

    return std::make_unique<DebugInfo>(static_cast<const llvm::DIVariable*>(debugVar));
}

DebugInfo* DebugUtil::getFromCache(const llvm::Value* value)
{
    if (!this->debugCache.count(value))
    {
        this->debugCache[value] = this->getVarDebugInfo(value);
    }

    return this->debugCache.at(value).get();
}
