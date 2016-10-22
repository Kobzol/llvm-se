#pragma once

#include <z3++.h>

class MemoryLocation;
class Path;

class Solver
{
public:
    Solver(z3::context* ctx, Path* path);
    Solver(const Solver& other);

    Solver& operator=(const Solver& other);

    z3::solver copySolver(const z3::solver& solver);

    void addConstraint(const z3::expr& e);
    void addMemLoc(MemoryLocation* memLoc);

    bool isSatisfiable();
    bool isSatisfiable(const z3::expr& e);

    z3::context& getContext();

    void dump(int priority);

private:
    z3::context* ctx;
    Path* path;
    z3::solver solver;
};