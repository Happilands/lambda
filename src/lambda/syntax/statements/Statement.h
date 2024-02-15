//
// Created by daanp on 02/02/2024.
//

#ifndef LAMBDA_STATEMENT_H
#define LAMBDA_STATEMENT_H

#include <memory>

class Interpreter;

class Statement {
public:
    virtual void run(Interpreter& interpreter) = 0;
};

#endif //LAMBDA_STATEMENT_H
