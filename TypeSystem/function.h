// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef FUNCTION_H
#define FUNCTION_H

#include"value.h"
#include<string>
#include<vector>
#include<memory>

namespace Oblivia{
	class IFn;

	class Function:public Value{
		public:
		std::vector<std::string>arguments;
		std::unique_ptr<IFn>body;
		Function();
		Function(const std::vector<std::string>&as,const std::unique_ptr<IFn>&b);
		Function(const Function&a);
		Function&operator=(const Function&a);
		void print(std::ostream&os)const;
	};
}

#endif
