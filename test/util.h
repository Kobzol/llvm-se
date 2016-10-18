#pragma once

#include "catch.hpp"

#include "context.h"

extern Context CTX;
extern std::unique_ptr<llvm::Module> moduleHolder;

void handleCode(std::string code);