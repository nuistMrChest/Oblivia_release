// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#include<iostream>
#include"./TypeSystem/type_system.h"
#include"./Tokenize/tokenize.h"
#include"./Situation/situation.h"
#include"./Statement/statement.h"
#include"./Expression/expression.h"
#include"relp.h"
#include"interpreter.h"

using namespace std;
using namespace Oblivia;

int main(int argc,char**argv){
    if(argc!=1&&argc!=2){
        std::cout<<"Too many arguments"<<std::endl;
        return 0;
    }
    if(argc==1)RELP();
    else if(argc==2){
        std::string path=argv[1];
        interpreter(path);
    }
}