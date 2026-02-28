// Copyright (c) 2026 MrChest
// Licensed under the MIT License
#ifndef STATEMENT_H
#define STATEMENT_H

#include"../Situation/situation.h"
#include<memory>
#include"../Expression/expression.h"
#include"../Tokenize/tokenize.h"
#include<string>
#include<iostream>
#include<vector>

namespace Oblivia{
    enum class ExecuteResult{
        Other,

        EndLoop,
        ContinueLoop
    };

    enum class StatementType{
        Null,
        Expr,
        Let,
        Print,
        Scan,
        If,
        Else,
        While,
        Block,
        Fn,
        Break,
        Continue,
        Execute,
        Borrow,
        Move
    };

    StatementType getStateType(const Tokens&a);

    std::ostream&operator<<(std::ostream&os,const StatementType&a);

    bool isStatement(const Tokens&t);

    class Statement{
        protected:
        Tokens tokens;
        public:
        StatementType type;
        size_t stack_level;
        
        Statement*e;
        
        bool linked;
        
        bool have_else;
        
        Statement();
        virtual Situation execute(ExecuteResult&result)=0;
        virtual Situation build()=0;
        friend std::ostream&operator<<(std::ostream&os,const Statement&a);
    };

    Situation buildStatement(std::unique_ptr<Statement>&r,size_t l,const Tokens&t);

    class Expr:public Statement{
        private:
        Expression e;
        public:
        Expr();
        Expr(size_t l,const Tokens&t);
        Situation execute(ExecuteResult&result);
        static bool isLegal(const Tokens&t);
        Situation build();
    };

    class Let:public Statement{
        public:
        std::string name;
        Expression val;
        Type val_ty;
        Let();
        Let(size_t l,const Tokens&t);
        Situation execute(ExecuteResult&result);
        static bool isLegal(const Tokens&t);
        Situation build();
    };

    class Print:public Statement{
        private:
        Expression e;
        public:
        Print();
        Print(size_t l,const Tokens&t);
        Situation execute(ExecuteResult&result);
        static bool isLegal(const Tokens&t);
        Situation build();
    };

    class Scan:public Statement{
        public:
        Scan();
        Scan(size_t l,const Tokens&t);
        Situation execute(ExecuteResult&result);
        static bool isLegal(const Tokens&t);
        Situation build();
    };

    class Block:public Statement{
        private:
        Situation linkElse();
        public:
        std::vector<std::unique_ptr<Statement>>subStates;

        Block();
        Block(size_t l,const Tokens&t);
        Situation execute(ExecuteResult&result);
        static bool isLegal(const Tokens&t);
        Situation build();
    };

    class Else;

    class If:public Statement{
        public:
        Expression j;
        std::unique_ptr<Statement>t;

        If();
        If(size_t l,const Tokens&t);
        Situation execute(ExecuteResult&result);
        static bool isLegal(const Tokens&t);
        Situation build();
    };

    class Else:public Statement{
        public:
        std::unique_ptr<Statement>f;
        
        Else();
        Else(size_t l,const Tokens&t);
        Situation execute(ExecuteResult&result);
        static bool isLegal(const Tokens&t);
        Situation build();
    };

    class While:public Statement{
        public:
        std::unique_ptr<Statement>d;
        Expression j;
        While();
        While(size_t l,const Tokens&t);
        Situation execute(ExecuteResult&result);
        static bool isLegal(const Tokens&t);
        Situation build();
    };

    class Break:public Statement{
        public:
        Break();
        Break(size_t l,const Tokens&t);
        Situation execute(ExecuteResult&result);
        static bool isLegal(const Tokens&t);
        Situation build();
    };

    class Continue:public Statement{
        public:
        Continue();
        Continue(size_t l,const Tokens&t);
        Situation execute(ExecuteResult&result);
        static bool isLegal(const Tokens&t);
        Situation build();
    };

    class Execute:public Statement{
        public:
        std::string code;
        Execute();
        Execute(size_t l,const Tokens&t);
        Situation execute(ExecuteResult&result);
        static bool isLegal(const Tokens&t);
        Situation build();
    };

    bool isOwner(const Token&a,size_t l);

    class Move:public Statement{
        public:
        Expression from;
        Expression to;
        Move();
        Move(size_t l,const Tokens&t);
        Situation execute(ExecuteResult&result);
        static bool isLegal(const Tokens&t);
        Situation build();
    };

    class Borrow:public Statement{
        public:
        std::string name;
        Expression from;
        Borrow();
        Borrow(size_t l,const Tokens&t);
        Situation execute(ExecuteResult&result);
        static bool isLegal(const Tokens&t);
        Situation build();
    };

    // class Fn:public Statement{
    //     public:
    //     Fn();
    //     Fn(int l,const Tokens&t);
    //     Situation execute(ExecuteResult&result);
    //     static bool isLegal(const Tokens&t);
    //     Situation build();
    // };
}

#endif
