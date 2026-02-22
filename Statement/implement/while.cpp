// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../statement.h"
#include<iostream>

namespace Oblivia{
    While::While(){
        type=StatementType::While;
        stack_level=0;
        tokens=Tokens();
        d=nullptr;
        j=Expression();
    }

    While::While(int l,const Tokens&t){
        type=StatementType::While;
        stack_level=l;
        tokens=t;
        d=nullptr;
        j=Expression();
        this->build();
    }

    bool While::isLegal(const Tokens&t){
        if(t.size()<4)return false;
        if(t[0].str!="while")return false;
        int i=1;
        Tokens tmp;
        while(i<t.size()&&t[i].type!=TokenType::Colon){
            tmp.push_back(t[i]);
            i++;
        }
        if(i==t.size())return false;
        if(t[i].type!=TokenType::Colon)return false;
        if(!isExpression(tmp))return false;
        Tokens sub=t;
        sub.erase(sub.begin(),sub.begin()+i+1);
        return isStatement(sub);
    }

    Situation While::execute(ExecuteResult&result){
        ExecuteResult er;
        Situation es=j.calculate();
        if(es!=Situation::Success)return es;
        bool jb;
        j.getBool(jb);
        while(jb){
            d->execute(er);
            if(er==ExecuteResult::EndLoop)break;
            es=j.calculate();
            if(es!=Situation::Success)return es;
            j.getBool(jb);
        }
        return Situation::Success;
    }

    Situation While::build(){
        int i=1;
        Tokens jt;
        while(i<tokens.size()&&tokens[i].type!=TokenType::Colon){
            jt.push_back(tokens[i]);
            i++;
        }
        j=Expression(jt,stack_level);
        Tokens tmp=tokens;
        tmp.erase(tmp.begin(),tmp.begin()+i+1);
        return buildStatement(d,stack_level+1,tmp);
    }
}