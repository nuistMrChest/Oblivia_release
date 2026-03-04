// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../statement.h"

namespace Oblivia{
    bool Borrow::isLegal(const Tokens&t){
        if(t[0].str!="borrow")return false;
        if(t[t.size()-1].type!=TokenType::SemiColon)return false;
        if(t[t.size()-2].type!=TokenType::Identifier)return false;
        if(t[t.size()-3].type!=TokenType::Comma)return false;
        Tokens tmp=t;
        tmp.erase(tmp.begin());
        for(int i=0;i<3;i++)tmp.pop_back();
        return isExpression(tmp);
    }

    Borrow::Borrow(){
        type=StatementType::Borrow;
        stack_level=0;
        tokens=Tokens();
        from=Expression();
        name="";
    }

    Borrow::Borrow(size_t l,const Tokens&t){
        type=StatementType::Borrow;
        stack_level=l;
        tokens=t;
        from=Expression();
        name="";
        this->build();
    }

    Situation Borrow::build(){
        name=tokens[tokens.size()-2].str;
        Tokens tf=tokens;
        tf.erase(tf.begin());
        for(int i=0;i<3;i++)tf.pop_back();
        from=Expression(tf,stack_level);
        return Situation::Success;
    }

    Situation Borrow::execute(ExecuteResult&result){
        result=ExecuteResult::Other;
        Situation sf=from.calculate();
        if(sf!=Situation::Success)return sf;
        if(!isOwner(from.v,stack_level))return Situation::NotOwner;
        ValueType&from_v=getValueTypeRef(from.v,stack_level);
        Type&ft=getTypeRef(from.v,stack_level);
        for(auto i=Variable::variables.begin();i!=Variable::variables.end();i++){
            if(i->first.level==stack_level&&i->first.name==name)return Situation::UsedIdentifier;
        }
        Variable*tmp=new Variable(stack_level,name,Reference(from_v,&ft));
        return Situation::Success;
    }
}