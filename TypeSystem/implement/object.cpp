// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../object.h"
#include"../value.h"
#include<string>
#include"../number.h"
#include"../array.h"
#include<memory>
#include<iostream>
#include"../string.h"

namespace Oblivia{
    Type Attribute::getType()const{
        return type;
    }

    Attribute::Attribute():index(-1),father(nullptr),name(""){
        type=Type::Number;
        as.v=Number(0);
        calculatable=true;
    }

    Attribute::Attribute(const std::string&n,const Object&f,int i):index(i),father(&f),name(n){
        type=Type::Number;
        as.v=Number(0);
        calculatable=true;
    }

    Attribute::Attribute(const std::string&n,const Object&f,int i,const Number&a):index(i),father(&f),name(n){
        type=Type::Number;
        as.v=a;
        calculatable=true;
    }

    Attribute::Attribute(const std::string&n,const Object&f,int i,const std::shared_ptr<Array>&a):index(i),father(&f),name(n){
        type=Type::Array;
        as.v=std::make_shared<Array>(*a);
        calculatable=false;
    }

    Attribute::Attribute(const std::string&n,const Object&f,int i,const std::shared_ptr<Object>&a):index(i),father(&f),name(n){
        type=Type::Object;
        as.v=std::make_shared<Object>(*a);
        calculatable=false;
    }

    Attribute::Attribute(const std::string&n,const Object&f,int i,const std::shared_ptr<String>&a):index(i),father(&f),name(n){
        type=Type::String;
        as.v=std::make_shared<String>(*a);
        calculatable=false;
    }

    Attribute&Attribute::operator=(const Attribute&a){
        this->type=a.type;
        this->as=a.as;
        this->calculatable=a.calculatable;
        return *this;
    }

    Number&Attribute::getNumber(){
        return this->as.Num();
    }

    const Number&Attribute::getConstNumber()const{
        return this->as.Num();
    }

    std::ostream&operator<<(std::ostream&os,const Attribute&a){
        os<<a.name<<" = ";
        switch(a.type){
            case Type::Number:os<<a.as.Num();break;
            case Type::Array:os<<a.as.Arr();break;
            case Type::Object:os<<a.as.Obj();break;
        }
        return os;
    }

    Object::Object(){
        type=Type::Object;
        attributes.resize(0);
    }

    Object::Object(const Object&a){
        type=Type::Object;
        attributes.resize(a.attributes.size());
        this->getIndex=a.getIndex;
        for(int i=0;i<a.attributes.size();i++){
            switch(a.attributes[i]->getType()){
                case Type::Number:this->attributes[i]=std::make_shared<Attribute>(a.attributes[i]->name,*this,i,a.attributes[i]->as.Num());break;
                case Type::Array:this->attributes[i]=std::make_shared<Attribute>(a.attributes[i]->name,*this,i,std::make_shared<Array>(a.attributes[i]->as.Arr()));break;
                case Type::Object:this->attributes[i]=std::make_shared<Attribute>(a.attributes[i]->name,*this,i,std::make_shared<Object>(a.attributes[i]->as.Obj()));break;
            }
        }
    }

    Attribute&Object::visitAttribute(const std::string&name){
        return *attributes[getIndex[name]];
    }

    void Object::addAttribute(const std::string&name,const Number&a){
        int index=attributes.size();
        attributes.push_back(std::make_shared<Attribute>(name,*this,index,a));
        getIndex[name]=index;
    }

    void Object::addAttribute(const std::string&name,const std::shared_ptr<Array>&a){
        int index=attributes.size();
        attributes.push_back(std::make_shared<Attribute>(name,*this,index,a));
        getIndex[name]=index;
    }

    void Object::addAttribute(const std::string&name,const std::shared_ptr<Object>&a){
        int index=attributes.size();
        attributes.push_back(std::make_shared<Attribute>(name,*this,index,a));
        getIndex[name]=index;
    }

    void Object::addAttribute(const std::string&name,const std::shared_ptr<String>&a){
        int index=attributes.size();
        attributes.push_back(std::make_shared<Attribute>(name,*this,index,a));
        getIndex[name]=index;
    }

    void Object::print(std::ostream&os)const{
        os<<"{ ";
        for(int i=0;i<attributes.size();i++){
            os<<*attributes[i]<<" ";
        }
        os<<"}";
    }

    Number Attribute::operator==(const Attribute&a)const{
        if(this->type!=a.type)return Number(0);
        switch(a.type){
            case Type::Number:return this->as.Num()==a.as.Num();
            case Type::Array:return this->as.Arr()==a.as.Arr();
            case Type::Object:return this->as.Obj()==a.as.Obj();
            default:return Number(0);
        }
        return Number(0);
    }

    Number Object::operator==(const Object&a)const{
        if(this->attributes.size()!=a.attributes.size())return Number(0);
        for(size_t i=0;i<a.attributes.size();i++){
            if(!(*(this->attributes[i])==*(a.attributes[i])))return Number(0);
        }
        return Number(1);
    }
}