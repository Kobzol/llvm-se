#pragma once

#include <string>

struct DebugInfo;

enum class CheckErrorType
{
    NullPointerDereference = 0,
    OutOfBoundsAccess = 1,
    UndefinedLoad = 2
};

class CheckError
{
public:
    CheckError(CheckErrorType type, std::string location);

    std::string getLocation() const;

    CheckErrorType getType() const;
    virtual void dump(int priority) const;

private:
    CheckErrorType type;
    std::string location;
};

class NullDereferenceError : public CheckError
{
public:
    NullDereferenceError(std::string location);

    virtual void dump(int priority) const override;

private:
    std::string location;
};

class OutOfBoundsError : public CheckError
{
public:
    OutOfBoundsError(std::string location);

    virtual void dump(int priority) const override;
};

class UndefinedLoadError : public CheckError
{
public:
    UndefinedLoadError(std::string location);

    virtual void dump(int priority) const override;
};
