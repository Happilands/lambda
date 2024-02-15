//
// Created by daanp on 05/02/2024.
//

#ifndef LAMBDA_PRINT_H
#define LAMBDA_PRINT_H

#include <iostream>

#include "Statement.h"
#include "lambda/syntax/expressions/Expression.h"

class Print
        : public Statement{
private:
    std::shared_ptr<Expression> expression;

public:
    explicit Print(std::shared_ptr<Expression> expression)
        : expression(std::move(expression)){
    }

public:
    void run(Interpreter& interpreter) override{
        std::string str = expression->reduce()->toString();

        // TODO: make this substr more elegant
        std::cout << str.substr(1, str.length() - 2) << std::endl;
    }
};


#endif //LAMBDA_PRINT_H
