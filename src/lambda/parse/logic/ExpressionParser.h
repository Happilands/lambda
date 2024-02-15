//
// Created by daanp on 05/02/2024.
//

#ifndef LAMBDA_EXPRESSIONPARSER_H
#define LAMBDA_EXPRESSIONPARSER_H

#include <memory>
#include <unordered_set>

#include "lambda/syntax/expressions/Expression.h"
#include "lambda/token/Token.h"

class Parser;

class ExpressionParser {
public:
    static std::shared_ptr<Expression> parseSequence(Parser& parser, const std::unordered_set<Token::Type>& closeTokens);
    static std::shared_ptr<Expression> parseBracketSequence(Parser& parser);
    static std::shared_ptr<Expression> parseExpression(Parser& parser);
    static std::shared_ptr<Expression> parseLambda(Parser& parser);
    static std::shared_ptr<Expression> parseIdentifier(Parser& parser);
};

#endif //LAMBDA_EXPRESSIONPARSER_H
