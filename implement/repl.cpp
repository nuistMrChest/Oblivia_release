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
            a=="/help"||
            a=="/list_variables"||
            a=="/scope_up"||
            a=="/scope_down"||
            a=="/scope"
        );
    }

    Command toCommand(const std::string&a){
        if(a=="/exit")return Command::Exit;
        else if(a=="/help")return Command::Help;
        else if(a=="/list_variables")return Command::LiseVariables;
        else if(a=="/scope_up")return Command::ScopeUp;
        else if(a=="/scope_down")return Command::ScopeDown;
        else if(a=="/scope")return Command::Scope;
        else return Command::Null;
    }

    void REPL(){
        size_t scope_level=1;
        std::string input;
        std::cout<<"Oblivia REPL v0.5.0"<<std::endl<<"By MrChest from NUIST"<<std::endl<<"Type \"/help\" for help\n";
        while(1){
            std::cout<<">>";
            std::getline(std::cin,input);
            if(isCommand(input)){
                Command cmd=toCommand(input);
                if(cmd==Command::Exit)break;
                else if(cmd==Command::Help){
                    std::cout<<"/help:show help information\n/exit:exit repl\n/list_variables:show all existing variables\n/scope:show current scope level\n/scope_up:increase scope level\n/scope_down:decrease scope level"<<std::endl;
                    continue;
                }
                else if(cmd==Command::LiseVariables){
                    std::cout<<"Existing Variables:\n";
                    for(auto i=Variable::variables.begin();i!=Variable::variables.end();++i){
                        if(i->second!=nullptr)std::cout<<i->first.name<<" "<<i->first.level<<" "<<i->second->type<<"\n";
                    }
                    continue;
                }
                else if(cmd==Command::ScopeUp){
                    ++scope_level;
                    std::cout<<"Current scope level: "<<scope_level<<"\n";
                    continue;
                }
                else if(cmd==Command::ScopeDown){
                    if(scope_level<=1){
                        std::cout<<"Cannot down grade scope level\n";
                    }
                    else{
                        for(auto i=Variable::variables.begin();i!=Variable::variables.end();i++){
                            if(i->first.level==scope_level)i->second=nullptr;
                        }
                        --scope_level;
                        std::cout<<"Scope level downgrade successfully\n";
                    }
                    std::cout<<"Current scope level: "<<scope_level<<"\n";
                    continue;
                }
                else if(cmd==Command::Scope){
                    std::cout<<"Current scope level: "<<scope_level<<"\n";
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
            Situation sb=buildStatement(stat,scope_level,t);
            if(sb!=Situation::Success){
                std::cout<<sb<<std::endl;
            }
            ExecuteResult er;
            Situation se=stat->execute(er);
            std::cout<<se<<std::endl;
        }
    }
}