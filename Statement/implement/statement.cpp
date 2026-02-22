// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../statement.h"

namespace Oblivia{
    std::ostream&operator<<(std::ostream&os,const StatementType&a){
        switch(a){
            case StatementType::Null:os<<"Null";break;
            case StatementType::Expr:os<<"Expr";break;
            case StatementType::Let:os<<"Let";break;
            case StatementType::Print:os<<"Print";break;
            case StatementType::Scan:os<<"Scan";break;
            case StatementType::If:os<<"If";break;
            case StatementType::Else:os<<"Else";break;
            case StatementType::While:os<<"While";break;
            case StatementType::Block:os<<"Block";break;
            case StatementType::Fn:os<<"Fn";break;
            case StatementType::Break:os<<"Break";break;
            case StatementType::Continue:os<<"Continue";break;
        }
        return os;
    }

    Statement::Statement():stack_level(0){
        type=StatementType::Null;
    }

    StatementType getStateType(const Tokens&a){
        if(a.size()<1)return StatementType::Null;
        if(a[0].str=="{")return StatementType::Block;
        else if(a[0].str=="let")return StatementType::Let;
        else if(a[0].str=="print")return StatementType::Print;
        else if(a[0].str=="scan")return StatementType::Scan;
        else if(a[0].str=="if")return StatementType::If;
        else if(a[0].str=="else")return StatementType::Else;
        else if(a[0].str=="while")return StatementType::While;
        else if(a[0].str=="ifn"||a[0].str=="ofn")return StatementType::Fn;
        else if(a[0].str=="break")return StatementType::Break;
        else if(a[0].str=="continue")return StatementType::Continue;
        else return StatementType::Expr;
    }

    std::ostream&operator<<(std::ostream&os,const Statement&a){
        for(int i=0;i<a.tokens.size();i++){
            os<<a.tokens[i].str;
            if(i!=a.tokens.size()-1)os<<" ";
        }
        return os;
    }

    Situation buildStatement(std::unique_ptr<Statement>&r,int l,const Tokens&t){
        StatementType type=getStateType(t);
        switch(type){
            case StatementType::Null:return Situation::BadStatement;
            case StatementType::Expr:r=std::make_unique<Expr>(l,t);break;
            case StatementType::Let:r=std::make_unique<Let>(l,t);break;
            case StatementType::Print:r=std::make_unique<Print>(l,t);break;
            case StatementType::Scan:r=std::make_unique<Scan>(l,t);break;
            case StatementType::If:r=std::make_unique<If>(l,t);break;
            case StatementType::Else:r=std::make_unique<Else>(l,t);break;
            case StatementType::While:r=std::make_unique<While>(l,t);break;
            case StatementType::Block:r=std::make_unique<Block>(l,t);break;
            // case StatementType::Fn:r=std::make_unique<Fn>(l,t);break;
            case StatementType::Break:r=std::make_unique<Break>(l,t);break;
            case StatementType::Continue:r=std::make_unique<Continue>(l,t);break;
            default:return Situation::Success;
        }
        return Situation::Success;
    }

    bool isStatement(const Tokens&t){
        return(
            Expr::isLegal(t)||
            Let::isLegal(t)||
            Print::isLegal(t)||
            Scan::isLegal(t)||
            Block::isLegal(t)||
            If::isLegal(t)||
            Else::isLegal(t)||
            While::isLegal(t)||
            Break::isLegal(t)||
            Continue::isLegal(t)
            // Fn::isLegal(t)
        );
    }
}
