// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../array.h"
#include"../value.h"
#include<vector>
#include<memory>
#include"../string.h"
#include"../object.h"

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

    ArrayElement::ArrayElement(const Array&f,size_t i,const std::shared_ptr<Array>&a):index(i),father(&f){
        type=Type::Array;
        as.v=std::make_shared<Array>(*a);
        calculatable=false;
    }

    ArrayElement::ArrayElement(const Array&f,size_t i,const std::shared_ptr<Object>&a):index(i),father(&f){
        type=Type::Object;
        as.v=std::make_shared<Object>(*a);
        calculatable=false;
    }

    ArrayElement::ArrayElement(const Array&f,size_t i,const std::shared_ptr<String>&a):index(i),father(&f){
        type=Type::String;
        as.v=std::make_shared<String>(*a);
        calculatable=false;
    }

    ArrayElement&ArrayElement::operator=(const ArrayElement&a){
        this->type=a.type;
        this->as=a.as;
        this->calculatable=a.calculatable;
        return *this;
    }

    Number&ArrayElement::getNumber(){
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
                array[i]=std::make_shared<ArrayElement>(*this,i);
            }
        }
        else array.resize(0);
    }

    Array::Array(const Array&a){
        this->type=a.type;
        this->array.resize(a.array.size());
        for(int i=0;i<a.array.size();i++){
            switch(a.array[i]->getType()){
                case Type::Number:this->array[i]=std::make_shared<ArrayElement>(*this,i,a.array[i]->as.Num());break;
                case Type::Array:this->array[i]=std::make_shared<ArrayElement>(*this,i,std::make_shared<Array>(a.array[i]->as.Arr()));break;
                case Type::Object:this->array[i]=std::make_shared<ArrayElement>(*this,i,std::make_shared<Object>(a.array[i]->as.Obj()));break;
            }
        }
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