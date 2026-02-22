// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../operator.h"

namespace Oblivia{
    Operator toOperator(const std::string&a){
        if(a=="+")return Operator::Addition;
        else if(a=="-")return Operator::Subtraction;
        else if(a=="*")return Operator::Multiplication;
        else if(a=="/")return Operator::Division;
        else if(a=="%")return Operator::Modulo;
        else if(a=="=")return Operator::Assignment;
        else if(a=="==")return Operator::Equality;
        else if(a=="!=")return Operator::Inequality;
        else if(a==">")return Operator::GreaterThan;
        else if(a=="<")return Operator::LessThan;
        else if(a==">=")return Operator::GreaterThanOrEqualTo;
        else if(a=="<=")return Operator::LessThanOrEqualTo;
        else if(a=="&&")return Operator::And;
        else if(a=="||")return Operator::Or;
        else if(a=="!")return Operator::Not;
        else if(a=="#")return Operator::ElementIndexing;
        else if(a=="->")return Operator::AttributeDereferencing;
        else if(a=="+=")return Operator::AdditionAssignment;
        else if(a=="-=")return Operator::SubtractionAssignment;
        else if(a=="*=")return Operator::MultiplicationAssignment;
        else if(a=="/=")return Operator::DivisionAssignment;
        else if(a=="%=")return Operator::ModuloAssignment;
        return Operator::NotOperator;
    }

    int getArity(const Operator&a){
        if(a==Operator::Not)return 1;
        else if(a==Operator::NotOperator)return -1;
        else return 2;
    }

    int getPrecedence(const Operator&a){
        switch(a){
            case Operator::ElementIndexing:
            case Operator::AttributeDereferencing:return 8;
            case Operator::Not:return 7;
            case Operator::Multiplication:
            case Operator::Division:
            case Operator::Modulo:return 6;
            case Operator::Addition:
            case Operator::Subtraction:return 5;
            case Operator::GreaterThan:
            case Operator::LessThan:
            case Operator::GreaterThanOrEqualTo:
            case Operator::LessThanOrEqualTo:return 4;
            case Operator::Equality:
            case Operator::Inequality:return 3;
            case Operator::And:return 2;
            case Operator::Or:return 1;
            case Operator::Assignment:
            case Operator::AdditionAssignment:
            case Operator::SubtractionAssignment:
            case Operator::MultiplicationAssignment:
            case Operator::DivisionAssignment:
            case Operator::ModuloAssignment:return 0;
            case Operator::NotOperator:
            default:return -1;
        }
    }

    Associativity getAssociativity(const Operator&a){
        switch(a){
            case Operator::Not:
            case Operator::Assignment:
            case Operator::AdditionAssignment:
            case Operator::SubtractionAssignment:
            case Operator::MultiplicationAssignment:
            case Operator::DivisionAssignment:
            case Operator::ModuloAssignment:return Associativity::Right;
            default:return Associativity::Left;
        }
    }
}