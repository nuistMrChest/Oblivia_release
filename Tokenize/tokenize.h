// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef TOKENIZE_H
#define TOKENIZE_H

#include<string>
#include<vector>
#include"../TypeSystem/type_system.h"
#include<iostream>
#include"../Situation/situation.h"
#include<variant>
#include<memory>

namespace Oblivia{
	typedef std::vector<std::string>Words;

	inline const Words keywords={
		"let",
		"print",
		"scan",
		"if",
		"else",
		"while",
		"break",
		"continue",
		"borrow",
		"move",
		"include",
		"return",
		"ifn"
	};

	enum class TokenType{
		Null,

		Value,
		
		Number,
		Identifier,
		Operator,
		Paren,
		Bracket,
		Brace,
		Arrow,
		Colon,
		Comma,
		SemiColon,

		BadToken,
		
		Variable,
		ArrayElement,
		ObjectAttribute,
		FunctionCall,

		DoubleQuote,
		BackSlash,
		String,
		Space,

		Caret,
		At,

		Object,
		Array,

		Reference
	};

	std::ostream&operator<<(std::ostream&os,const TokenType&a);

	Situation tokenize(Words&r,const std::string&a);

	struct Token{
		std::string str;
		TokenType type;
		struct TokenValue{
			std::variant<
				Number,
				Variable*,
				ArrayElement*,
				Attribute*,
				Operator,
				String,
				Object,
				Array,
				Reference,
				FunctionCall
			>v;

			Number&num();
			Variable&var();
			ArrayElement&ele();
			Attribute&att();
			Operator&ope();
			String&str();
			Object&obj();
			Array&arr();
			Reference&ref();
			FunctionCall&fc();

			const Number&num()const;
			const Variable&var()const;
			const ArrayElement&ele()const;
			const Attribute&att()const;
			const Operator&ope()const;
			const String&str()const;
			const Object&obj()const;
			const Array&arr()const;
			const Reference&ref()const;
			const FunctionCall&fc()const;
		}as;
		Token();
	};

	typedef std::vector<Token> Tokens;

	Situation processToken(Tokens&r,const Words&a);

	Situation processFunctionCall(Token&r,const Tokens&a);

	Situation processLiteral(Tokens&r,const Tokens&a);
}

#endif
