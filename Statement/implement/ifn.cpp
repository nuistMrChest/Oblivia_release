// Copyright (c) 2026 MrChest
// Licensed under the MIT License

#include"../statement.h"
#include"../../TypeSystem/function.h"
#include <memory>

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

	IFn::IFn(const IFn&a){
		this->type=a.type;
		this->scope_level=a.scope_level;
		this->tokens=a.tokens;
		this->arguments=a.arguments;
		buildStatement(this->body,scope_level+1,a.body->tokens);
	}

	Situation IFn::build(){
		size_t paren_quote=1;
		Token buf;
		size_t i=3;
		while(i<tokens.size()){
			if(tokens[i].str=="(")paren_quote++;
			if(tokens[i].str==")")paren_quote--;
			if(paren_quote==0)break;
			if(tokens[i].type==TokenType::Comma)arguments.push_back(buf.str);
			else buf=tokens[i];
			i++;
		}
		Tokens b;
		while(i<tokens.size()){
			b.push_back(tokens[i]);
			i++;
		}
		return buildStatement(body,scope_level+1,b);
	}

	bool IFn::isLegal(const Tokens&t){
		if(t.size()<5)return false;
		if(t[0].str!="ifn")return false;
		if(t[1].type!=TokenType::Identifier)return false;
		if(t[2].str!="(")return false;
		size_t paren_quote=1;
		size_t i=3;
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
		while(i<t.size()){
			b.push_back(t[i]);
			i++;
		}
		return isStatement(b);
	}

	Situation IFn::execute(Expression&ret,ExecuteResult&result,bool included){
		result=ExecuteResult::Other;
		for(auto i=Variable::variables.begin();i!=Variable::variables.end();i++){
			if(i->first.level==scope_level&&i->first.name==name)
				return Situation::UsedIdentifier;
		}
		Variable*var=new Variable(scope_level,name);
		var->type=Type::Function;
		var->as.v=std::make_unique<Function>(arguments,std::make_unique<IFn>(*this));
		return Situation::Success;
	}
}
