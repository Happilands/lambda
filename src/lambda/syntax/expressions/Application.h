//
// Created by daanp on 05/02/2024.
//

#ifndef LAMBDA_APPLICATION_H
#define LAMBDA_APPLICATION_H

#include <sstream>

#include "Expression.h"
#include "Lambda.h"

class Application
        : public Expression {
private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;

public:
    Application(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
        : left(std::move(l)), right(std::move(r)){
    }

    ~Application() override = default;

    Type getType() const override { return APPLICATION; }
    bool hasNotationRightBleed() const override {return right->hasNotationRightBleed(); }

public:
    std::shared_ptr<Expression> createCopy() override{
        return std::make_shared<Application>(left->createCopy(), right->createCopy());
    }

    std::shared_ptr<Expression> reduce() override{
        // We want to lazily evaluate the left to find the nearest lambda
        // When we find the lambda we can merge the left and right reduction paths by applying the right to the left
        // This makes the compute time of some expressions go from exponential to linear
        left = left->evaluate();

        if(left->getType() != LAMBDA) {
            left = left->reduce();
            right = right->reduce();
            return shared_from_this();
        }

        std::shared_ptr<Lambda> lambda = std::reinterpret_pointer_cast<Lambda>(left);

        lambda->substitute(right);
        left = nullptr;
        right = nullptr;
        return lambda->reduce();
    }

    std::shared_ptr<Expression> evaluate() override{
        left = left->evaluate();

        if(left->getType() != LAMBDA)
            return shared_from_this();

        std::shared_ptr<Lambda> lambda = std::reinterpret_pointer_cast<Lambda>(left);

        lambda->substitute(right);
        left = nullptr;
        right = nullptr;
        return lambda->evaluate();
    }

public:
    std::string toString() override{
        std::stringstream ss;

        // TODO: fix brackets

        bool leftBrackets = left->hasNotationRightBleed();
        bool rightBrackets = right->getType() == APPLICATION;

        if(leftBrackets)
            ss << '(' << left->toString() << ')';
        else
            ss << left->toString();

        ss << ' ';

        if(rightBrackets)
            ss << '(' << right->toString() << ')';
        else
            ss << right->toString();

        return ss.str();
    }
};

#endif //LAMBDA_APPLICATION_H
