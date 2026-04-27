// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../statement.h"
#include"../../Tokenize/tokenize.h"
#include"../../Expression/expression.h"

namespace Oblivia{
	Execute::Execute(){
		type=StatementType::Execute;
		scope_level=0;
		tokens=Tokens();
		code="";
	}

	Execute::Execute(size_t l,const Tokens&t){
		type=StatementType::Execute;
		scope_level=l;
		tokens=t;
		code="";
	}

	bool Execute::isLegal(const Tokens&tokens){
		if(tokens.size()<3)return false;
		if(tokens[tokens.size()-1].type!=TokenType::SemiColon)return false;
		if(tokens[0].str!="execute")return false;
		Tokens tmp=tokens;
		tmp.pop_back();
		tmp.erase(tmp.begin());
		return isExpression(tmp);
	}

	Situation Execute::execute(Expression&ret,ExecuteResult&result,bool included){
		Tokens t=tokens;
		t.pop_back();
		t.erase(t.begin()); 
		Expression e(t,scope_level);
		Situation se=e.calculate();
		if(se!=Situation::Success)return se;
		Type ty=getType(e.v,scope_level);
		if(ty!=Type::String)return Situation::NotString;
		code=getValueType(e.v,scope_level).Str().getCont();
		Words w;
		Situation sw=tokenize(w,code);
		if(sw!=Situation::Success)return sw;
		Tokens to;
		Situation st=processToken(to,w);
		if(st!=Situation::Success)return st;
		if(!isStatement(to))return Situation::IlegalStatement;
		std::unique_ptr<Statement>stat;
		Situation sb=buildStatement(stat,scope_level+1,to);
		if(sb!=Situation::Success)return sb;
		stat->execute(ret,result);
		return Situation::Success;
	}

	Situation Execute::build(){
		return Situation::Success;
	}
}
