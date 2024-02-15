//
// Created by daanp on 06/02/2024.
//

#ifndef LAMBDA_ASSIGNMENT_H
#define LAMBDA_ASSIGNMENT_H

#include "Statement.h"
#include "lambda/interpret/exception/InterpretException.h"
#include "lambda/syntax/expressions/Abstraction.h"

class Assignment
        : public Statement{
private:
    Expression::ReductionLevel reductionLevel;
    std::shared_ptr<Abstraction> abstraction;

public:
    explicit Assignment(Expression::ReductionLevel type, std::shared_ptr<Abstraction> abstraction)
        : reductionLevel(type), abstraction(std::move(abstraction)){
    }

public:
    void run(Interpreter& interpreter) override {
        abstraction->doSimplification(reductionLevel);
    }
};


#endif //LAMBDA_ASSIGNMENT_H
