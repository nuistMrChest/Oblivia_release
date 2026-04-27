// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../statement.h"
#include<iostream>
#include<stack>

namespace Oblivia{
	Block::Block(){
		scope_level=0;
		type=StatementType::Block;
		tokens=Tokens();
		subStates=std::vector<std::unique_ptr<Statement>>();
	}

	Block::Block(size_t l,const Tokens&t){
		scope_level=l;
		type=StatementType::Block;
		tokens=t;
		this->build();
	}

	Situation Block::execute(Expression&ret,ExecuteResult&result,bool included){
		for(int i=0;i<subStates.size();i++){
			if(subStates[i]->type==StatementType::Else)continue;
			Situation tmp=subStates[i].get()->execute(ret,result);
			if(
				result==ExecuteResult::ContinueLoop||
				result==ExecuteResult::EndLoop||
				result==ExecuteResult::Return
			)
				return tmp;
			if(tmp!=Situation::Success&&tmp!=Situation::Test){
				std::cout<<tmp<<std::endl;
				std::cout<<*subStates[i].get()<<std::endl;
			}
			if(tmp==Situation::Test){
				std::cout<<tmp<<std::endl;
				std::cout<<*subStates[i].get()<<std::endl;
			}
		}
		if(!included)
			for(auto i=Variable::variables.begin();i!=Variable::variables.end();i++){
				if(i->first.level==this->scope_level+1){
					delete i->second;
					i->second=nullptr;
				}
			}
		return Situation::Success;
	}

	bool Block::isLegal(const Tokens&tokens){
		if(tokens.size()<3)return false;
		if(tokens[0].str!="{"||tokens[tokens.size()-1].str!="}")return false;
		Tokens tmp;
		int braceCnt=0;
		for(int i=1;i<tokens.size()-1;i++){
			tmp.push_back(tokens[i]);
			if(tokens[i].str=="{")braceCnt++;
			if(tokens[i].str=="}")braceCnt--;
			if((tokens[i].type==TokenType::SemiColon||tokens[i].str=="}")&&braceCnt==0){
				if(!isStatement(tmp))return false;
				tmp.clear();
			}
			if(braceCnt<0)return false;
		}
		if(!tmp.empty()&&!isStatement(tmp))return false;
		if(braceCnt!=0)return false;
		return true;
	}

	Situation Block::build(){
		Tokens &t=tokens;
		if(t[0].str=="{"&&t[t.size()-1].str=="}"){
			Tokens tmp;
			int braceCnt=0;
			for(int i=1;i<t.size()-1;i++){
				tmp.push_back(t[i]);
				if(t[i].str=="{")braceCnt++;
				if(t[i].str=="}")braceCnt--;
				if((t[i].type==TokenType::SemiColon||t[i].str=="}")&&braceCnt==0){
					if(isStatement(tmp)){
						std::unique_ptr<Statement>tmpS;
						Situation sit=buildStatement(tmpS,scope_level+1,tmp);
						if(sit==Situation::Success)subStates.push_back(std::move(tmpS));
						else return sit;
						tmp.clear();
					}
					else return Situation::BadStatement;
				}
			}
			return linkElse();
		}
		return Situation::BadToken;
	}

	Situation Block::linkElse(){
		std::stack<size_t>if_ind;
		for(int i=0;i<subStates.size();i++){
			if(subStates[i]->type==StatementType::If)if_ind.push(i);
			if(subStates[i]->type==StatementType::Else){
				if(if_ind.empty())return Situation::UnlinkedElse;
				subStates[i]->linked=true;
				subStates[if_ind.top()]->have_else=true;
				subStates[if_ind.top()]->e=&(*subStates[i]);
				if_ind.pop();
			}
		}
		return Situation::Success;
	}
}
