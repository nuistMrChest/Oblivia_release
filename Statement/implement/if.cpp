// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../statement.h"

namespace Oblivia{
    If::If(){
        e=nullptr;
        scope_level=0;
        type=StatementType::If;
        tokens=Tokens();
        t=nullptr;
        j=Expression();
        have_else=false;
    }

    If::If(size_t l,const Tokens&to){
        e=nullptr;
        scope_level=l;
        tokens=to;
        t=nullptr;
        type=StatementType::If;
        j=Expression();
        have_else=false;
        this->build();
    }

    bool If::isLegal(const Tokens&t){
        if(t.size()<4)return false;
        if(t[0].str!="if")return false;
        Tokens tmp;
        int i=1;
        while(i<t.size()&&t[i].type!=TokenType::Colon){
            tmp.push_back(t[i]);
            i++;
        }
        if(i==t.size())return false;
        if(!isExpression(tmp))return false;
        if(t[i].type!=TokenType::Colon)return false;
        Tokens subState=t;
        subState.erase(subState.begin(),subState.begin()+i+1);
        return isStatement(subState);
    }

    Situation If::execute(ExecuteResult&result,bool included){
        result=ExecuteResult::Other;
        Situation es=j.calculate();
        if(es!=Situation::Success)return es;
        bool jb;
        Situation bs=j.getBool(jb);
        if(bs!=Situation::Success)return bs;
        if(jb)t->execute(result);
        else if(have_else)e->execute(result);
        return Situation::Success;
    }

    Situation If::build(){
        Tokens je;
        int i=1;
        while(tokens[i].type!=TokenType::Colon){
            je.push_back(tokens[i]);
            i++;
        }
        j=Expression(je,scope_level);
        Tokens subState=tokens;
        subState.erase(subState.begin(),subState.begin()+i+1);
        Situation sit=buildStatement(t,scope_level+1,subState);
        return sit;
    }
}