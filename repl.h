// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef REPL_H
#define REPL_H

#include<string>

namespace Oblivia{
    enum class Command{
        Null,
        Exit,
        Help,
        LiseVariables,
        ScopeUp,
        ScopeDown,
        Scope
    };
    Command toCommand(const std::string&a);
    void REPL();
    bool isCommand(const std::string&a);
}

#endif