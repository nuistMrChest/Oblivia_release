// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef SITUATION_H
#define SITUATION_H

#include<iostream>

namespace Oblivia{
    enum class Situation{
        Test,

        Success,
        
        BadToken,
        FailedCalaulation,
        BadStatement,
        BuildFailed,
        FailedReverse,
        BadUnaryOperator,
        NotCalcutalable,
        VariableNotFound,
        NotValue,
        BadBinaryOperator,
        NotAssignable,
        NotAssigner,
        NotArray,
        BadIndexing,
        NotObject,
        BadAttribute,
        BadString,
        BadLiteral,
        BadObjectLiteral,
        BadArrayLiteral,
        NotBoolean,
        UnlinkedElse,

        NotString,
        IlegalStatement,

        BadEscape,

        NotOwner,
        NotMovable,

        UsedIdentifier,

        AttributeExist,
        BadAttributeName,
        BadPath
    };

    std::ostream&operator<<(std::ostream&os,const Situation&a);
}

#endif