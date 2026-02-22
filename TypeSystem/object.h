// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef OBJECT_H
#define OBJECT_H

#include"value.h"
#include"number.h"
#include"variable.h"
#include<string>
#include<vector>
#include<memory>
#include<unordered_map>
#include<iostream>

namespace Oblivia{
    class Object;

    class Attribute:public Calculatable{
        private:
        const int index;
        const Object*father;
        public:
        Type type;
        const std::string name;
        Type getType()const;
        ValueType as;
        Attribute();
        Attribute(const std::string&n,const Object&f,int i);
        Attribute(const std::string&n,const Object&f,int i,const Number&a);
        Attribute(const std::string&n,const Object&f,int i,const std::shared_ptr<Array>&a);
        Attribute(const std::string&n,const Object&f,int i,const std::shared_ptr<Object>&a);
        Attribute(const std::string&n,const Object&f,int i,const std::shared_ptr<String>&a);
        Attribute&operator=(const Attribute&a);
        Number operator==(const Attribute&a)const;
        Number&getNumber();
        const Number&getConstNumber()const;
        friend std::ostream&operator<<(std::ostream&os,const Attribute&a);
    };

    class Object:public Value{
        private:
        std::vector<std::shared_ptr<Attribute>>attributes;
        public:
        std::unordered_map<std::string,int>getIndex;
        Object();
        Object(const Object&a);
        Attribute&visitAttribute(const std::string&name);
        void addAttribute(const std::string&name,const Number&a);
        void addAttribute(const std::string&name,const std::shared_ptr<Array>&a);
        void addAttribute(const std::string&name,const std::shared_ptr<Object>&a);
        void addAttribute(const std::string&name,const std::shared_ptr<String>&a);
        void print(std::ostream&os)const;
        Number operator==(const Object&a)const;
    };
}

#endif