// Copyright (c) 2026 MrChest
// Licensed under the MIT License

#include"../statement.h"

namespace Oblivia{
	IFn::IFn(){
		type=StatementType::IFn;
		scope_level=0;
		tokens=Tokens();
	}

	IFn::IFn(size_t l,const Tokens&t){
		type=StatementType::IFn;
		scope_level=l;
		tokens=t;
		build();
	}

	Situation IFn::build(){
		size_t paren_quote=0;
		Token buf;
		size_t i=2;
		while(i<tokens.size()){
			if(tokens[i].str=="(")paren_quote++;
			if(tokens[i].str==")")paren_quote--;
			if(paren_quote==0)break;
			if(tokens[i].type==TokenType::Comma)arguments.push_back(buf.str);
			else buf=tokens[i];
			i++;
		}
		i++;
		Tokens b;
		while(i<tokens.size()){
			b.push_back(tokens[i]);
			i++;
		}
		return buildStatement(body,scope_level+1,b);
	}

	bool IFn::isLegal(const Tokens&t){
		size_t paren_quote=0;
		size_t i=2;
		TokenType cur=TokenType::Null;
		TokenType last=TokenType::Null;
		while(i<t.size()){
			if(t[i].str=="(")paren_quote++;
			if(t[i].str==")"){
				if(paren_quote==0)return false;
				paren_quote--;
			}
			if(paren_quote==0)break;
			else{
				if(t[i].type!=TokenType::Identifier&&t[i].type!=TokenType::Comma)
					return false;
				cur=t[i].type;
				if(cur==last)return false;
				last=cur;
			}
			i++;
		}
		i++;
		Tokens b;
		return isStatement(b);
	}

	Situation IFn::execute(Expression&ret,ExecuteResult&result,bool included){
	}
}
