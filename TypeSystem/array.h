// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef ARRAY_H
#define ARRAY_H

#include"value.h"
#include<vector>
#include<memory>
#include<variant>
#include"variable.h"
#include"number.h"

namespace Oblivia{
    class Array;
    class Object;
    class String;

    class ArrayElement:public Calculatable{
        private:
        const size_t index;
        const Array*father;
        public:
        Type type;
        Type getType()const;
        ValueType as;
        ArrayElement();
        ArrayElement(const Array&f,size_t i);
        ArrayElement(const Array&f,size_t i,const Number&a);
        ArrayElement(const Array&f,size_t i,const std::shared_ptr<Array>&a);
        ArrayElement(const Array&f,size_t i,const std::shared_ptr<Object>&a);
        ArrayElement(const Array&f,size_t i,const std::shared_ptr<String>&a);
        ArrayElement&operator=(const ArrayElement&a);
        Number operator==(const ArrayElement&a)const;
        Number&getNumber();
        const Number&getConstNumber()const;
        friend std::ostream&operator<<(std::ostream&os,const ArrayElement&a);
    };

    class Array:public Value{
        private:
        std::vector<std::shared_ptr<ArrayElement>>array;
        public:
        Array();
        Array(int length);
        Array(const Array&a);
        Array&operator=(const Array&a);
        int getLength();
        ArrayElement&visitValue(size_t index);
        Number operator==(const Array&a)const;
        void print(std::ostream&os)const;
    };
}

#endif