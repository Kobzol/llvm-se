#pragma once

#include <string>

namespace llvm {
    class CallInst;
    class Instruction;
}

class Path;

class CallInfo
{
public:
    CallInfo(Path* path, llvm::CallInst* inst, std::string name, std::string demangledName);

    Path* getPath() const;
    llvm::CallInst* getInst() const;
    const std::string& getName() const;
    const std::string& getDemangledName() const;

private:
    Path* path;
    llvm::CallInst* inst;
    std::string name;
    std::string demangledName;
};

class CallHandler
{
public:
    virtual bool shouldHandle(const CallInfo& info) const = 0;
    virtual void handle(const CallInfo& info) const;
};
