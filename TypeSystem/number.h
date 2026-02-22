// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef NUMBER_H
#define NUMBER_H

#include"value.h"
#include<string>

namespace Oblivia{
    class Number;

    class Calculatable{
        public:
        virtual Number&getNumber()=0;
        virtual const Number&getConstNumber()const=0;
        bool calculatable;
    };

    class Number:public Value,public Calculatable{
        private:
        float value;
        public:
        Number();
        Number(float a);
        Number(const Number&a);
        Number(const std::string&a);
        Number operator+(const Number&a);
        Number operator-(const Number&a);
        Number operator*(const Number&a);
        Number operator/(const Number&a);
        Number operator%(const Number&a);
        Number&operator=(const Number&a);
        Number operator>(const Number&a);
        Number operator<(const Number&a);
        Number operator==(const Number&a);
        Number operator>=(const Number&a);
        Number operator<=(const Number&a);
        Number operator!=(const Number&a);
        Number operator&&(const Number&a);
        Number operator||(const Number&a);
        Number operator!();
        Number&operator+=(const Number&a);
        Number&operator-=(const Number&a);
        Number&operator*=(const Number&a);
        Number&operator/=(const Number&a);
        Number&operator%=(const Number&a);
        float getFloatValue();
        size_t getSizeT()const;
        void print(std::ostream&os)const;
        Number&getNumber();
        const Number&getConstNumber()const;
        operator bool()const;

        Number operator+(const Number&a)const;
         Number operator-(const Number&a)const;
        Number operator*(const Number&a)const;
        Number operator/(const Number&a)const;
        Number operator%(const Number&a)const;
        Number&operator=(const Number&a)const;
        Number operator>(const Number&a)const;
        Number operator<(const Number&a)const;
        Number operator==(const Number&a)const;
        Number operator>=(const Number&a)const;
        Number operator<=(const Number&a)const;
        Number operator!=(const Number&a)const;
        Number operator&&(const Number&a)const;
        Number operator||(const Number&a)const;
        Number operator!()const;
        Number&operator+=(const Number&a)const;
        Number&operator-=(const Number&a)const;
        Number&operator*=(const Number&a)const;
        Number&operator/=(const Number&a)const;
        Number&operator%=(const Number&a)const;
    };
}

#endif