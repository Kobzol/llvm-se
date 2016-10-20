#pragma once

#include "catch.hpp"

#include "Context.h"

extern Context CTX;
extern std::unique_ptr<llvm::Module> moduleHolder;

void handleCode(const std::string& code);