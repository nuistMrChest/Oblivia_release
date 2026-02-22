// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef RELP_H
#define RELP_H

#include<string>

namespace Oblivia{
    enum class Command{
        Null,
        Exit,
        Help
    };
    Command toCommand(const std::string&a);
    void RELP();
    bool isCommand(const std::string&a);
}

#endif