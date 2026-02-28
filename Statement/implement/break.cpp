// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../statement.h"

namespace Oblivia{
    Break::Break(){
        type=StatementType::Break;
        stack_level=0;
        tokens=Tokens();
    }

    Break::Break(size_t l,const Tokens&t){
        type=StatementType::Break;
        stack_level=l;
        tokens=t;
    }

    bool Break::isLegal(const Tokens&t){
        if(t.size()!=2)return false;
        if(t[0].str!="break")return false;
        if(t[1].type!=TokenType::SemiColon)return false;
        return true;
    }

    Situation Break::execute(ExecuteResult&result){
        result=ExecuteResult::EndLoop;
        return Situation::Success;
    }

    Situation Break::build(){
        return Situation::Success;
    }
}