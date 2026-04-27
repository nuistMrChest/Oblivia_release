// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../checker.h"
#include"../tokenize.h"

namespace Oblivia{
	bool isNumberChar(char a){
		return(
			(a>='0'&&a<='9')||
			a=='.'
		);
	}

	bool isNumber(const std::string&a){
		if(a.size()<1)return false;
		int dot_count=0;
		for(int i=0;i<a.length();i++){
			if(!isNumberChar(a[i]))return false;
			if(a[i]=='.')dot_count++;
		}
		if(dot_count>1)return false;
		return true;
	}

	bool isKeyWord(const std::string&a){
		for(int i=0;i<keywords.size();i++)if(a==keywords[i])return true;
		return false;
	}

	bool isIdentifierChar(char a){
		return(
			(a>='a'&&a<='z')||
			(a>='A'&&a<='Z')||
			a=='_'
		);
	}

	bool isIdentifier(const std::string&a){
		for(int i=0;i<a.length();i++)if(!isIdentifierChar(a[i]))return false;
		return true;
	}

	bool isOperatorChar(char a){
		return(
			a=='+'||
			a=='-'||
			a=='*'||
			a=='/'||
			a=='%'||
			a=='='||
			a=='>'||
			a=='<'||
			a=='!'||
			a=='&'||
			a=='|'||
			a=='#'
		);
	}

	bool isOperator(const std::string&a){
		return(
			a=="+"||
			a=="-"||
			a=="*"||
			a=="/"||
			a=="%"||
			a=="="||
			a=="=="||
			a==">="||
			a=="<="||
			a=="!="||
			a==">"||
			a=="<"||
			a=="&&"||
			a=="||"||
			a=="!"||
			a=="+="||
			a=="-="||
			a=="*="||
			a=="/="||
			a=="%="||
			a=="#"||
			a=="->"
		);
	}

	bool isParenChar(char a){
		return a=='('||a==')';
	}

	bool isParen(const std::string&a){
		return a=="("||a==")";
	}

	bool isBracketChar(char a){
		return a=='['||a==']';
	}

	bool isBracket(const std::string&a){
		return a=="["||a=="]";
	}

	bool isBraceChar(char a){
		return a=='{'||a=='}';
	}

	bool isBrace(const std::string&a){
		return a=="{"||a=="}";
	}

	bool isArrow(const std::string&a){
		return a=="->";
	}

	bool isColonChar(char a){
		return a==':';
	}

	bool isColon(const std::string&a){
		return a==":";
	}

	bool isCommaChar(char a){
		return a==',';
	}

	bool isComma(const std::string&a){
		return a==",";
	}

	bool isSemiColonChar(char a){
		return a==';';
	}

	bool isSemiColon(const std::string&a){
		return a==";";
	}

	bool isDoubleQuoteChar(char a){
		return a=='\"';
	}

	bool isDoubleQuote(const std::string&a){
		return a=="\"";
	}

	bool isBackSlashChar(char a){
		return a=='\\';
	}

	bool isBackSlash(const std::string&a){
		return a=="\\";
	}

	bool isSpaceChar(char a){
		return a==' ';
	}
	
	bool isSpace(const std::string&a){
		return a==" ";
	}

	bool isCaretChar(char a){
		return a=='^';
	}

	bool isCaret(const std::string&a){
		return a=="^";
	}
	
	bool isAtChar(char a){
		return a=='@';
	}

	bool isAt(const std::string&a){
		return a=="@";
	}
}
