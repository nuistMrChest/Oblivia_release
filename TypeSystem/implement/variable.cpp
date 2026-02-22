// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../variable.h"
#include"../value.h"
#include<memory>
#include<string>
#include<unordered_map>
#include"../number.h"
#include"../array.h"
#include"../object.h"
#include<variant>
#include"../string.h"

namespace Oblivia{
    std::unordered_map<VarKey,Variable*,VarKeyHash>Variable::variables;

    Number&ValueType::Num(){
        return std::get<Number>(v);
    }

    Array&ValueType::Arr(){
        return *std::get<std::shared_ptr<Array>>(v);
    }

    Object&ValueType::Obj(){
        return *std::get<std::shared_ptr<Object>>(v);
    }

    String&ValueType::Str(){
        return *std::get<std::shared_ptr<String>>(v);
    }

    const Number&ValueType::Num()const{
        return std::get<Number>(v);
    }

    const Array&ValueType::Arr()const{
        return *std::get<std::shared_ptr<Array>>(v);
    }

    const Object&ValueType::Obj()const{
        return *std::get<std::shared_ptr<Object>>(v);
    }

    const String&ValueType::Str()const{
        return *std::get<std::shared_ptr<String>>(v);
    }

    ValueType::ValueType(){
        this->v=Number(0);
    }

    ValueType::ValueType(const ValueType&a){
        if(std::holds_alternative<Number>(a.v))this->v=a.Num();
        else if(std::holds_alternative<std::shared_ptr<Array>>(a.v))this->v=std::make_shared<Array>(a.Arr());
        else if(std::holds_alternative<std::shared_ptr<Object>>(a.v))this->v=std::make_shared<Object>(a.Obj());
        else if(std::holds_alternative<std::shared_ptr<String>>(a.v))this->v=std::make_shared<String>(a.Str());
        else this->v=Number(0);
    }

    ValueType&ValueType::operator=(const ValueType&a){
        if(std::holds_alternative<Number>(a.v))this->v=a.Num();
        else if(std::holds_alternative<std::shared_ptr<Array>>(a.v))this->v=std::make_shared<Array>(a.Arr());
        else if(std::holds_alternative<std::shared_ptr<Object>>(a.v))this->v=std::make_shared<Object>(a.Obj());
        else if(std::holds_alternative<std::shared_ptr<String>>(a.v))this->v=std::make_shared<String>(a.Str());
        else this->v=Number(0);
        return *this;
    }

    bool VarKey::operator==(const VarKey&a)const{
        return this->name==a.name&&this->level==a.level;
    }

    VarKey::VarKey(const std::string&n,size_t l){
        this->name=n;
        this->level=l;
    }

    size_t VarKeyHash::operator()(const VarKey&a)const noexcept{
        return std::hash<std::string>()(a.name)^(std::hash<size_t>()(a.level)<<1);
    }

    Variable::Variable(int l,const std::string&n):name(n),stack_level(l){
        type=Type::Number;
        as.v=Number(0);
        calculatable=true;
        variables[VarKey(n,l)]=this;
    }

    Variable::Variable(int l,const std::string&n,const Number&v):name(n),stack_level(l){
        as.v=v;
        type=Type::Number;
        calculatable=true;
        variables[VarKey(n,l)]=this;
    }

    Variable::Variable(int l,const std::string&n,const Array&v):name(n),stack_level(l){
        as.v=std::make_shared<Array>(v);
        type=Type::Array;
        calculatable=false;
        variables[VarKey(n,l)]=this;
    }

    Variable::Variable(int l,const std::string&n,const Object&v):name(n),stack_level(l){
        as.v=std::make_shared<Object>(v);
        type=Type::Object;
        calculatable=false;
        variables[VarKey(n,l)]=this;
    }

    Variable::Variable(int l,const std::string&n,const String&v):name(n),stack_level(l){
        as.v=std::make_shared<String>(v);
        type=Type::String;
        calculatable=false;
        variables[VarKey(n,l)]=this;
    }

    Number&Variable::getNumber(){
        return as.Num();
    }

    const Number&Variable::getConstNumber()const{
        return as.Num();
    }

    Type Variable::getType()const{
        return type;
    }
}