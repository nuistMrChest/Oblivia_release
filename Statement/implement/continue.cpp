// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../statement.h"

namespace Oblivia{
    Continue::Continue(){
        type=StatementType::Continue;
        stack_level=0;
        tokens=Tokens();
    }

    Continue::Continue(size_t l,const Tokens&t){
        type=StatementType::Continue;
        stack_level=l;
        tokens=t;
    }

    bool Continue::isLegal(const Tokens&t){
        if(t.size()!=2)return false;
        if(t[0].str!="continue")return false;
        if(t[1].type!=TokenType::SemiColon)return false;
        return true;
    }

    Situation Continue::execute(ExecuteResult&result){
        result=ExecuteResult::ContinueLoop;
        return Situation::Success;
    }

    Situation Continue::build(){
        return Situation::Success;
    }
}