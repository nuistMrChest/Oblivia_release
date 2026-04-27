// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../statement.h"

namespace Oblivia{
	Else::Else(){
		type=StatementType::Else;
		scope_level=0;
		tokens=Tokens();
		linked=false;
		f=nullptr;
	}

	Else::Else(size_t l,const Tokens&t){
		type=StatementType::Else;
		scope_level=l;
		tokens=t;
		f=nullptr;
		linked=false;
		this->build();
	}

	Situation Else::execute(Expression&ret,ExecuteResult&result,bool included){
		result=ExecuteResult::Other;
		if(linked)f->execute(ret,result);
		return Situation::Success;
	}

	bool Else::isLegal(const Tokens&t){
		if(t.size()<2)return false;
		if(t[0].str!="else")return false;
		Tokens tmp=t;
		tmp.erase(tmp.begin());
		return isStatement(tmp);
	}

	Situation Else::build(){
		Tokens tmp=tokens;
		tmp.erase(tmp.begin());
		return buildStatement(f,scope_level+1,tmp);
	}
}
