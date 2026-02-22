// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../statement.h"

namespace Oblivia{
    Expr::Expr(){
        type=StatementType::Expr;
        stack_level=0;
        tokens=Tokens();
        e=Expression();
    }

    Expr::Expr(int l,const Tokens&t){
        type=StatementType::Expr;
        stack_level=l;
        tokens=t;
        e=Expression();
        this->build();
    }

    bool Expr::isLegal(const Tokens&tokens){
        if(tokens[tokens.size()-1].type!=TokenType::SemiColon)return false;
        Tokens tmp=tokens;
        tmp.pop_back();
        return isExpression(tmp);
    }

    Situation Expr::execute(ExecuteResult&result){
        result=ExecuteResult::Other;
        return e.calculate();
    }

    Situation Expr::build(){
        Tokens t=tokens;
        t.pop_back();
        e=Expression(t,stack_level);
        return Situation::Success;
    }
}
