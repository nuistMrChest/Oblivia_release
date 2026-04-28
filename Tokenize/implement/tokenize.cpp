// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../tokenize.h"
#include"../checker.h"
#include<string>
#include<vector>
#include<algorithm>
#include<stack>
#include<utility>
#include"../../Expression/expression.h"

namespace Oblivia{
	std::ostream&operator<<(std::ostream&os,const TokenType&a){
		switch(a){
			case TokenType::Null:os<<"Null";break;
			case TokenType::Value:os<<"Value";break;
			case TokenType::Number:os<<"Number";break;
			case TokenType::Identifier:os<<"Identifier";break;
			case TokenType::Operator:os<<"Operator";break;
			case TokenType::Paren:os<<"Paren";break;
			case TokenType::Bracket:os<<"Bracket";break;
			case TokenType::Brace:os<<"Brace";break;
			case TokenType::Arrow:os<<"Arrow";break;
			case TokenType::Colon:os<<"Colon";break;
			case TokenType::Comma:os<<"Comma";break;
			case TokenType::SemiColon:os<<"SemiColon";break;
			case TokenType::BadToken:os<<"MotherFucker";break;
			case TokenType::Variable:os<<"Variable";break;
			case TokenType::ArrayElement:os<<"ArrayElement";break;
			case TokenType::ObjectAttribute:os<<"ObjectAttribute";break;
			case TokenType::FunctionCall:os<<"FunctionCall";break;
			case TokenType::DoubleQuote:os<<"DoubleQuote";break;
			case TokenType::BackSlash:os<<"BackSlash";break;
			case TokenType::String:os<<"String";break;
			case TokenType::Space:os<<"Space";break;
			case TokenType::Caret:os<<"Caret";break;
			case TokenType::At:os<<"At";break;
			case TokenType::Object:os<<"Object";break;
			case TokenType::Array:os<<"Array";break;
			case TokenType::Reference:os<<"Reference";break;
		}
		return os;
	}

	Situation tokenize(Words&r,const std::string&a){
		TokenType type=TokenType::Null;
		TokenType last_type=TokenType::Null;
		std::string tmp="";
		Words res;
		for(size_t i=0;i<a.length();i++){
			if(isNumberChar(a[i]))type=TokenType::Number;
			else if(isOperatorChar(a[i]))type=TokenType::Operator;
			else if(isIdentifierChar(a[i]))type=TokenType::Identifier;
			else if(isBracketChar(a[i]))type=TokenType::Bracket;
			else if(isBraceChar(a[i]))type=TokenType::Brace;
			else if(isParenChar(a[i]))type=TokenType::Paren;
			else if(isColonChar(a[i]))type=TokenType::Colon;
			else if(isSemiColonChar(a[i]))type=TokenType::SemiColon;
			else if(isCommaChar(a[i]))type=TokenType::Comma;
			else if(isDoubleQuoteChar(a[i]))type=TokenType::DoubleQuote;
			else if(isBackSlashChar(a[i]))type=TokenType::BackSlash;
			else if(isSpaceChar(a[i]))type=TokenType::Space;
			else if(isCaretChar(a[i]))type=TokenType::Caret;
			else if(isAtChar(a[i]))type=TokenType::At;
			else if(a[i]=='\t'||a[i]=='\n'||a[i]=='\r'){
				if(!tmp.empty()){
					res.push_back(tmp);
					tmp.clear();
				}
				continue;
			}
			else type=TokenType::Null;
			if(type!=last_type&&!tmp.empty()){
				res.push_back(tmp);
				tmp.clear();
			}
			tmp.push_back(a[i]);
			last_type=type;
		}
		if(!tmp.empty()){
			res.push_back(tmp);
		}

		Words final_res;
		while(!res.empty()){
			if(isBracketChar(res[0][0])||(res[0].length()>=2&&res[0][1]=='!'))while(!res[0].empty()){
				std::string tmp_str;
				tmp_str+=res[0][0];
				final_res.push_back(tmp_str);
				res[0].erase(0,1);
			}
			else if(isParenChar(res[0][0])||(res[0].length()>=2&&res[0][1]=='!'))while(!res[0].empty()){
				std::string tmp_str;
				tmp_str+=res[0][0];
				final_res.push_back(tmp_str);
				res[0].erase(0,1);
			}
			else if(isSpaceChar(res[0][0])||(res[0].length()>=2&&res[0][1]=='!'))while(!res[0].empty()){
				std::string tmp_str;
				tmp_str+=res[0][0];
				final_res.push_back(tmp_str);
				res[0].erase(0,1);
			}
			else if(isDoubleQuoteChar(res[0][0])||(res[0].length()>=2&&res[0][1]=='!'))while(!res[0].empty()){
				std::string tmp_str;
				tmp_str+=res[0][0];
				final_res.push_back(tmp_str);
				res[0].erase(0,1);
			}
			else if(isBackSlashChar(res[0][0])||(res[0].length()>=2&&res[0][1]=='!'))while(!res[0].empty()){
				std::string tmp_str;
				tmp_str+=res[0][0];
				final_res.push_back(tmp_str);
				res[0].erase(0,1);
			}
			else if(isSemiColonChar(res[0][0])||(res[0].length()>=2&&res[0][1]=='!'))while(!res[0].empty()){
				std::string tmp_str;
				tmp_str+=res[0][0];
				final_res.push_back(tmp_str);
				res[0].erase(0,1);
			}
			else if(isBraceChar(res[0][0])||(res[0].length()>=2&&res[0][1]=='!'))while(!res[0].empty()){
				std::string tmp_str;
				tmp_str+=res[0][0];
				final_res.push_back(tmp_str);
				res[0].erase(0,1);
			}
			else if(res[0].length()>=3&&res[0][1]!='!'&&res[0][2]=='!'){
				std::string tmp_str;
				tmp_str+=res[0][0];
				tmp_str+=res[0][1];
				final_res.push_back(tmp_str);
				res[0].erase(0,2);
				while(!res[0].empty()){
					tmp_str="";
					tmp_str+=res[0][0];
					final_res.push_back(tmp_str);
					res[0].erase(0,1);
				}
			}
			else{
				final_res.push_back(res[0]);
				res.erase(res.begin());
			}
		}
		final_res.erase(
			std::remove(
				final_res.begin(),
				final_res.end(),
				""
			),
			final_res.end()
		);
		r=std::move(final_res);
		return Situation::Success;
	}

	Situation processToken(Tokens&r,const Words&a){
		Tokens tmpT;
		tmpT.clear();
		for(size_t i=0;i<a.size();i++){
			Token tmp;
			tmp.str=a[i];
			if(isNumber(a[i])){
				tmp.type=TokenType::Number;
				tmp.as.v=Number(a[i]);
			}
			else if(isSpace(a[i]))tmp.type=TokenType::Space;
			else if(isIdentifier(a[i]))tmp.type=TokenType::Identifier;
			else if(isOperator(a[i])){
				tmp.type=TokenType::Operator;
				tmp.as.v=toOperator(a[i]);
			}
			else if(isParen(a[i]))tmp.type=TokenType::Paren;
			else if(isBracket(a[i]))tmp.type=TokenType::Bracket;
			else if(isBrace(a[i]))tmp.type=TokenType::Brace;
			else if(isColon(a[i]))tmp.type=TokenType::Colon;
			else if(isComma(a[i]))tmp.type=TokenType::Comma;
			else if(isSemiColon(a[i]))tmp.type=TokenType::SemiColon;
			else if(isBackSlash(a[i]))tmp.type=TokenType::BackSlash;
			else if(isDoubleQuote(a[i]))tmp.type=TokenType::DoubleQuote;
			else if(isCaret(a[i]))tmp.type=TokenType::Caret;
			else if(isAt(a[i]))tmp.type=TokenType::At;
			else tmp.type=TokenType::Null;
			tmpT.push_back(tmp);
		}
		bool in_ind=false;
		for(auto it=tmpT.begin();it!=tmpT.end();it++){
			if(in_ind&&it->str=="]"){
				in_ind=false;
				it->str=")";
				it->type=TokenType::Paren;
			}
			if(!(it==tmpT.begin()||((it-1)->type==TokenType::At||(it-1)->type==TokenType::Caret)))if(it->str=="["){
				in_ind=true;
				it->str="(";
				it->type=TokenType::Paren;
				Token sharp;
				sharp.str="#";
				sharp.type=TokenType::Operator;
				sharp.as.v=Operator::ElementIndexing;
				it=tmpT.insert(it, sharp);
				it++;
			}
		}
		for(size_t i=0;i<tmpT.size();i++){
			if(tmpT[i].type==TokenType::BackSlash){
				if(i+1>=tmpT.size())return Situation::BadEscape;
				tmpT[i+1].str.insert(0,"\\");
				tmpT[i+1].type=TokenType::Null;
				tmpT.erase(tmpT.begin()+i);
			}
		}
		for(size_t i=0;i<tmpT.size();){
			if(tmpT[i].type==TokenType::DoubleQuote){
				size_t start=i;
				size_t j=i+1;
				std::string tmpS;
				while(j<tmpT.size()&&tmpT[j].type!=TokenType::DoubleQuote){
					tmpS+=tmpT[j].str;
					j++;
				}
				if(j>=tmpT.size()){
					return Situation::BadString;
					break;
				}
				tmpT[j].str=tmpS;
				tmpT[j].type=TokenType::String;
				
				for(size_t k=0;k<tmpT[j].str.length();k++){
					if(tmpT[j].str[k]=='\\'){
						if(k+1>=tmpT[j].str.length())return Situation::BadEscape;
						switch(tmpT[j].str[k+1]){
							case 'n':tmpT[j].str[k+1]='\n';break;
							case '\"':break;
							case 'a':tmpT[j].str[k+1]='\a';break;
							case 'b':tmpT[j].str[k+1]='\b';break;
							case 'f':tmpT[j].str[k+1]='\f';break;
							case 'r':tmpT[j].str[k+1]='\r';break;
							case 't':tmpT[j].str[k+1]='\t';break;
							case 'v':tmpT[j].str[k+1]='\v';break;
							case '\\':break;
							default:return Situation::BadEscape;
						}
						tmpT[j].str.erase(k,1);
					}
				}
				
				tmpT[j].as.v=String(tmpT[j].str);

				tmpT.erase(tmpT.begin()+start,tmpT.begin()+j);
				i=start+1;
				continue;
			}
			++i;
		}
		tmpT.erase(
			std::remove_if(
				tmpT.begin(),
				tmpT.end(),
				[](const Token&a){return a.str==" ";}
			),tmpT.end()
		);
		r=std::move(tmpT);
		return Situation::Success;
	}

	Token::Token(){
		str="";
		type=TokenType::Null;
	}

	Number&Token::TokenValue::num(){
		if(!std::holds_alternative<Number>(v))v.emplace<Number>();
		return std::get<Number>(v);
	}

	Variable&Token::TokenValue::var(){
		return*std::get<Variable*>(v);
	}

	ArrayElement&Token::TokenValue::ele(){
		return*std::get<ArrayElement*>(v);
	}

	Attribute&Token::TokenValue::att(){
		return*std::get<Attribute*>(v);
	}

	Operator&Token::TokenValue::ope(){
		return std::get<Operator>(v);
	}

	String&Token::TokenValue::str(){
		return std::get<String>(v);
	}

	Object&Token::TokenValue::obj(){
		return std::get<Object>(v);
	}

	Array&Token::TokenValue::arr(){
		return std::get<Array>(v);
	}

	Reference&Token::TokenValue::ref(){
		return std::get<Reference>(v);
	}

	FunctionCall&Token::TokenValue::fc(){
		return std::get<FunctionCall>(v);
	}

	const Number&Token::TokenValue::num()const{
		return std::get<Number>(v);
	}

	const Variable&Token::TokenValue::var()const{
		return*std::get<Variable*>(v);
	}

	const ArrayElement&Token::TokenValue::ele()const{
		return*std::get<ArrayElement*>(v);
	}

	const Attribute&Token::TokenValue::att()const{
		return*std::get<Attribute*>(v);
	}

	const Operator&Token::TokenValue::ope()const{
		return std::get<Operator>(v);
	}

	const String&Token::TokenValue::str()const{
		return std::get<String>(v);
	}

	const Object&Token::TokenValue::obj()const{
		return std::get<Object>(v);
	}

	const Array&Token::TokenValue::arr()const{
		return std::get<Array>(v);
	} 
	
	const Reference&Token::TokenValue::ref()const{
		return std::get<Reference>(v);
	}

	const FunctionCall&Token::TokenValue::fc()const{
		return std::get<FunctionCall>(v);
	}

	Situation createObject(Token&res,const Tokens&a){
		return Situation::Test;
	}

	Situation createArray(Token&res,const Tokens&a){
		return Situation::Test;
	}

	Situation processLiteral(Tokens&r,const Tokens&a){
		return Situation::Success;
	}

//here!!!!!!!!!!!!!!!!
	Situation processFunctionCall(Token&r,const Tokens&a){
		if(
			a.size()<3&&
			a[0].type!=TokenType::Identifier&&
			a[1].str!="("&&a[a.size()-1].str!=")"
		)return Situation::BadFunctionCall;
		return Situation::Success;
	}
}
