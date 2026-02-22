// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef STRING_H
#define STRING_H

#include"value.h"
#include"number.h"
#include<string>
#include<iostream>

namespace Oblivia{
    class String:public Value{
        private:
        std::string content;
        public:
        String();
        String(const std::string&s);
        String(const String&a);
        const std::string&getCont()const;
        void print(std::ostream&os)const;
        String operator+(const String&a)const;
        Number operator==(const String&a)const;
        String visitValue(size_t index);
        String&operator=(const String&a);
    };
}

#endif