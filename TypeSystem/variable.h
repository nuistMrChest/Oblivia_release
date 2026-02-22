// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef VARIABLE_H
#define VARIABLE_H

#include"value.h"
#include<memory>
#include<string>
#include<unordered_map>
#include"number.h"
#include<variant>

namespace Oblivia{
    class Array;
    class Object;
    class String;

    struct ValueType{
        std::variant<Number,std::shared_ptr<Array>,std::shared_ptr<Object>,std::shared_ptr<String>>v;
        Number&Num();
        Array&Arr();
        Object&Obj();
        String&Str();

        const Number&Num()const;
        const Array&Arr()const;
        const Object&Obj()const;
        const String&Str()const;
    };

    struct VarKey{
        std::string name;
        size_t level;
        bool operator==(const VarKey&a)const;
        VarKey(const std::string&n,size_t l);
    };

    struct VarKeyHash{
        size_t operator()(const VarKey&a)const noexcept;
    };

    class Variable:public Calculatable{
        private:
        std::string name;
        int stack_level;
        public:
        Type type;
        ValueType as;
        static std::unordered_map<VarKey,Variable*,VarKeyHash>variables;
        Variable(int l,const std::string&n);
        Variable(int l,const std::string&n,const Number&v);
        Variable(int l,const std::string&n,const Array&v);
        Variable(int l,const std::string&n,const Object&v);
        Variable(int l,const std::string&n,const String&v);
        Number&getNumber();
        const Number&getConstNumber()const;
        Type getType()const;
    };
}

#endif
