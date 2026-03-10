// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include"../Tokenize/tokenize.h"
#include"../TypeSystem/type_system.h"
#include<vector>
#include <iostream>

namespace Oblivia{
    bool isExpression(const Tokens&a);
    ValueType getValueType(const Token&a,size_t level);
    ValueType&getValueTypeRef(Token&a,size_t level);
    Type getType(const Token&a,size_t level);
    Type&getTypeRef(Token&a,size_t level);
    ValueType getTrueValueType(const Token&a,size_t level);
    ValueType&getTrueValueTypeRef(Token&a,size_t level);
    Type getTrueType(const Token&a,size_t level);
    Type&getTrueTypeRef(Token&a,size_t level);
    String getString(const Token&a,size_t level);
    class Expression{
        private:
        Tokens t;
        bool need_calculatable;
        public:
        Token v;
        size_t scope_level;
        Expression(const Tokens&a,size_t l);

        Expression();
        Expression(const Expression&a);

        const Expression&operator=(const Expression&a);

        Situation calculate();
        friend std::ostream&operator<<(std::ostream&os,const Expression&a);

        Situation getBool(bool&res);
    };
}

#endif
