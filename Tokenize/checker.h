// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef CHECKER_H
#define CHECKER_H

#include<string>
#include<vector>

namespace Oblivia{
    bool isNumber(const std::string&a);
    bool isNumberChar(char a);

    bool isIdentifier(const std::string&a);
    bool isIdentifierChar(char a);

    bool isOperator(const std::string&a);
    bool isOperatorChar(char a);

    bool isParen(const std::string&a);
    bool isParenChar(char a);

    bool isBracket(const std::string&a);
    bool isBracketChar(char a);

    bool isBrace(const std::string&a);
    bool isBraceChar(char a);

    bool isArrow(const std::string&a);

    bool isColon(const std::string&a);
    bool isColonChar(char a);

    bool isComma(const std::string&a);
    bool isCommaChar(char a);

    bool isSemiColon(const std::string&a);
    bool isSemiColonChar(char a);

    bool isKeyWord(const std::string&a);

    bool isDoubleQuoteChar(char a);
    bool isDoubleQuote(const std::string&a);

    bool isBackSlashChar(char a);
    bool isBackSlash(const std::string&a);

    bool isSpaceChar(char a);
    bool isSpace(const std::string&a);

    bool isCaretChar(char a);
    bool isCaret(const std::string&a);

    bool isAtChar(char a);
    bool isAt(const std::string&a);
}

#endif
