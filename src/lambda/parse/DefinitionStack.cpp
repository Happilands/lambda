//
// Created by daanp on 02/02/2024.
//

#include "DefinitionStack.h"
#include "lambda/parse/exception/SyntaxException.h"

std::shared_ptr<Expression> DefinitionStack::find(const Token &identifier) {
    std::stack<std::shared_ptr<Expression>>& stack = identifier2defineStack[identifier.content];

    if(stack.empty())
        throw SyntaxException(std::format("Found undefined identifier: '{}'", identifier.content), identifier);

    return stack.top();
}

void DefinitionStack::push(const std::string& identifier, std::shared_ptr<Expression> expression) {
    // Will construct a new stack if identifier is not present.
    std::stack<std::shared_ptr<Expression>>& stack = identifier2defineStack[identifier];
    stack.push(expression);
}

void DefinitionStack::pop(const std::string& identifier) {
    std::stack<std::shared_ptr<Expression>>& stack = identifier2defineStack[identifier];
    stack.pop();

    if(stack.empty())
        identifier2defineStack.erase(identifier);
}
