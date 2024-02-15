//
// Created by daanp on 12/02/2024.
//

#ifndef LAMBDA_PLAY_H
#define LAMBDA_PLAY_H

#include "Statement.h"
#include "lambda/syntax/expressions/Lambda.h"

class Interpreter;

class Play
        : public Statement{
private:
    std::shared_ptr<Expression> state;
    std::shared_ptr<Expression> update;
    std::shared_ptr<Expression> render;

public:
    Play(std::shared_ptr<Expression> state, std::shared_ptr<Expression> update, std::shared_ptr<Expression> render)
        : state(std::move(state)), update(std::move(update)), render(std::move(render)){

    }

    [[noreturn]] void run(Interpreter& interpreter) override;
};


#endif //LAMBDA_PLAY_H
