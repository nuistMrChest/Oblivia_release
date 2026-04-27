// Copyright (c) 2026 MrChest
// Licensed under the MIT License

#include"../function.h"
#include"../../Statement/statement.h"
#include <memory>
#include <vector>

namespace Oblivia{
	Function::Function(){
		type=Type::Function;
	}

	Function::Function(const std::vector<std::string>&as,const std::unique_ptr<IFn>&b){
		type=Type::Function;
		arguments=as;
		body=std::make_unique<IFn>(*b);
	}

	Function::Function(const Function&a){
		this->type=a.type;
		this->arguments=a.arguments;
		this->body=std::make_unique<IFn>(*a.body);
	}

	Function&Function::operator=(const Function&a){
		this->type=a.type;
		this->arguments=a.arguments;
		this->body=std::make_unique<IFn>(*a.body);
		return*this;
	}

	void Function::print(std::ostream&os)const{
		os<<"function with arguments: ";
		for(size_t i=0;i<arguments.size();i++)os<<arguments[i]<<" ";
	}
}
