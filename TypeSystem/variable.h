// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef VARIABLE_H
#define VARIABLE_H

#include"value.h"
#include<memory>
#include<string>
#include<unordered_map>
#include"number.h"
#include<variant>
#include<vector>

namespace Oblivia{
	class Array;
	class Object;
	class String;
	class Reference;
	class Function;

	struct ValueType{
		std::variant<
			Number,
			std::unique_ptr<Array>,
			std::unique_ptr<Object>,
			std::unique_ptr<String>,
			std::unique_ptr<Reference>,
			std::unique_ptr<Function>
		>v;
		std::vector<Reference*>refed_by;

		Number&Num();
		Array&Arr();
		Object&Obj();
		String&Str();
		Reference&Ref();
		Function&Fun();

		const Number&Num()const;
		const Array&Arr()const;
		const Object&Obj()const;
		const String&Str()const;
		const Reference&Ref()const;
		const Function&Fun()const;

		ValueType();
		ValueType(const ValueType&a);
		ValueType&operator=(const ValueType&a);
		~ValueType();
	};

	Number&getNumberRef(ValueType&a,Type t);
	Number getNumber(const ValueType&a,Type t);

	bool isArray(const ValueType&a,Type t);
	Array&getArrayRef(ValueType&a,Type t);
	Array getArray(const ValueType&a,Type t);

	struct VarKey{
		std::string name;
		size_t level;
		bool operator==(const VarKey&a)const;
		VarKey(const std::string&n,size_t l);
	};

	struct VarKeyHash{
		size_t operator()(const VarKey&a)const noexcept;
	};

	class Variable:public Calculatable{
		private:
		std::string name;
		size_t scope_level;
		public:
		Type type;
		ValueType as;
		static std::unordered_map<VarKey,Variable*,VarKeyHash>variables;
		Variable(size_t l,const std::string&n);
		Variable(size_t l,const std::string&n,const Number&v);
		Variable(size_t l,const std::string&n,const Array&v);
		Variable(size_t l,const std::string&n,const Object&v);
		Variable(size_t l,const std::string&n,const String&v);
		Variable(size_t l,const std::string&n,const Reference&v);
		Variable(size_t l,const std::string&n,const Function&v);
		Number&getNumber();
		const Number&getConstNumber()const;
		Type getType()const;
	};
}

#endif
