//
// Created by daanp on 05/02/2024.
//

#ifndef LAMBDA_LAMBDA_H
#define LAMBDA_LAMBDA_H

#include <sstream>
#include <utility>

#include "Expression.h"
#include "Variable.h"

class Lambda
        : public Expression {
private:
    std::shared_ptr<Variable> variable;
    std::shared_ptr<Expression> body;

public:
    explicit Lambda(const std::string &name)
            : variable(std::make_shared<Variable>(name)), body(nullptr) {
    }

    Lambda(const std::string &name, const std::shared_ptr<Expression> &body)
            : variable(std::make_shared<Variable>(name)), body(body) {
    }

    ~Lambda() override = default;

    Type getType() const override { return LAMBDA; }
    bool hasNotationRightBleed() const override {return false; }

public:
    std::shared_ptr<Expression> createCopy() override {
        auto result = std::make_shared<Lambda>(variable->name);
        variable->copyInProgress = result;
        result->setBody(body->createCopy());
        variable->copyInProgress = nullptr;
        return result;
    }

    void substitute(const std::shared_ptr<Expression> &substitution) {
        variable->substitution = substitution;
    }

    std::shared_ptr<Expression> reduce() override {
        body = body->reduce();
        if (variable->substitution)
            return body;
        else
            return shared_from_this();
    }

    std::shared_ptr<Expression> evaluate() override {
        if (variable->substitution) {
            return body->evaluate();
        } else
            return shared_from_this();
    }

public:
    [[nodiscard]] inline const std::shared_ptr<Variable> &getVariable() { return variable; }
    [[nodiscard]] inline const std::string getVariableName() const { return variable->name; }

    inline void setBody(std::shared_ptr<Expression> body_) { body = std::move(body_); }

    std::string collapseToString() {
        std::stringstream ss;
        ss << ' ' << variable->name;

        if (body->getType() == LAMBDA)
            ss << std::reinterpret_pointer_cast<Lambda>(body)->collapseToString();
        else
            ss << '.' << body->toString();
        return ss.str();
    }

    std::string toString() override {
        std::stringstream ss;
        ss << "(λ" << variable->name;

        if (body->getType() == LAMBDA)
            ss << std::reinterpret_pointer_cast<Lambda>(body)->collapseToString() << ')';
        else
            ss << '.' << body->toString() << ')';
        return ss.str();
    }
};

#endif //LAMBDA_LAMBDA_H
