// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../statement.h"
#include<memory>

namespace Oblivia{
    bool isOwner(const Token&a,size_t l){
        switch(a.type){
            case TokenType::Variable:return true;
            case TokenType::ArrayElement:return true;
            case TokenType::ObjectAttribute:return true;
            case TokenType::Identifier:{
                for(size_t i=l;i>0;i--){
                    VarKey tmp(a.str,i);
                    if(Variable::variables.contains(tmp)&&Variable::variables[tmp]!=nullptr)return true;
                }
                return false;
            }
            default:return false;
        }
        return false;
    }

    bool Move::isLegal(const Tokens&t){
        if(t[0].str!="move")return false;
        if(t[t.size()-1].type!=TokenType::SemiColon)return false;
        Tokens to=t;
        to.pop_back();
        to.erase(to.begin());
        Tokens tn;
        size_t i=0;
        while(i<to.size()&&to[i].type!=TokenType::Comma){
            tn.push_back(to[i]);
            i++;
        }
        if(!isExpression(tn))return false;
        if(to[i].type!=TokenType::Comma)return false;
        to.erase(to.begin(),to.begin()+i+1);
        return isExpression(to);
    }

    Move::Move(){
        type=StatementType::Move;
        scope_level=0;
        tokens=Tokens();
        from=Expression();
        to=Expression();
    }

    Move::Move(size_t l,const Tokens&t){
        type=StatementType::Move;
        scope_level=l;
        tokens=t;
        from=Expression();
        to=Expression();
        this->build();
    }

    Situation Move::build(){
        Tokens tt=tokens;
        tt.pop_back();
        tt.erase(tt.begin());
        Tokens tf;
        size_t i=0;
        while(tt[i].type!=TokenType::Comma){
            tf.push_back(tt[i]);
            i++;
        }
        from=Expression(tf,scope_level);
        tt.erase(tt.begin(),tt.begin()+i+1);
        to=Expression(tt,scope_level);
        return Situation::Success;
    }

    Situation Move::execute(ExecuteResult&result,bool included){
        result=ExecuteResult::Other;
        Situation sfe=from.calculate();
        if(sfe!=Situation::Success)return sfe;
        Situation ste=to.calculate();
        if(ste!=Situation::Success)return ste;
        if(!isOwner(from.v,scope_level))return Situation::NotOwner;
        if(!isOwner(to.v,scope_level))return Situation::NotOwner;
        ValueType&from_v=getTrueValueTypeRef(from.v,scope_level);
        Type&tf=getTrueTypeRef(from.v,scope_level);
        ValueType&to_v=getTrueValueTypeRef(to.v,scope_level);
        Type&tt=getTrueTypeRef(to.v,scope_level);
        tt=tf;
        switch(tf){
            case Type::Number:to_v.v=std::move(from_v.Num());break;
            case Type::Array:to_v.v=std::move(std::get<std::unique_ptr<Array>>(from_v.v));break;
            case Type::Object:to_v.v=std::move(std::get<std::unique_ptr<Object>>(from_v.v));break;
            case Type::String:to_v.v=std::move(std::get<std::unique_ptr<String>>(from_v.v));break;
            case Type::Reference:to_v.v=std::move(std::get<std::unique_ptr<Reference>>(from_v.v));break;
            default:return Situation::NotMovable;
        }
        from_v.v=Number(0);
        tf=Type::Number;
        return Situation::Success;
    }
}