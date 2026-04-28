// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef FUNCTION_CALL_H
#define FUNCTION_CALL_H

#include"value.h"
#include<string>
#include<vector>

namespace Oblivia{
	class Expression;

	class FunctionCall:public Value{
		public:
		std::string name;
		std::vector<Expression>arguments;
		Expression getReturn();

		FunctionCall();
		FunctionCall(const std::string&n,const std::vector<Expression>&as);
		void print(std::ostream&os)const;
	};
}

#endif
