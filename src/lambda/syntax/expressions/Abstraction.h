//
// Created by daanp on 06/02/2024.
//

#ifndef LAMBDA_ABSTRACTION_H
#define LAMBDA_ABSTRACTION_H

#include "Expression.h"

class Abstraction
        : public Expression {
private:
    ReductionLevel reductionLevel = DEFINED;
    std::string identifier;
    std::shared_ptr<Expression> expression;

public:
    explicit Abstraction(std::string identifier, std::shared_ptr<Expression> expression)
            : identifier(std::move(identifier)), expression(std::move(expression)) {
    }

    ~Abstraction() override = default;

    Type getType() const override { return ABSTRACTION; }

public:
    void doSimplification(ReductionLevel desiredLevel) {
        if (reductionLevel >= desiredLevel)
            return;

        switch (desiredLevel) {
            case DEFINED:
                break;
            case EVALUATED:
                expression = expression->evaluate();
                break;
            case REDUCED:
                expression = expression->reduce();
                break;
        }
        reductionLevel = desiredLevel;
    }

public:
    std::shared_ptr<Expression> createCopy() override {
        return shared_from_this();
    }

    std::shared_ptr<Expression> reduce() override {
        if (reductionLevel < REDUCED) {
            expression = expression->reduce();
            reductionLevel = REDUCED;
        }

        return expression->createCopy();
    }

    std::shared_ptr<Expression> evaluate() override {
        if (reductionLevel < EVALUATED) {
            expression = expression->evaluate();
            reductionLevel = EVALUATED;
        }

        return expression->createCopy();
    }

public:
    std::string toString() override {
        return '[' + expression->toString() + ']';
    }
};

#endif //LAMBDA_ABSTRACTION_H
