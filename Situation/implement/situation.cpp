// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include<iostream>
#include"../situation.h"

namespace Oblivia{
    std::ostream&operator<<(std::ostream&os,const Situation&a){
        switch(a){
            case Situation::Test:os<<"Test";break;
            case Situation::Success:os<<"Success";break;
            case Situation::BadToken:os<<"BadToken";break;
            case Situation::FailedCalaulation:os<<"FailedCalulation";break;
            case Situation::BadStatement:os<<"BadStatement";break;
            case Situation::BuildFailed:os<<"BuildFailed";break;
            case Situation::FailedReverse:os<<"FailedReverse";break;
            case Situation::BadUnaryOperator:os<<"BadUnaryOperator";break;
            case Situation::NotCalcutalable:os<<"NotCalcutalable";break;
            case Situation::VariableNotFound:os<<"VariableNotFound";break;
            case Situation::NotValue:os<<"NotValue";break;
            case Situation::BadBinaryOperator:os<<"BadBinaryOperator";break;
            case Situation::NotAssignable:os<<"NotAssignable";break;
            case Situation::NotAssigner:os<<"NotAssigner";break;
            case Situation::NotArray:os<<"NotArray";break;
            case Situation::BadIndexing:os<<"BadIndexing";break;
            case Situation::NotObject:os<<"NotObject";break;
            case Situation::BadAttribute:os<<"BadAttribute";break;
            case Situation::BadString:os<<"BadString";break;
            case Situation::BadLiteral:os<<"BadLiteral";break;
            case Situation::BadObjectLiteral:os<<"BadObjectLiteral";break;
            case Situation::BadArrayLiteral:os<<"BadArrayLiteral";break;
            case Situation::NotBoolean:os<<"NotBoolean";break;
            case Situation::UnlinkedElse:os<<"UnlinkedElse";break;
            case Situation::BadEscape:os<<"BadEscape";break;
            case Situation::NotString:os<<"NotString";break;
            case Situation::IlegalStatement:os<<"IlegalStatement";break;
        }
        return os;
    }
}