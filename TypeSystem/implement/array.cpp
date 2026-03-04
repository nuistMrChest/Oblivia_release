// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../array.h"
#include"../value.h"
#include<vector>
#include<memory>
#include"../string.h"
#include"../object.h"
#include"../reference.h"

namespace Oblivia{
    Type ArrayElement::getType()const{
        return type;
    }

    ArrayElement::ArrayElement():index(-1),father(nullptr){
        type=Type::Number;
        as.v=Number(0);
        calculatable=true;
    }

    ArrayElement::ArrayElement(const Array&f,size_t i):index(i),father(&f){
        type=Type::Number;
        as.v=Number(0);
        calculatable=true;
    }

    ArrayElement::ArrayElement(const Array&f,size_t i,const Number&a):index(i),father(&f){
        type=Type::Number;
        as.v=a;
        calculatable=true;
    }

    ArrayElement::ArrayElement(const Array&f,size_t i,const std::unique_ptr<Array>&a):index(i),father(&f){
        type=Type::Array;
        as.v=std::make_unique<Array>(*a);
        calculatable=false;
    }

    ArrayElement::ArrayElement(const Array&f,size_t i,const std::unique_ptr<Object>&a):index(i),father(&f){
        type=Type::Object;
        as.v=std::make_unique<Object>(*a);
        calculatable=false;
    }

    ArrayElement::ArrayElement(const Array&f,size_t i,const std::unique_ptr<String>&a):index(i),father(&f){
        type=Type::String;
        as.v=std::make_unique<String>(*a);
        calculatable=false;
    }

    ArrayElement::ArrayElement(const Array&f,size_t i,const std::unique_ptr<Reference>&a):index(i),father(&f){
        type=Type::Reference;
        as.v=std::make_unique<Reference>(*a);
        calculatable=a->calculatable;
    }

    ArrayElement&ArrayElement::operator=(const ArrayElement&a){
        this->type=a.type;
        this->as=a.as;
        this->calculatable=a.calculatable;
        return *this;
    }

    Number&ArrayElement::getNumber(){
        if(this->type==Type::Reference)return this->as.Ref().ref->Num();
        return this->as.Num();
    }

    const Number&ArrayElement::getConstNumber()const{
        return this->as.Num();
    }

    std::ostream&operator<<(std::ostream&os,const ArrayElement&a){
        switch(a.type){
            case Type::Number:os<<a.as.Num();break;
            case Type::Array:os<<a.as.Arr();break;
            case Type::Object:os<<a.as.Obj();break;
            case Type::Reference:os<<a.as.Ref();break;
            case Type::String:os<<a.as.Str();break;
        }
        return os;
    }

    Array::Array(){
        type=Type::Array;
        array.resize(0);
    }

    Array::Array(int length){
        type=Type::Array;
        if(length>0){
            array.resize(length);
            for(int i=0;i<length;i++){
                array[i]=std::make_unique<ArrayElement>(*this,i);
            }
        }
        else array.resize(0);
    }

    Array::Array(const Array&a){
        this->type=a.type;
        this->array.resize(a.array.size());
        for(int i=0;i<a.array.size();i++){
            switch(a.array[i]->getType()){
                case Type::Number:this->array[i]=std::make_unique<ArrayElement>(*this,i,a.array[i]->as.Num());break;
                case Type::Array:this->array[i]=std::make_unique<ArrayElement>(*this,i,std::make_unique<Array>(a.array[i]->as.Arr()));break;
                case Type::Object:this->array[i]=std::make_unique<ArrayElement>(*this,i,std::make_unique<Object>(a.array[i]->as.Obj()));break;
                case Type::String:this->array[i]=std::make_unique<ArrayElement>(*this,i,std::make_unique<String>(a.array[i]->as.Str()));break;
                case Type::Reference:this->array[i]=std::make_unique<ArrayElement>(*this,i,std::make_unique<Reference>(a.array[i]->as.Ref()));break;
            }
        }
    }

    Array&Array::operator=(const Array&a){
        this->type=a.type;
        this->array.resize(a.array.size());
        for(int i=0;i<a.array.size();i++){
            switch(a.array[i]->getType()){
                case Type::Number:this->array[i]=std::make_unique<ArrayElement>(*this,i,a.array[i]->as.Num());break;
                case Type::Array:this->array[i]=std::make_unique<ArrayElement>(*this,i,std::make_unique<Array>(a.array[i]->as.Arr()));break;
                case Type::Object:this->array[i]=std::make_unique<ArrayElement>(*this,i,std::make_unique<Object>(a.array[i]->as.Obj()));break;
                case Type::String:this->array[i]=std::make_unique<ArrayElement>(*this,i,std::make_unique<String>(a.array[i]->as.Str()));break;
                case Type::Reference:this->array[i]=std::make_unique<ArrayElement>(*this,i,std::make_unique<Reference>(a.array[i]->as.Ref()));break;
            }
        }
        return *this;
    }

    int Array::getLength(){
        return array.size();
    }

    ArrayElement&Array::visitValue(size_t index){
        return *array[index];
    }

    void Array::print(std::ostream&os)const{
        os<<"{ ";
        for(int i=0;i<array.size();i++){
            os<<*array[i]<<" ";
        }
        os<<"}";
    }

    Number ArrayElement::operator==(const ArrayElement&a)const{
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

    Number Array::operator==(const Array&a)const{
        if(this->array.size()!=a.array.size())return Number(0);
        for(size_t i=0;i<a.array.size();i++){
            if(!(*(this->array[i])==*(a.array[i])))return Number(0);
        }
        return Number(1);
    }
}