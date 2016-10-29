#include "CallHandler.h"

#include "path/Path.h"

CallInfo::CallInfo(Path* path, llvm::CallInst* inst, std::string name, std::string demangledName)
    : path(path), inst(inst), name(name), demangledName(demangledName)
{

}

Path* CallInfo::getPath() const
{
    return path;
}

llvm::CallInst* CallInfo::getInst() const
{
    return inst;
}

const std::string& CallInfo::getName() const
{
    return name;
}

const std::string& CallInfo::getDemangledName() const
{
    return demangledName;
}

CallHandler::~CallHandler()
{

}

void CallHandler::handle(const CallInfo& info) const
{
    info.getPath()->moveToNextInstruction();
}
