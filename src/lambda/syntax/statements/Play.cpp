//
// Created by daanp on 12/02/2024.
//

#include <iostream>

#include "Play.h"
#include "lambda/syntax/expressions/Application.h"

[[noreturn]] void Play::run(Interpreter &interpreter) {
    while (true){
        state = std::make_shared<Application>(update->createCopy(), state);
        state = state->reduce();
        std::shared_ptr<Expression> result = std::make_shared<Application>(render->createCopy(), state->createCopy());
        std::string str = result->reduce()->toString();

        // TODO: make this substr more elegant
        std::cout << str.substr(1, str.length() - 2) << std::endl;
    }
}
