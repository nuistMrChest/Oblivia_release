// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../statement.h"
#include"../../Tokenize/checker.h"

namespace Oblivia{
    Let::Let(){
        tokens=Tokens();
        type=StatementType::Let;
        stack_level=0;
    }

    Let::Let(int l,const Tokens&t){
        tokens=t;
        type=StatementType::Let;
        stack_level=l;
        this->build();
    }

    bool Let::isLegal(const Tokens&tokens){
        if(tokens.size()<3)return false;
        if(tokens[tokens.size()-1].type!=TokenType::SemiColon)return false;
        if(tokens[0].str!="let")return false;
        if(tokens[1].type!=TokenType::Identifier)return false;
        Tokens tmp=tokens;
        tmp.pop_back();
        tmp.erase(tmp.begin(),tmp.begin()+2);
        if(!tmp.empty()){
            if(tmp[0].str!="=")return false;
            tmp.erase(tmp.begin());
            return isExpression(tmp);
        }
        return true;
    }

    Situation Let::execute(ExecuteResult&result){
        result=ExecuteResult::Other;
        Variable* var=new Variable(stack_level,name);
        if(tokens.size()>3){
           Situation si=val.calculate();
           if(si!=Situation::Success)return si;
           var->as=getValueType(val.v,stack_level);
           var->type=getType(val.v,stack_level);
        }
        return Situation::Success;
    }

    Situation Let::build(){
        name=tokens[1].str;
        if(tokens.size()>3){
            Tokens tmp=tokens;
            tmp.erase(tmp.begin(),tmp.begin()+3);
            tmp.pop_back();
            std::cout<<"\n";
            val=Expression(tmp,stack_level);
        }
        return Situation::Test;
    }
}
