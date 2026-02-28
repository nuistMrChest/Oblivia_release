// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../statement.h"
#include<iostream>

namespace Oblivia{
    Print::Print(){
        type=StatementType::Print;
        stack_level=0;
        tokens=Tokens();
        e=Expression();
    }

    Print::Print(size_t l,const Tokens&t){
        type=StatementType::Print;
        stack_level=l;
        tokens=t;
        e=Expression();
        this->build();
    }

    bool Print::isLegal(const Tokens&tokens){
        if(tokens.size()<3)return false;
        if(tokens[tokens.size()-1].type!=TokenType::SemiColon)return false;
        if(tokens[0].str!="print")return false;
        Tokens tmp=tokens;
        tmp.erase(tmp.begin());
        tmp.pop_back();
        return isExpression(tmp);
    }

    Situation Print::execute(ExecuteResult&result){
        result=ExecuteResult::Other;
        Situation si=e.calculate();
        if(si!=Situation::Success)return si;
        std::cout<<e;
        return Situation::Success;
    }

    Situation Print::build(){
        Tokens tmp=tokens;
        tmp.pop_back();
        tmp.erase(tmp.begin());
        e=Expression(tmp,stack_level); 
        return Situation::Success;
    }
}
