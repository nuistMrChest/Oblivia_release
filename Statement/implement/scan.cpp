// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../statement.h"
#include<iostream>

namespace Oblivia{
    Scan::Scan(){
        type=StatementType::Scan;
        stack_level=0;
        tokens=Tokens();
    }

    Scan::Scan(size_t l,const Tokens&t){
        type=StatementType::Scan;
        stack_level=l;
        tokens=t;
    }

    bool Scan::isLegal(const Tokens&tokens){
        if(tokens.size()<3)return false;
        if(tokens[tokens.size()-1].type!=TokenType::SemiColon)return false;
        if(tokens[0].str!="scan")return false;
        Tokens tmp=tokens;
        tmp.erase(tmp.begin());
        tmp.pop_back();
        return isExpression(tmp);
    }

    Situation Scan::execute(ExecuteResult&result){
        result=ExecuteResult::Other;
        Tokens tmp=tokens;
        tmp.pop_back();
        tmp.erase(tmp.begin());
        Expression e(tmp,stack_level);
        e.calculate();
        if(e.v.type!=TokenType::Identifier&&e.v.type!=TokenType::Variable&&e.v.type!=TokenType::ArrayElement&&e.v.type!=TokenType::ObjectAttribute)return Situation::NotAssignable;
        getTypeRef(e.v,stack_level)=Type::String;
        ValueType&val=getValueTypeRef(e.v,stack_level);
        std::string tmp_s;
        std::getline(std::cin,tmp_s);
        val.v=std::make_unique<String>(tmp_s);
        return Situation::Success;
    }

    Situation Scan::build(){
        return Situation::Test;
    }
}