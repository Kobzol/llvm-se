#pragma once

#include <string>

struct DebugInfo;

enum class CheckErrorType
{
    NullPointerDereference = 0,
    OutOfBoundsAccess = 1,
    UndefinedLoad = 2,
    SEMark = 10
};

class CheckError
{
public:
    CheckError(CheckErrorType type, std::string location);
    virtual ~CheckError();

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

class SEMarkError : public CheckError
{
public:
    SEMarkError(CheckErrorType type, std::string location, int64_t id = 0);

    int64_t getId() const;

    virtual void dump(int priority) const;

private:
    int64_t id;
};