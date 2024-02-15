//
// Created by daanp on 05/02/2024.
//

#ifndef LAMBDA_EXPRESSION_H
#define LAMBDA_EXPRESSION_H

#include <string>
#include <memory>

class Expression
: public std::enable_shared_from_this<Expression>{
public:
    enum ReductionLevel {
        DEFINED = 0,
        EVALUATED = 1,
        REDUCED = 2
    };

    enum Type {
        ABSTRACTION,
        APPLICATION,
        LAMBDA,
        VARIABLE
    };

public:
    virtual ~Expression()= default;

public:
    [[nodiscard]] virtual bool hasNotationRightBleed() const{return false;}
    [[nodiscard]] virtual Type getType() const = 0;
    virtual std::shared_ptr<Expression> createCopy() = 0;
    virtual std::shared_ptr<Expression> reduce() = 0;
    virtual std::shared_ptr<Expression> evaluate() = 0;
    virtual std::string toString() = 0;
};

#endif //LAMBDA_EXPRESSION_H
