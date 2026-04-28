// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef FUNCTION_CALL_H
#define FUNCTION_CALL_H

#include"value.h"
#include<string>
#include<vector>

namespace Oblivia{
	class Expression;
	enum class Situation;

	class FunctionCall:public Value{
		public:
		std::string name;
		std::vector<Expression>arguments;
		Situation call(Expression&res);

		FunctionCall();
		FunctionCall(const std::string&n,const std::vector<Expression>&as);
		void print(std::ostream&os)const;
	};
}

#endif
