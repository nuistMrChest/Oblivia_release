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
#include"../reference.h"

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

    Attribute::Attribute(const std::string&n,const Object&f,int i,const std::unique_ptr<Array>&a):index(i),father(&f),name(n){
        type=Type::Array;
        as.v=std::make_unique<Array>(*a);
        calculatable=false;
    }

    Attribute::Attribute(const std::string&n,const Object&f,int i,const std::unique_ptr<Object>&a):index(i),father(&f),name(n){
        type=Type::Object;
        as.v=std::make_unique<Object>(*a);
        calculatable=false;
    }

    Attribute::Attribute(const std::string&n,const Object&f,int i,const std::unique_ptr<String>&a):index(i),father(&f),name(n){
        type=Type::String;
        as.v=std::make_unique<String>(*a);
        calculatable=false;
    }

    Attribute::Attribute(const std::string&n,const Object&f,int i,const std::unique_ptr<Reference>&a):index(i),father(&f),name(n){
        type=Type::Reference;
        as.v=std::make_unique<Reference>(*a);
        calculatable=a->calculatable;
    }

    Attribute&Attribute::operator=(const Attribute&a){
        this->type=a.type;
        this->as=a.as;
        this->calculatable=a.calculatable;
        return *this;
    }

    Number&Attribute::getNumber(){
        if(this->type==Type::Reference)return this->as.Ref().ref->Num();
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
            case Type::String:os<<a.as.Str();break;
            case Type::Reference:os<<a.as.Ref();break;
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
                case Type::Number:this->attributes[i]=std::make_unique<Attribute>(a.attributes[i]->name,*this,i,a.attributes[i]->as.Num());break;
                case Type::Array:this->attributes[i]=std::make_unique<Attribute>(a.attributes[i]->name,*this,i,std::make_unique<Array>(a.attributes[i]->as.Arr()));break;
                case Type::Object:this->attributes[i]=std::make_unique<Attribute>(a.attributes[i]->name,*this,i,std::make_unique<Object>(a.attributes[i]->as.Obj()));break;
                case Type::String:this->attributes[i]=std::make_unique<Attribute>(a.attributes[i]->name,*this,i,std::make_unique<String>(a.attributes[i]->as.Str()));break;
                case Type::Reference:this->attributes[i]=std::make_unique<Attribute>(a.attributes[i]->name,*this,i,std::make_unique<Reference>(a.attributes[i]->as.Ref()));break;
            }
        }
    }

    Object&Object::operator=(const Object&a){
        type=Type::Object;
        attributes.resize(a.attributes.size());
        this->getIndex=a.getIndex;
        for(int i=0;i<a.attributes.size();i++){
            switch(a.attributes[i]->getType()){
                case Type::Number:this->attributes[i]=std::make_unique<Attribute>(a.attributes[i]->name,*this,i,a.attributes[i]->as.Num());break;
                case Type::Array:this->attributes[i]=std::make_unique<Attribute>(a.attributes[i]->name,*this,i,std::make_unique<Array>(a.attributes[i]->as.Arr()));break;
                case Type::Object:this->attributes[i]=std::make_unique<Attribute>(a.attributes[i]->name,*this,i,std::make_unique<Object>(a.attributes[i]->as.Obj()));break;
                case Type::String:this->attributes[i]=std::make_unique<Attribute>(a.attributes[i]->name,*this,i,std::make_unique<String>(a.attributes[i]->as.Str()));break;
                case Type::Reference:this->attributes[i]=std::make_unique<Attribute>(a.attributes[i]->name,*this,i,std::make_unique<Reference>(a.attributes[i]->as.Ref()));break;
            }
        }
        return*this;
    }

    Attribute&Object::visitAttribute(const std::string&name){
        return *attributes[getIndex[name]];
    }

    void Object::addAttribute(const std::string&name){
        int index=attributes.size();
        attributes.push_back(std::make_unique<Attribute>(name,*this,index));
        getIndex[name]=index;
    }

    void Object::addAttribute(const std::string&name,const Number&a){
        int index=attributes.size();
        attributes.push_back(std::make_unique<Attribute>(name,*this,index,a));
        getIndex[name]=index;
    }

    void Object::addAttribute(const std::string&name,const std::unique_ptr<Array>&a){
        int index=attributes.size();
        attributes.push_back(std::make_unique<Attribute>(name,*this,index,a));
        getIndex[name]=index;
    }

    void Object::addAttribute(const std::string&name,const std::unique_ptr<Object>&a){
        int index=attributes.size();
        attributes.push_back(std::make_unique<Attribute>(name,*this,index,a));
        getIndex[name]=index;
    }

    void Object::addAttribute(const std::string&name,const std::unique_ptr<String>&a){
        int index=attributes.size();
        attributes.push_back(std::make_unique<Attribute>(name,*this,index,a));
        getIndex[name]=index;
    }

    void Object::addAttribute(const std::string&name,const std::unique_ptr<Reference>&a){
        int index=attributes.size();
        attributes.push_back(std::make_unique<Attribute>(name,*this,index,a));
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
            case Type::String:return this->as.Str()==a.as.Str();
            case Type::Reference:return this->as.Ref()==a.as.Ref();
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

    bool Object::attributeExist(const std::string&a){
        return getIndex.contains(a);
    }
}