#pragma once

struct DebugInfo;

enum class CheckErrorType
{
    NullPointerDereference = 0,
    OutOfBoundsAccess = 1,
    UndefinedLoadChecker = 2
};

class CheckError
{
public:
    CheckError(CheckErrorType type);
    CheckError(CheckErrorType type, const DebugInfo* info);

    CheckErrorType getType() const;
    const DebugInfo* getDebugInfo() const;

private:
    CheckErrorType type;
    const DebugInfo* debugInfo = nullptr;
};

class NullDereferenceError : public CheckError
{
public:
    NullDereferenceError(const DebugInfo* info);
};

class OutOfBoundsError : public CheckError
{
public:
    OutOfBoundsError(const DebugInfo* info);
};

class UndefinedLoadError : public CheckError
{
public:
    UndefinedLoadError(const DebugInfo* info);
};
