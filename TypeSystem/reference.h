// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef REFERENCE_H
#define REFERENCE_H

#include"value.h"
#include<iostream>
#include"number.h"

namespace Oblivia{
    struct ValueType;
    class Number;
    class Reference:public Value,public Calculatable{
        public:
        ValueType*ref;
        Type ref_type;
        bool refed;

        void print(std::ostream&os)const;
        Reference();
        Reference(ValueType&v,Type t);
        Reference(const Reference&a);
        Reference&operator=(const Reference&a);
        Number operator==(const Reference&a)const;
        Number&getNumber();
        const Number&getConstNumber()const;
        ~Reference();
    };
}

#endif