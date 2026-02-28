// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../variable.h"
#include"../reference.h"
#include"../array.h"
#include"../object.h"
#include"../string.h"
#include"../number.h"
#include<algorithm>
#include<iostream>

namespace Oblivia{
    void Reference::print(std::ostream&os)const{
        if(refed){
            switch(ref_type){
                case Type::Number:os<<ref->Num();break;
                case Type::Array:os<<ref->Arr();break;
                case Type::Object:os<<ref->Obj();break;
                case Type::String:os<<ref->Str();break;
                default:os<<"";
            }
        }
        else{
            os<<"null reference";
        }
    }

    Reference::Reference(){
        ref=nullptr;
        ref_type=Type::Null;
        refed=false;
        type=Type::Refence;
        calculatable=false;
    }

    Reference::Reference(ValueType&v,Type t){
        ref=&v;
        ref_type=t;
        refed=true;
        type=Type::Refence;
        v.refed_by.push_back(this);
        if(t==Type::Number)calculatable=true;
        else calculatable=false;
    }

    Reference::Reference(const Reference&a){
        this->ref=a.ref;
        this->type=a.type;
        this->refed=a.refed;
        this->ref_type=a.ref_type;
        this->ref->refed_by.push_back(this);
        this->calculatable=a.calculatable;
    }

    Reference&Reference::operator=(const Reference&a){
        this->ref=a.ref;
        this->type=a.type;
        this->refed=a.refed;
        this->ref_type=a.ref_type;
        this->ref->refed_by.push_back(this);
        return*this;
    }

    Number Reference::operator==(const Reference&a)const{
        if(this->refed&&this->ref==a.ref)return Number(1);
        return Number(0);
    }

    Number&Reference::getNumber(){
        return ref->Num();
    }

    const Number&Reference::getConstNumber()const{
        return ref->Num();
    }

    Reference::~Reference(){
        if(ref!=nullptr){
            ref->refed_by.erase(
                std::remove(
                    ref->refed_by.begin(),
                    ref->refed_by.end(),
                    this
                ),
                ref->refed_by.end()
            );
        }
    }
}