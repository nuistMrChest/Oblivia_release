// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../string.h"
#include<iostream>

namespace Oblivia{
    String::String():content(""){
        type=Type::String;
    }

    String::String(const std::string&s):content(s){
        type=Type::String;
    }

    String::String(const String&a):content(a.getCont()){
        type=Type::String;
    }

    const std::string&String::getCont()const{
        return content;
    }

    void String::print(std::ostream&os)const{
        os<<content;
    }

    String String::operator+(const String&a)const{
        return String(this->content+a.content);
    }

    Number String::operator==(const String&a)const{
        if(this->content==a.content)return Number(1);
        return Number(0);
    }

    String String::visitValue(size_t index){
        std::string tmp;
        tmp=content[index];
        return String(tmp);
    }

    String&String::operator=(const String&a){
        this->content=a.content;
        this->type=a.type;
        return *this;
    }
}