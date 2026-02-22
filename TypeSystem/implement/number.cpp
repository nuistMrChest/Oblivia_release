// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../number.h"
#include<math.h>

namespace Oblivia{

    Number::Number(){
        this->type=Type::Number;
        this->value=0;
        calculatable=true;
    }

    Number::Number(float a){
        this->type=Type::Number;
        this->value=a;
        calculatable=true;
    }

    Number::Number(const std::string&a){
        float tmp=0.0f;
        int frac_digits=0;
        bool after_dot=false;
        for(int i=0;i<a.length();i++){
            if(a[i]=='.'){
                after_dot=true;
                continue;
            }
            tmp = tmp*10.0f+(a[i]-'0');
            if(after_dot)frac_digits++;
        }
        while(frac_digits--)tmp*=0.1f;
        value=tmp;
        this->type=Type::Number;
        calculatable=true;
    }

    float Number::getFloatValue(){
        return this->value;
    }

    Number Number::operator+(const Number&a){
        return Number(this->value+a.value);
    }

    Number Number::operator-(const Number&a){
        return Number(this->value-a.value);
    }

    Number Number::operator*(const Number&a){
        return Number(this->value*a.value);
    }
    
    Number Number::operator/(const Number&a){
        return Number(this->value/a.value);
    }

    Number Number::operator%(const Number&a){
        Number tmp;
        tmp.value=fmod(this->value,a.value);
        return tmp;
    }

    Number&Number::operator=(const Number&a){
        this->value=a.value;
        this->type=a.type;
        this->calculatable=a.calculatable;
        return *this;
    }

    Number&Number::operator+=(const Number&a){
        this->value+=a.value;
        this->type=a.type;
        this->calculatable=a.calculatable;
        return *this;
    }

    Number&Number::operator-=(const Number&a){
        this->value-=a.value;
        this->type=a.type;
        this->calculatable=a.calculatable;
        return *this;
    }

    Number&Number::operator*=(const Number&a){
        this->value*=a.value;
        this->type=a.type;
        this->calculatable=a.calculatable;
        return *this;
    }

    Number&Number::operator/=(const Number&a){
        this->value/=a.value;
        this->type=a.type;
        this->calculatable=a.calculatable;
        return *this;
    }

    Number&Number::operator%=(const Number&a){
        this->value=fmod(this->value,a.value);
        this->type=a.type;
        this->calculatable=a.calculatable;
        return *this;
    }

    Number Number::operator>(const Number&a){
        if(this->value>a.value)return Number(1);
        return Number(0);
    }

    Number Number::operator<(const Number&a){
        if(this->value<a.value)return Number(1);
        return Number(0);
    }

    Number Number::operator>=(const Number&a){
        if(this->value>=a.value)return Number(1);
        return Number(0);
    }

    Number Number::operator<=(const Number&a){
        if(this->value<=a.value)return Number(1);
        return Number(0);
    }

    Number Number::operator==(const Number&a){
        if(this->value==a.value)return Number(1);
        return Number(0);
    }

    Number Number::operator!=(const Number&a){
        if(this->value!=a.value)return Number(1);
        return Number(0);
    }

    Number Number::operator&&(const Number&a){
        if(this->value!=0&&a.value!=0)return Number(1);
        return Number(0);
    }

    Number Number::operator||(const Number&a){
        if(this->value!=0||a.value!=0)return Number(1);
        return Number(0);
    }

    Number Number::operator!(){
        return Number(!bool(*this));
    }

    void Number::print(std::ostream&os)const{
        os<<this->value;
    }

    Number&Number::getNumber(){
        return *this;
    }

    const Number&Number::getConstNumber()const{
        return *this;
    }

    Number::Number(const Number&a){
        this->type=a.type;
        this->value=a.value;
        calculatable=true;
    }

    Number::operator bool() const{
        if(isnan(value))return false;
        return value!=0.0;
    }

    size_t Number::getSizeT()const{
        return value;
    }

    Number Number::operator+(const Number&a)const{
        return Number(this->value+a.value);
    }

    Number Number::operator-(const Number&a)const{
        return Number(this->value-a.value);
    }

    Number Number::operator*(const Number&a)const{
        return Number(this->value*a.value);
    }
    
    Number Number::operator/(const Number&a)const{
        return Number(this->value/a.value);
    }

    Number Number::operator%(const Number&a)const{
        Number tmp;
        tmp.value=fmod(this->value,a.value);
        return tmp;
    }

    Number Number::operator>(const Number&a)const{
        if(this->value>a.value)return Number(1);
        return Number(0);
    }

    Number Number::operator<(const Number&a)const{
        if(this->value<a.value)return Number(1);
        return Number(0);
    }

    Number Number::operator>=(const Number&a)const{
        if(this->value>=a.value)return Number(1);
        return Number(0);
    }

    Number Number::operator<=(const Number&a)const{
        if(this->value<=a.value)return Number(1);
        return Number(0);
    }

    Number Number::operator==(const Number&a)const{
        if(this->value==a.value)return Number(1);
        return Number(0);
    }

    Number Number::operator!=(const Number&a)const{
        if(this->value!=a.value)return Number(1);
        return Number(0);
    }

    Number Number::operator&&(const Number&a)const{
        if(this->value!=0&&a.value!=0)return Number(1);
        return Number(0);
    }

    Number Number::operator||(const Number&a)const{
        if(this->value!=0||a.value!=0)return Number(1);
        return Number(0);
    }

    Number Number::operator!()const{
        return Number(!bool(*this));
    }
}