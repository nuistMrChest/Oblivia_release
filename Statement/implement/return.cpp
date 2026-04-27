// Copyright (c) 2026 MrChest
// Licensed under the MIT License

#include"../statement.h"

namespace Oblivia{
	Return::Return(){
		type=StatementType::Return;
		scope_level=0;
		tokens=Tokens();
		ret_val=Expression();
	}

	Return::Return(size_t l,const Tokens&t){
		type=StatementType::Return;
		scope_level=l;
		tokens=t;
		ret_val=Expression();
		this->build();
}

	bool Return::isLegal(const Tokens&t){
		if(t.size()<2)return false;
		if(t[0].str!="return")return false;
		if(t[t.size()-1].type!=TokenType::SemiColon)return false;
		Tokens tmp=t;
		tmp.pop_back();
		tmp.erase(tmp.begin());
		return isExpression(tmp);
	}

	Situation Return::execute(
			Expression&ret,
			ExecuteResult&result,
			bool included
		){
		Situation cs=ret_val.calculate();
		if(cs!=Situation::Success)return cs;
		ret=ret_val;
		result=ExecuteResult::Return;
		return Situation::Success;
	}

	Situation Return::build(){
		Tokens tmp=tokens;
		tmp.pop_back();
		tmp.erase(tmp.begin());
		ret_val=Expression(tmp,scope_level);
	}
}
