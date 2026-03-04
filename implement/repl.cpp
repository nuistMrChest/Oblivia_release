// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include"../repl.h"
#include<string>
#include<iostream>
#include"../TypeSystem/type_system.h"
#include"../Tokenize/tokenize.h"
#include"../Statement/statement.h"
#include"../Situation/situation.h"
#include"../Expression/expression.h"
#include<memory>

namespace Oblivia{
    bool isCommand(const std::string&a){
        return(
            a=="/exit"||
            a=="/help"
        );
    }

    Command toCommand(const std::string&a){
        if(a=="/exit")return Command::Exit;
        else if(a=="/help")return Command::Help;
        else return Command::Null;
    }

    void REPL(){
        std::string input;
        std::cout<<"Oblivia REPL v0.4.0"<<std::endl<<"By MrChest form NUIST"<<std::endl;
        while(1){
            std::cout<<">>";
            std::getline(std::cin,input);
            if(isCommand(input)){
                Command cmd=toCommand(input);
                if(cmd==Command::Exit)break;
                else if(cmd==Command::Help){
                    std::cout<<"Help system not implemented"<<std::endl;
                    continue;
                }
            }
            Words w;
            Situation sw=tokenize(w,input);
            if(sw!=Situation::Success){
                std::cout<<sw<<std::endl;
                continue;
            }
            Tokens t;
            Situation st=processToken(t,w);
            if(st!=Situation::Success){
                std::cout<<st<<std::endl;
                continue;
            }
            if(!isStatement(t)){
                std::cout<<"Ilegal Statement"<<std::endl;
                continue;
            }
            std::unique_ptr<Statement>stat;
            Situation sb=buildStatement(stat,1,t);
            if(sb!=Situation::Success){
                std::cout<<sb<<std::endl;
            }
            ExecuteResult er;
            Situation se=stat->execute(er);
            std::cout<<se<<std::endl;
        }
    }
}