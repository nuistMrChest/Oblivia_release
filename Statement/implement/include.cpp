// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../statement.h"
#include<fstream>

namespace Oblivia{
    bool Include::isLegal(const Tokens&t){
        if(t.size()<3)return false;
        if(t[0].str!="include")return false;
        if(t[t.size()-1].type!=TokenType::SemiColon)return false;
        Tokens tmp=t;
        tmp.erase(tmp.begin());
        tmp.pop_back();
        return isExpression(tmp);
    }

    Include::Include(){
        type=StatementType::Include;
        scope_level=0;
        tokens=Tokens();
        pe=Expression();
    }

    Include::Include(size_t l,const Tokens&t){
        type=StatementType::Include;
        scope_level=l;
        tokens=t;
        pe=Expression();
        this->build();
    }

    Situation Include::build(){
        Tokens tmp=tokens;
        tmp.erase(tmp.begin());
        tmp.pop_back();
        pe=Expression(tmp,scope_level);
        return Situation::Success;
    }

    Situation Include::execute(Expression&ret,ExecuteResult&result,bool included){
        Situation se=pe.calculate();
        if(se!=Situation::Success)return se;
        if(getType(pe.v,scope_level)!=Type::String)return Situation::NotString;
        std::string path=getValueType(pe.v,scope_level).Str().getCont();
        std::ifstream fin(path);
        if(!fin)return Situation::BadPath;
        std::string code{std::istreambuf_iterator<char>(fin),std::istreambuf_iterator<char>()};
        code.push_back('}');
        code.insert(code.begin(),'{');
        Words w;
        Situation sw=tokenize(w,code);
        if(sw!=Situation::Success)return sw;
        Tokens t;
        Situation st=processToken(t,w);
        if(st!=Situation::Success)return st;
        if(!isStatement(t))return Situation::BadStatement;
        std::unique_ptr<Statement>stat;
        Situation sb=buildStatement(stat,scope_level-1,t);
        if(sb!=Situation::Success)return sb;
        return stat->execute(ret,result,true);    
    }
}
