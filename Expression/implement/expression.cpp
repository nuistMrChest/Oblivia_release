// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../expression.h"
#include"../../Tokenize/tokenize.h"
#include"../../TypeSystem/type_system.h"
#include<algorithm>
#include<stack>

#include<iostream>

namespace Oblivia{
    Number zero(0);

    bool isValue(const Token&a){
        return a.type==TokenType::Number||a.type==TokenType::String||a.type==TokenType::Variable||a.type==TokenType::ArrayElement||a.type==TokenType::ObjectAttribute||a.type==TokenType::Identifier||a.type==TokenType::Reference;
    }

    bool isExpression(const Tokens&a){
        Tokens b=a;
        b.erase(
            std::remove_if(
                b.begin(),
                b.end(),
                [](const Token&a){return a.str=="!";}
            ),
            b.end()
        );
        
        for(size_t i=0;i<b.size();i++){
            if(b[i].type==TokenType::Identifier&&i+1<b.size()&&b[i+1].str=="("){
                while(i+1<b.size()&&b[i+1].str!=")")b.erase(b.begin()+i+1);
                b.erase(b.begin()+i+1);
            }
            if(b[i].str=="[")b[i].type=TokenType::Operator;
            if(b[i].str=="]")b.erase(b.begin()+i);
            if(b[i].type==TokenType::Arrow)b[i].type=TokenType::Operator;
        }

        Token front;
        front.str="(";
        front.type=TokenType::Paren;

        Token back;
        back.str=")";
        back.type=TokenType::Paren;

        b.insert(b.begin(),front);
        b.push_back(back);

        std::stack<Token>stk;

        for(size_t i=0;i<b.size();i++){
            if(b[i].type==TokenType::Reference||b[i].type==TokenType::String||b[i].type==TokenType::Number||b[i].type==TokenType::Operator||b[i].type==TokenType::Identifier||b[i].str=="(")stk.push(b[i]);
            else if(b[i].str==")"){
                if(!isValue(stk.top()))return false;
                TokenType type=TokenType::Null;
                TokenType last_type=TokenType::Null;
                int count=0;
                while(stk.top().str!="("){
                    count++;
                    if(isValue(stk.top()))type=TokenType::Value;
                    else if(stk.top().type==TokenType::Operator)type=TokenType::Operator;
                    if(type==last_type)return false;
                    last_type=type;
                    stk.pop();
                }
                if(count%2==0)return false;
                stk.pop();
                Token tmp;
                tmp.type=TokenType::Number;
                stk.push(tmp);
            }
            else return false;
        }

        for(size_t i=0;i<a.size();i++)if(a[i].str=="!"&&i+1<a.size()&&!(a[i+1].type==TokenType::Number||a[i+1].type==TokenType::Identifier||a[i+1].str=="!"||a[i+1].str=="("))return false;
        return true;
    }

    Expression::Expression(const Tokens&a,size_t l):t(a),need_calculatable(false),stack_level(l){}

    Expression::Expression():t(Tokens()),need_calculatable(false){}

    Expression::Expression(const Expression&a){
        this->v=a.v;
        this->t=a.t;
        this->need_calculatable=a.need_calculatable;
        this->stack_level=a.stack_level;
    }

    const Expression&Expression::operator=(const Expression&a){
        this->v=a.v;
        this->t=a.t;
        this->need_calculatable=a.need_calculatable;
        this->stack_level=a.stack_level;
        return a;
    }

    const Number&toNumber(const Token&a,size_t l){
        switch(a.type){
            case TokenType::Identifier:{
                for(size_t i=l;i>0;i--){
                    VarKey tmp(a.str,i);
                    if(Variable::variables.contains(tmp)&&Variable::variables[tmp]!=nullptr){
                        if(Variable::variables[tmp]->calculatable)return Variable::variables[tmp]->getNumber();
                        else return zero;
                    }
                }
                break;
            }
            case TokenType::Variable:{
                if(a.as.var().calculatable)return a.as.var().getConstNumber();
                else return zero;
                break;
            }
            case TokenType::ArrayElement:{
                if(a.as.ele().calculatable)return a.as.ele().getConstNumber();
                else return zero;
                break;
            }
            case TokenType::ObjectAttribute:{
                if(a.as.att().calculatable)return a.as.att().getConstNumber();
                else return zero;
                break;
            }
            case TokenType::Number:{
                if(a.as.num().calculatable)return a.as.num().getConstNumber();
                else return zero;
                break;
            }
            case TokenType::Reference:{
                if(a.as.ref().calculatable)return a.as.ref().getConstNumber();
                else return zero;
                break;
            }
        }
        return zero;
    }

    bool getCal(const Token&a,size_t l){
        switch(a.type){
            case TokenType::Identifier:{
                for(size_t i=l;i>0;i--){
                    VarKey tmp(a.str,i);
                    if(Variable::variables.contains(tmp)&&Variable::variables[tmp]!=nullptr){
                        return Variable::variables[tmp]->calculatable;
                    }
                }
                break;
            }
            case TokenType::Variable:return a.as.var().calculatable;break;
            case TokenType::ArrayElement:return a.as.ele().calculatable;break;
            case TokenType::ObjectAttribute:return a.as.att().calculatable;break;
            case TokenType::Number:return a.as.num().calculatable;break;
            case TokenType::Reference:return a.as.ref().calculatable;break;
            default:return false;
        }
        return false;
    }

    bool assignable(const Token&a,size_t l){
        switch(a.type){
            case TokenType::Identifier:{
                for(size_t i=l;i>0;i--){
                    VarKey tmp(a.str,i);
                    if(Variable::variables.contains(tmp)&&Variable::variables[tmp]!=nullptr){
                        return true;
                    }
                }
                break;
            }
            case TokenType::Variable:
            case TokenType::ArrayElement:
            case TokenType::ObjectAttribute:return true;break;
            case TokenType::Reference:return true;break;
            default:return false;
        }
        return false;
    }

    bool assigner(const Token&a,size_t l){
        switch(a.type){
            case TokenType::Identifier:{
                for(size_t i=l;i>0;i--){
                    VarKey tmp(a.str,i);
                    if(Variable::variables.contains(tmp)&&Variable::variables[tmp]!=nullptr)return true;
                }
                break;
            }
            case TokenType::ArrayElement:
            case TokenType::ObjectAttribute:
            case TokenType::Variable:return true;
            case TokenType::Number:return true;
            case TokenType::String:return true;
            case TokenType::Reference:return true;
            default:return false;
        }
        return false;
    }

    ValueType getValueType(const Token&a,size_t level){
        switch(a.type){
            case TokenType::Identifier:{
                for(size_t i=level;i>0;i--){
                    VarKey tmp(a.str,i);
                    if(Variable::variables.contains(tmp)&&Variable::variables[tmp]!=nullptr)return Variable::variables[tmp]->as;
                }
                break;
            }
            case TokenType::Variable:return a.as.var().as;break;
            case TokenType::ArrayElement:return a.as.ele().as;break;
            case TokenType::ObjectAttribute:return a.as.att().as;break;
            case TokenType::Number:{
                ValueType tmp;
                tmp.v=a.as.num();
                return tmp;
            }
            case TokenType::String:{
                ValueType tmp;
                tmp.v=std::make_unique<String>(a.as.str());
                return tmp;
            }
            case TokenType::Reference:{
                return*(a.as.ref().ref);
            }
            default:{
                ValueType tmp;
                tmp.v=Number(0);
                return tmp;
            }
        }
        ValueType tmp;
        tmp.v=Number(0);
        return tmp;
    }

    ValueType Na;

    ValueType&getValueTypeRef(Token&a,size_t level){
        switch(a.type){
            case TokenType::Identifier:{
                for(size_t i=level;i>0;i--){
                    VarKey tmp(a.str,i);
                    if(Variable::variables.contains(tmp)&&Variable::variables[tmp]!=nullptr)return Variable::variables[tmp]->as;
                }
                break;
            }
            case TokenType::Variable:return a.as.var().as;break;
            case TokenType::ArrayElement:return a.as.ele().as;break;
            case TokenType::ObjectAttribute:return a.as.att().as;break;
            case TokenType::Reference:return*(a.as.ref().ref);break;
            default:{
                Na.v=Number(0);
                return Na;
            }
        }
        Na.v=Number(0);
        return Na;
    }

    Type getType(const Token&a,size_t level){
        switch(a.type){
            case TokenType::Identifier:{
               
                for(size_t i=level;i>0;i--){
                    VarKey tmp(a.str,i);
                    
                    if(Variable::variables.contains(tmp)&&Variable::variables[tmp]!=nullptr)return Variable::variables[tmp]->getType();
                }
                break;
            }
            case TokenType::Variable:return a.as.var().getType();break;
            case TokenType::ArrayElement:return a.as.ele().getType();break;
            case TokenType::ObjectAttribute:return a.as.att().getType();break;
            case TokenType::Number:return Type::Number;break;
            case TokenType::String:return Type::String;break;
            case TokenType::Reference:return a.as.ref().ref_type;break;
            default:return Type::Null;
        }
        return Type::Null;
    }

    Type Nb=Type::Null;

    Type&getTypeRef(Token&a,size_t level){
        switch(a.type){
            case TokenType::Identifier:{
               
                for(size_t i=level;i>0;i--){
                    VarKey tmp(a.str,i);
                    
                    if(Variable::variables.contains(tmp)&&Variable::variables[tmp]!=nullptr)return Variable::variables[tmp]->type;
                }
                break;
            }
            case TokenType::Variable:return a.as.var().type;break;
            case TokenType::ArrayElement:return a.as.ele().type;break;
            case TokenType::ObjectAttribute:return a.as.att().type;break;
            case TokenType::Reference:return a.as.ref().ref_type;break;
            default:return Nb;
        }
        return Nb;
    }

    Number compair(const Token&left,const Token&right,size_t level){
        Type leftT=getType(left,level);
        Type rightT=getType(right,level);
        if(leftT!=rightT)return Number(0);
        ValueType leftV=getValueType(left,level);
        ValueType rightV=getValueType(right,level);
        switch(leftT){
            case Type::Number:return leftV.Num()==rightV.Num();
            case Type::Array:return leftV.Arr()==rightV.Arr();
            case Type::Object:return leftV.Obj()==rightV.Obj();
            case Type::String:return leftV.Str()==rightV.Str();
            case Type::Refence:return leftV.Ref()==rightV.Ref();
            default:return Number(0);
        }
        return Number(0);
    }

    bool isString(const Token&a,size_t level){
        switch(a.type){
            case TokenType::String:return true;break;
            case TokenType::Identifier:{
                for(size_t i=level;i>0;i--){
                    VarKey tmp(a.str,i);
                    if(Variable::variables.contains(tmp)&&Variable::variables[tmp]!=nullptr){
                        if(Variable::variables[tmp]->getType()==Type::String)return true;
                    }
                }
                return false;
                break;
            }
            case TokenType::Variable:return a.as.var().getType()==Type::String;break;
            case TokenType::ArrayElement:return a.as.ele().getType()==Type::String;break;
            case TokenType::ObjectAttribute:return a.as.att().getType()==Type::String;break;
            case TokenType::Reference:return a.as.ref().ref_type==Type::String;break;
            default:return false;
        }
        return false;
    }

    String getString(const Token&a,size_t level){
        String tmpS;
        switch(a.type){
            case TokenType::String:tmpS=a.as.str();break;
            case TokenType::Identifier:{
                for(size_t i=level;i>0;i--){
                    VarKey tmp(a.str,i);
                    if(Variable::variables.contains(tmp)&&Variable::variables[tmp]!=nullptr){
                        if(Variable::variables[tmp]->getType()==Type::String)tmpS=Variable::variables[tmp]->as.Str();
                    }
                }
                break;
            }
            case TokenType::Variable:tmpS=a.as.var().as.Str();break;
            case TokenType::ArrayElement:tmpS=a.as.ele().as.Str();break;
            case TokenType::ObjectAttribute:tmpS=a.as.att().as.Str();break;
            case TokenType::Reference:tmpS=a.as.ref().ref->Str();break;
            default:;
        }
        return tmpS;
    }

    Situation operate(Token&res,Operator ope,Token&left,Token&right,size_t level){
        bool leftCal=getCal(left,level);
        bool rightCal=getCal(right,level);
        switch(ope){
            case Operator::Addition:{
                if((leftCal&&rightCal)){
                    res.str="$";
                    res.type=TokenType::Number;
                    res.as.num()=toNumber(left,level)+toNumber(right,level);
                }
                else if(isString(left,level)&&isString(right,level)){
                    res.str="$";
                    res.type=TokenType::String;
                    res.as.v=getString(left,level)+getString(right,level);
                }
                else return Situation::NotCalcutalable;
                break;
            }
            case Operator::Subtraction:{
                if(!(leftCal&&rightCal))return Situation::NotCalcutalable;
                res.str="$";
                res.type=TokenType::Number;
                res.as.num()=toNumber(left,level)-toNumber(right,level);
                break;
            }
            case Operator::Multiplication:{
                if(!(leftCal&&rightCal))return Situation::NotCalcutalable;
                res.str="$";
                res.type=TokenType::Number;
                res.as.num()=toNumber(left,level)*toNumber(right,level);
                break;
            }
            case Operator::Division:{
                if(!(leftCal&&rightCal))return Situation::NotCalcutalable;
                res.str="$";
                res.type=TokenType::Number;
                res.as.num()=toNumber(left,level)/toNumber(right,level);
                break;
            }
            case Operator::Modulo:{
                if(!(leftCal&&rightCal))return Situation::NotCalcutalable;
                res.str="$";
                res.type=TokenType::Number;
                res.as.num()=toNumber(left,level)%toNumber(right,level);
                break;
            }
            case Operator::And:{
                if(!(leftCal&&rightCal))return Situation::NotCalcutalable;
                res.str="$";
                res.type=TokenType::Number;
                res.as.num()=toNumber(left,level)&&toNumber(right,level);
                break;
            }
            case Operator::Or:{
                if(!(leftCal&&rightCal))return Situation::NotCalcutalable;
                res.str="$";
                res.type=TokenType::Number;
                res.as.num()=toNumber(left,level)||toNumber(right,level);
                break;
            }
            case Operator::Equality:{
                res.str="$";
                res.type=TokenType::Number;
                res.as.num()=compair(left,right,level);
                break;
            }
            case Operator::Inequality:{
                res.str="$";
                res.type=TokenType::Number;
                res.as.num()=(!compair(left,right,level));
                break;
            }
            case Operator::GreaterThan:{
                if(!(leftCal&&rightCal))return Situation::NotCalcutalable;
                res.str="$";
                res.type=TokenType::Number;
                res.as.v=toNumber(left,level)>toNumber(right,level);
                break;
            }
            case Operator::LessThan:{
                if(!(leftCal&&rightCal))return Situation::NotCalcutalable;
                res.str="$";
                res.type=TokenType::Number;
                res.as.num()=toNumber(left,level)<toNumber(right,level);
                break;
            }
            case Operator::GreaterThanOrEqualTo:{
                if(!(leftCal&&rightCal))return Situation::NotCalcutalable;
                res.str="$";
                res.type=TokenType::Number;
                res.as.num()=toNumber(left,level)>=toNumber(right,level);
                break;
            }
            case Operator::LessThanOrEqualTo:{
                if(!(leftCal&&rightCal))return Situation::NotCalcutalable;
                res.str="$";
                res.type=TokenType::Number;
                res.as.num()=toNumber(left,level)<=toNumber(right,level);
                break;
            }
            case Operator::Assignment:{
                if(!assignable(left,level))return Situation::NotAssignable;
                if(!assigner(right,level))return Situation::NotAssigner;
                getValueTypeRef(left,level)=getValueType(right,level);
                getTypeRef(left,level)=getType(right,level);
                res.str=left.str;
                res.type=left.type;
                res.as=left.as;
                break;
            }
            case Operator::AdditionAssignment:{
                if(!assignable(left,level))return Situation::NotAssignable;
                if(!assigner(right,level))return Situation::NotAssigner;
                if((leftCal&&rightCal)){
                    getNumberRef(getValueTypeRef(left,level),getTypeRef(left,level))=getNumber(getValueType(left,level),getType(left,level))+getNumber(getValueType(right,level),getType(right,level));
                    res.str=left.str;
                    res.type=left.type;
                    res.as=left.as;
                }
                else if(isString(left,level)&&isString(right,level)){
                    getValueTypeRef(left,level).Str()=getValueType(left,level).Str()+getValueType(right,level).Str();
                    res.str=left.str;
                    res.type=left.type;
                    res.as=left.as;
                }
                else return Situation::NotCalcutalable;
                break;
            }
            case Operator::SubtractionAssignment:{
                if(!(leftCal&&rightCal))return Situation::NotCalcutalable;
                if(!assignable(left,level))return Situation::NotAssignable;
                if(!assigner(right,level))return Situation::NotAssigner;
                    getNumberRef(getValueTypeRef(left,level),getTypeRef(left,level))=getNumber(getValueType(left,level),getType(left,level))-getNumber(getValueType(right,level),getType(right,level));
                res.str=left.str;
                res.type=left.type;
                res.as=left.as;
                break;
            }
            case Operator::MultiplicationAssignment:{
                if(!(leftCal&&rightCal))return Situation::NotCalcutalable;
                if(!assignable(left,level))return Situation::NotAssignable;
                if(!assigner(right,level))return Situation::NotAssigner;
                    getNumberRef(getValueTypeRef(left,level),getTypeRef(left,level))=getNumber(getValueType(left,level),getType(left,level))*getNumber(getValueType(right,level),getType(right,level));
                res.str=left.str;
                res.type=left.type;
                res.as=left.as;
                break;
            }
            case Operator::DivisionAssignment:{
                if(!(leftCal&&rightCal))return Situation::NotCalcutalable;
                if(!assignable(left,level))return Situation::NotAssignable;
                if(!assigner(right,level))return Situation::NotAssigner;
                    getNumberRef(getValueTypeRef(left,level),getTypeRef(left,level))=getNumber(getValueType(left,level),getType(left,level))/getNumber(getValueType(right,level),getType(right,level));
                res.str=left.str;
                res.type=left.type;
                res.as=left.as;
                break;
            }
            case Operator::ModuloAssignment:{
                if(!(leftCal&&rightCal))return Situation::NotCalcutalable;
                if(!assignable(left,level))return Situation::NotAssignable;
                if(!assigner(right,level))return Situation::NotAssigner;
                    getNumberRef(getValueTypeRef(left,level),getTypeRef(left,level))=getNumber(getValueType(left,level),getType(left,level))%getNumber(getValueType(right,level),getType(right,level));
                res.str=left.str;
                res.type=left.type;
                res.as=left.as;
                break;
            }
            case Operator::ElementIndexing:{
                if(isString(left,level)){
                    if(!rightCal)return Situation::BadIndexing;
                    res.str="$";
                    res.type=TokenType::String;
                    res.as.v=getString(left,level).visitValue(toNumber(right,level).getSizeT());
                    break;
                }
                else{
                    switch(left.type){
                        case TokenType::Identifier:{
                            for(size_t i=level;i>0;i--){
                                VarKey tmp(left.str,i);
                                if(Variable::variables.contains(tmp)&&Variable::variables[tmp]!=nullptr)if(!isArray(Variable::variables[tmp]->as,Variable::variables[tmp]->type))return Situation::NotArray;
                            }
                            break;
                        }
                        case TokenType::Variable:if(!isArray(left.as.var().as,left.as.var().type))return Situation::NotArray;break;
                        case TokenType::ArrayElement:if(!isArray(left.as.ele().as,left.as.ele().type))return Situation::NotArray;break;
                        case TokenType::ObjectAttribute:if(!isArray(left.as.att().as,left.as.att().type))return Situation::NotArray;break;
                        default:return Situation::NotArray;
                    }
                    if(!rightCal)return Situation::BadIndexing;
                    size_t ind=toNumber(right,level).getSizeT();
                    Array&tmpA=getArrayRef(getValueTypeRef(left,level),getType(left,level));
                    if(ind>tmpA.getLength())return Situation::BadIndexing;
                    res.str="$";
                    res.type=TokenType::ArrayElement;
                    res.as.v=&tmpA.visitValue(ind);
                    break;
                }
            }
            case Operator::AttributeDereferencing:{
                if(right.type!=TokenType::Identifier)return Situation::BadAttribute;
                switch(left.type){
                    case TokenType::Identifier:{
                        for(size_t i=level;i>0;i--){
                            VarKey tmp(left.str,i);
                            if(Variable::variables.contains(tmp)&&Variable::variables[tmp]!=nullptr)if(Variable::variables[tmp]->getType()!=Type::Object)return Situation::NotObject;
                        }
                        break;
                    }
                    case TokenType::Variable:if(left.as.var().getType()!=Type::Object)return Situation::NotObject;break;
                    case TokenType::ArrayElement:if(left.as.ele().getType()!=Type::Object)return Situation::NotObject;break;
                    case TokenType::ObjectAttribute:if(left.as.att().getType()!=Type::Object)return Situation::NotObject;break;
                    default:return Situation::NotObject;
                }
                std::string tmpAt=right.str;
                Object&tmpO=getValueTypeRef(left,level).Obj();
                res.str="$";
                res.type=TokenType::ObjectAttribute;
                res.as.v=&tmpO.visitAttribute(tmpAt);
                break;
            }
            default:return Situation::BadBinaryOperator;
        }
        return Situation::Success;
    }

    Situation operate(Token&res,Operator ope,Token&right,size_t level){
        switch(ope){
            case Operator::Not:{
                switch(right.type){
                    case TokenType::Identifier:{
                        for(size_t i=level;i>0;i--){
                            VarKey tmp{right.str,i};
                            if(Variable::variables.contains(tmp)&&Variable::variables[tmp]!=nullptr){
                                right.type=TokenType::Variable;
                                right.as.v=Variable::variables[tmp];
                                if(!right.as.var().calculatable)return Situation::NotCalcutalable;
                                res.type=TokenType::Number;
                                if(right.as.var().getNumber()!=Number(0)){
                                    res.as.v=Number(0);
                                    res.str="0";
                                }
                                else{
                                    res.as.v=Number(1);
                                    res.str="1";
                                }
                                break;
                            }
                        }
                        break;
                    }
                    case TokenType::Variable:{
                        if(!right.as.var().calculatable)return Situation::NotCalcutalable;
                        res.type=TokenType::Number;
                        if(right.as.var().getNumber()!=Number(0)){
                            res.as.v=Number(0);
                            res.str="0";
                        }
                        else{
                            res.as.v=Number(1);
                            res.str="1";
                        }
                        break;
                    }
                    case TokenType::ArrayElement:{
                        if(!right.as.ele().calculatable)return Situation::NotCalcutalable;
                        res.type=TokenType::Number;
                        if(right.as.ele().getNumber()!=Number(0)){
                            res.as.v=Number(0);
                            res.str="0";
                        }
                        else{
                            res.as.v=Number(1);
                            res.str="1";
                        }
                        break;
                    }
                    case TokenType::ObjectAttribute:{
                        if(!right.as.att().calculatable)return Situation::NotCalcutalable;
                        res.type=TokenType::Number;
                        if(right.as.att().getNumber()!=Number(0)){
                            res.as.v=Number(0);
                            res.str="0";
                        }
                        else{
                            res.as.v=Number(1);
                            res.str="1";
                        }
                        break;
                    }
                    case TokenType::Number:{
                        if(!right.as.num().calculatable)return Situation::NotCalcutalable;
                        res.type=TokenType::Number;
                        if(right.as.num().getNumber()!=Number(0)){
                            res.as.v=Number(0);
                            res.str="0";
                        }
                        else{
                            res.as.v=Number(1);
                            res.str="1";
                        }
                        break;
                    }
                    default:return Situation::NotValue;
                }
                break;
            }
            default:return Situation::BadUnaryOperator;
        }
        return Situation::Success;
    }

    Situation Expression::calculate(){
        Tokens rev;
        std::stack<Token>stk;
        for(int i=0;i<t.size();i++){
            if(isValue(t[i]))rev.push_back(t[i]);
            if(t[i].str=="(")stk.push(t[i]);
            if(t[i].str==")"){
                while(!stk.empty()&&stk.top().str!="("){
                    rev.push_back(stk.top());
                    stk.pop();
                }
                if(stk.empty())return Situation::FailedReverse;
                stk.pop();
            }
            if(t[i].type==TokenType::Operator){
                if(getAssociativity(t[i].as.ope())==Associativity::Left)while(!stk.empty()&&stk.top().type==TokenType::Operator&&getPrecedence(stk.top().as.ope())>=getPrecedence(t[i].as.ope())){
                        rev.push_back(stk.top());
                        stk.pop();
                }
                else if(getAssociativity(t[i].as.ope())==Associativity::Right)while(!stk.empty()&&stk.top().type==TokenType::Operator&&getPrecedence(stk.top().as.ope())>getPrecedence(t[i].as.ope())){
                        rev.push_back(stk.top());
                        stk.pop();
                }
                stk.push(t[i]);
            }
        }
        while(!stk.empty()){
            rev.push_back(stk.top());
            stk.pop();
        }
        for(int i=0;i<rev.size();i++){
            if(isValue(rev[i]))stk.push(rev[i]);
            if(rev[i].type==TokenType::Operator){
                int arity=getArity(rev[i].as.ope());
                Token res;
                Situation si;
                if(arity==1){
                    if(stk.empty())return Situation::FailedCalaulation;
                    Token right=stk.top();
                    stk.pop();
                    si=operate(res,rev[i].as.ope(),right,stack_level);
                    if(si==Situation::Success)stk.push(res);
                    else return si;
                }
                else if(arity==2){
                    if(stk.empty())return Situation::FailedCalaulation;
                    Token right=stk.top();
                    stk.pop();
                    if(stk.empty())return Situation::FailedCalaulation;
                    Token left=stk.top();
                    stk.pop();
                    si=operate(res,rev[i].as.ope(),left,right,stack_level);
                    if(si==Situation::Success)stk.push(res);
                    else return si;
                }
            }
        }
        if(stk.size()!=1)return Situation::FailedCalaulation;
        v=stk.top();
        return Situation::Success;
    }

    std::ostream&operator<<(std::ostream&os,const Expression&a){
        ValueType val=getValueType(a.v,a.stack_level);
        Type ty=getType(a.v,a.stack_level); 
      
        switch(ty){
            case Type::Array:{
                os<<val.Arr();
                break;
            }
            case Type::Number:{
                os<<val.Num();
                break;
            }
            case Type::Object:{
                os<<val.Obj();
                break;
            }
            case Type::String:{
                os<<val.Str();
                break;
            }
            case Type::Refence:{
                os<<val.Ref();
                break;
            }
        }
        return os;
    }

    Situation Expression::getBool(bool&res){
        switch(v.type){
            case TokenType::Identifier:{
                for(size_t i=stack_level;i>0;i--){
                    VarKey tmp(v.str,i);
                    if(Variable::variables.contains(tmp)&&Variable::variables[tmp]!=nullptr){
                        Variable&tmpV=*Variable::variables[tmp];
                        if(tmpV.calculatable){
                            res=tmpV.getNumber();
                            return Situation::Success;
                        }
                        else return Situation::NotBoolean;
                    }
                }
                break;
            }
            case TokenType::Variable:{
                if(v.as.var().calculatable){
                    res=v.as.var().getNumber();
                    return Situation::Success;
                }
                else return Situation::NotBoolean;
                break;
            }
            case TokenType::ArrayElement:{
                if(v.as.ele().calculatable){
                    res=v.as.ele().getNumber();
                    return Situation::Success;
                }
                else return Situation::NotBoolean;
            }
            case TokenType::ObjectAttribute:{
                if(v.as.att().calculatable){
                    res=v.as.att().getNumber();
                    return Situation::Success;
                }
                else return Situation::NotBoolean;
            }
            case TokenType::Number:{
                res=v.as.num();
                return Situation::Success;
            }
            default:return Situation::NotBoolean;
        }
        return Situation::NotBoolean;
    }
}
