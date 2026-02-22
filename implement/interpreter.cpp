// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../interpreter.h"
#include<string>
#include<fstream>
#include<iostream>
#include"../TypeSystem/type_system.h"
#include"../Tokenize/tokenize.h"
#include"../Statement/statement.h"
#include"../Situation/situation.h"
#include"../Expression/expression.h"
#include<memory>
#include<iterator>

namespace Oblivia{
    void interpreter(const std::string&path){
        std::ifstream fin(path);
        if(!fin){
            std::cout<<"Path not found"<<std::endl;
            return;
        }
        std::string input{std::istreambuf_iterator<char>(fin),std::istreambuf_iterator<char>()};
        Words w;
        Situation sw=tokenize(w,input);
        if(sw!=Situation::Success){
            std::cout<<sw<<std::endl;
            return;
        }
        Tokens t;
        Situation st=processToken(t,w);
        if(st!=Situation::Success){
            std::cout<<st<<std::endl;
            return;
        }
        if(!isStatement(t)){
            std::cout<<"Ilegal Statement"<<std::endl;
            return;
        }
        std::unique_ptr<Statement>stat;
        Situation sb=buildStatement(stat,1,t);
        if(sb!=Situation::Success){
            std::cout<<sb<<std::endl;
        }
        ExecuteResult er;
        stat->execute(er);
    }
}