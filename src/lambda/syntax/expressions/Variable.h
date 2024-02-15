//
// Created by daanp on 05/02/2024.
//

#ifndef LAMBDA_VARIABLE_H
#define LAMBDA_VARIABLE_H

#include "Expression.h"

class Lambda;

class Variable
        : public Expression{
private:
    std::string name;
    std::shared_ptr<Expression> substitution;
    std::shared_ptr<Lambda> copyInProgress;
    ReductionLevel reductionLevel = DEFINED;

    friend class Lambda;

public:
    explicit Variable(std::string name)
        : name(std::move(name)), substitution(nullptr), copyInProgress(nullptr){
    }

    ~Variable() override = default;

    Type getType() const override { return VARIABLE; }

public:
    std::shared_ptr<Expression> createCopy() override;

    std::shared_ptr<Expression> reduce() override{
        if(substitution) {
            if(reductionLevel < REDUCED) {
                substitution = substitution->reduce();
                reductionLevel = REDUCED;
            }

            // TODO: figure out why this needs to be a three?? it should just be a two...
            if(shared_from_this().use_count() == 3)
                return substitution;

            return substitution->createCopy();
        }
        else return shared_from_this();
    }

    std::shared_ptr<Expression> evaluate() override{
        if(substitution) {
            if(reductionLevel < EVALUATED) {
                substitution = substitution->evaluate();
                reductionLevel = EVALUATED;
            }

            // One from the lambda and one from the caller
            if(shared_from_this().use_count() == 2)
                return substitution;

            return substitution->createCopy();
        }
        else return shared_from_this();
    }

public:
    std::string toString() override{
        if(substitution)
            return substitution->toString();
        else
            return name;
    }
};

#endif //LAMBDA_VARIABLE_H
