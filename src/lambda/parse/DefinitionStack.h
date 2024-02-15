//
// Created by daanp on 02/02/2024.
//

#ifndef LAMBDA_DEFINITIONSTACK_H
#define LAMBDA_DEFINITIONSTACK_H

#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <memory>

#include "lambda/syntax/expressions/Expression.h"
#include "lambda/token/Token.h"

class DefinitionStack {
    std::unordered_map<std::string, std::stack<std::shared_ptr<Expression>>> identifier2defineStack;

public:
    std::shared_ptr<Expression> find(const Token& identifier);
    void push(const std::string& identifier, std::shared_ptr<Expression> expression);
    void pop(const std::string& identifier);
};


#endif //LAMBDA_DEFINITIONSTACK_H
