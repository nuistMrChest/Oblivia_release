// Copyright (c) 2026 MrChest
// Licensed under the MIT License

#include"../function_call.h"
#include"../../Expression/expression.h"
#include"../../Situation/situation.h"

namespace Oblivia{
	FunctionCall::FunctionCall(){
		type=Type::FunctionCall;
	}

	FunctionCall::FunctionCall(const std::string&n,const std::vector<Expression>&as):
		arguments(as),
		name(n)
	{
		type=Type::FunctionCall;
	}

	void FunctionCall::print(std::ostream&os)const{
		os<<name;
	}

	Situation FunctionCall::call(Expression&res){
		return Situation::Test;
	}
}
