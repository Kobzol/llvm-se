#pragma once

#include <z3++.h>

class Solver
{
public:
    Solver(z3::context* ctx);
    Solver(const Solver& other);

    Solver& operator=(const Solver& other);

    z3::solver copySolver(const z3::solver& solver);

    void addConstraint(const z3::expr& e);

    bool isSatisfiable();
    bool isSatisfiable(const z3::expr& e);

private:
    z3::context& getContext();

    z3::context* ctx;
    z3::solver solver;
};