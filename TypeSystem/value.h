// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef VALUE_H
#define VALUE_H

#include<iostream>

namespace Oblivia{
    enum class Type{
        Null,

        Number,
        Array,
        Function,
        Object,
        String,
        Refence
    };

    std::ostream&operator<<(std::ostream&os,const Type&a);

    class Value{
        protected:
        Type type;
        public:
        Type getType()const;
        virtual void print(std::ostream&os)const=0;
    };

    std::ostream&operator<<(std::ostream&os,const Value&a);
}

#endif