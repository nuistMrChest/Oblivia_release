// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../statement.h"
#include"../../Tokenize/checker.h"
#include<memory>

namespace Oblivia{
    Let::Let(){
        tokens=Tokens();
        type=StatementType::Let;
        scope_level=0;
        val_ty=Type::Null;
    }

    Let::Let(size_t l,const Tokens&t){
        tokens=t;
        type=StatementType::Let;
        scope_level=l;
        val_ty=Type::Null;
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
            if(tmp[0].str=="="||tmp[0].str=="#"){
                tmp.erase(tmp.begin());
                    return isExpression(tmp);
            }
            else if(tmp[0].type==TokenType::At){
                return tmp.size()==1;
            }
            else return false;
        }
        return true;
    }

    Situation Let::execute(Expression&ret,ExecuteResult&result,bool included){
        result=ExecuteResult::Other;
        for(auto i=Variable::variables.begin();i!=Variable::variables.end();i++){
            if(i->first.level==scope_level&&i->first.name==name)return Situation::UsedIdentifier;
        }
        Variable*var=new Variable(scope_level,name);
        if(tokens.size()>3){
            switch(val_ty){
                case Type::Number:{
                    Situation si=val.calculate();
                    if(si!=Situation::Success)return si;
                    var->as=getValueType(val.v,scope_level);
                    var->type=getType(val.v,scope_level);
                    break;
                }
                case Type::Array:{
                    Situation si=val.calculate();
                    if(si!=Situation::Success)return si;
                    if(getType(val.v,scope_level)!=Type::Number)return Situation::BadIndexing;
                    var->type=Type::Array;
                    var->as.v=std::make_unique<Array>(getValueType(val.v,scope_level).Num().getSizeT());
                    break;
                }
                case Type::Object:{
                    var->type=Type::Object;
                    var->as.v=std::make_unique<Object>();
                    break;
                }
                default:return Situation::NotAssigner;
            }

        }
        return Situation::Success;
    }

    Situation Let::build(){
        name=tokens[1].str;
        if(tokens.size()>3){
            if(tokens[2].type==TokenType::Operator)switch(toOperator(tokens[2].str)){
                case Operator::Assignment:val_ty=Type::Number;break;
                case Operator::ElementIndexing:val_ty=Type::Array;break;
                default:val_ty=Type::Null;
            }
            else val_ty=Type::Object;
            Tokens tmp=tokens;
            tmp.erase(tmp.begin(),tmp.begin()+3);
            tmp.pop_back();
            if(tokens[2].type==TokenType::Operator)val=Expression(tmp,scope_level);
        }
        return Situation::Test;
    }
}
