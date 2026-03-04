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
#include"../reference.h"

namespace Oblivia{
    std::unordered_map<VarKey,Variable*,VarKeyHash>Variable::variables;

    Number&ValueType::Num(){
        return std::get<Number>(v);
    }

    Array&ValueType::Arr(){
        return*std::get<std::unique_ptr<Array>>(v);
    }

    Object&ValueType::Obj(){
        return*std::get<std::unique_ptr<Object>>(v);
    }

    String&ValueType::Str(){
        return*std::get<std::unique_ptr<String>>(v);
    }

    Reference&ValueType::Ref(){
        return*std::get<std::unique_ptr<Reference>>(v);
    }

    const Number&ValueType::Num()const{
        return std::get<Number>(v);
    }

    const Array&ValueType::Arr()const{
        return*std::get<std::unique_ptr<Array>>(v);
    }

    const Object&ValueType::Obj()const{
        return*std::get<std::unique_ptr<Object>>(v);
    }

    const String&ValueType::Str()const{
        return*std::get<std::unique_ptr<String>>(v);
    }

    const Reference&ValueType::Ref()const{
        return*std::get<std::unique_ptr<Reference>>(v);
    }

    ValueType::ValueType(){
        this->v=Number(0);
    }

    ValueType::ValueType(const ValueType&a){
        if(std::holds_alternative<Number>(a.v))this->v=a.Num();
        else if(std::holds_alternative<std::unique_ptr<Array>>(a.v))this->v=std::make_unique<Array>(a.Arr());
        else if(std::holds_alternative<std::unique_ptr<Object>>(a.v))this->v=std::make_unique<Object>(a.Obj());
        else if(std::holds_alternative<std::unique_ptr<String>>(a.v))this->v=std::make_unique<String>(a.Str());
        else if(std::holds_alternative<std::unique_ptr<Reference>>(a.v))this->v=std::make_unique<Reference>(a.Ref());
        else this->v=Number(0);
    }

    ValueType&ValueType::operator=(const ValueType&a){
        if(std::holds_alternative<Number>(a.v))this->v=a.Num();
        else if(std::holds_alternative<std::unique_ptr<Array>>(a.v))this->v=std::make_unique<Array>(a.Arr());
        else if(std::holds_alternative<std::unique_ptr<Object>>(a.v))this->v=std::make_unique<Object>(a.Obj());
        else if(std::holds_alternative<std::unique_ptr<String>>(a.v))this->v=std::make_unique<String>(a.Str());
        else if(std::holds_alternative<std::unique_ptr<Reference>>(a.v))this->v=std::make_unique<Reference>(a.Ref());
        else this->v=Number(0);
        return *this;
    }

    ValueType::~ValueType(){
        for(size_t i=0;i<refed_by.size();i++){
            refed_by[i]->ref=nullptr;
            refed_by[i]->refed=false;
            refed_by[i]->ref_type=nullptr;
        }
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

    Variable::Variable(size_t l,const std::string&n):name(n),stack_level(l){
        type=Type::Number;
        as.v=Number(0);
        calculatable=true;
        variables[VarKey(n,l)]=this;
    }

    Variable::Variable(size_t l,const std::string&n,const Number&v):name(n),stack_level(l){
        as.v=v;
        type=Type::Number;
        calculatable=true;
        variables[VarKey(n,l)]=this;
    }

    Variable::Variable(size_t l,const std::string&n,const Array&v):name(n),stack_level(l){
        as.v=std::make_unique<Array>(v);
        type=Type::Array;
        calculatable=false;
        variables[VarKey(n,l)]=this;
    }

    Variable::Variable(size_t l,const std::string&n,const Object&v):name(n),stack_level(l){
        as.v=std::make_unique<Object>(v);
        type=Type::Object;
        calculatable=false;
        variables[VarKey(n,l)]=this;
    }

    Variable::Variable(size_t l,const std::string&n,const String&v):name(n),stack_level(l){
        as.v=std::make_unique<String>(v);
        type=Type::String;
        calculatable=false;
        variables[VarKey(n,l)]=this;
    }

    Variable::Variable(size_t l,const std::string&n,const Reference&v):name(n),stack_level(l){
        as.v=std::make_unique<Reference>(v);
        type=Type::Reference;
        calculatable=v.calculatable;
        variables[VarKey(n,l)]=this;
    }

    Number&Variable::getNumber(){
        if(type==Type::Reference)return as.Ref().ref->Num();
        return as.Num();
    }

    const Number&Variable::getConstNumber()const{
        if(type==Type::Reference)return as.Ref().ref->Num();
        return as.Num();
    }

    Type Variable::getType()const{
        return type;
    }

    Number z(0);

    Number&getNumberRef(ValueType&a,Type t){
        switch(t){
            case Type::Number:return a.Num();
            case Type::Reference:return a.Ref().ref->Num();
            default:return z;
        }
        return z;
    }

    Number getNumber(const ValueType&a,Type t){
        switch(t){
            case Type::Number:return a.Num();
            case Type::Reference:return a.Ref().ref->Num();
            default:return Number(0);
        }
        return Number(0);
    }

    bool isArray(const ValueType&a,Type t){
        switch(t){
            case Type::Array:return true;
            case Type::Reference:return*(a.Ref().ref_type)==Type::Array;
            default:return false;
        }
        return false;
    }

    Array dfa;

    Array&getArrayRef(ValueType&a,Type t){
        switch(t){
            case Type::Array:return a.Arr();
            case Type::Reference:return a.Ref().ref->Arr();
            default:return dfa;
        }
        return dfa;
    }

    Array getArray(const ValueType&a,Type t){
        switch(t){
            case Type::Array:return a.Arr();
            case Type::Reference:return a.Ref().ref->Arr();
            default:return dfa;
        }
        return dfa;
    }
}