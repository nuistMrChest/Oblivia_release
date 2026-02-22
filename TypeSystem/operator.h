// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef OPERATOR_H
#define OPERATOR_H

#include<string>

namespace Oblivia{
    enum class Operator{
        NotOperator,

        Addition,
        Subtraction,
        Multiplication,
        Division,
        Modulo,
        Assignment,
        Equality,
        Inequality,
        GreaterThan,
        LessThan,
        GreaterThanOrEqualTo,
        LessThanOrEqualTo,
        And,
        Or,
        Not,
        ElementIndexing,
        AttributeDereferencing,
        AdditionAssignment,
        SubtractionAssignment,
        MultiplicationAssignment,
        DivisionAssignment,
        ModuloAssignment
    };

    Operator toOperator(const std::string&a);

    int getArity(const Operator&a);

    int getPrecedence(const Operator&a);

    enum class Associativity{
        Right,
        Left
    };

    Associativity getAssociativity(const Operator&a);
}

#endif