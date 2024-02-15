//
// Created by daanp on 05/02/2024.
//

#include "ExpressionParser.h"
#include "lambda/parse/Parser.h"
#include "lambda/syntax/expressions/Application.h"
#include "lambda/parse/exception/UnexpectedTokenException.h"

std::shared_ptr<Expression> ExpressionParser::parseSequence(Parser &parser, const std::unordered_set<Token::Type>& closeTokens) {
    std::vector<std::shared_ptr<Expression>> expressions;

    while (!closeTokens.contains(parser.peek().type)){
        expressions.push_back(parseExpression(parser));
    }

    if(expressions.empty()) {
        Token next = parser.peek();
        throw SyntaxException("Found illegal empty expression", next);
    }

    for(int i = 1; i < expressions.size(); i++){
        expressions[i] = std::make_shared<Application>(expressions[i - 1], expressions[i]);
    }

    return expressions.back();
}

std::shared_ptr<Expression> ExpressionParser::parseBracketSequence(Parser &parser) {
    parser.expect(Token::OPEN_BRACKET);
    auto result = parseSequence(parser, {Token::CLOSE_BRACKET});
    parser.expect(Token::CLOSE_BRACKET);
    return result;
}

std::shared_ptr<Expression> ExpressionParser::parseExpression(Parser &parser) {
    Token first = parser.peek();

    switch (first.type) {
        case Token::OPEN_BRACKET:
            return parseBracketSequence(parser);
        case Token::LAMBDA:
            return parseLambda(parser);
        case Token::IDENTIFIER:
            return parseIdentifier(parser);
        default:
            throw UnexpectedTokenException(first);
    }
}

#include "lambda/syntax/expressions/Lambda.h"

std::shared_ptr<Expression> ExpressionParser::parseLambda(Parser &parser) {
    Token lambdaToken = parser.expect(Token::LAMBDA);

    std::vector<Token> identifiers;
    identifiers.push_back(parser.expect(Token::IDENTIFIER));
    while (parser.peek().type == Token::IDENTIFIER){
        identifiers.push_back(parser.expect(Token::IDENTIFIER));
    }
    Token dotToken = parser.expect(Token::DOT);

    std::vector<std::shared_ptr<Lambda>> lambdas;
    for(Token& token : identifiers)
        lambdas.push_back(std::make_shared<Lambda>(token.content));
    for(auto& lambda : lambdas)
        parser.getDefinitionStack().push(lambda->getVariableName(), lambda->getVariable());

    auto body = parseSequence(parser, {Token::CLOSE_BRACKET, Token::TERMINATOR});

    for(auto& lambda : lambdas)
        parser.getDefinitionStack().pop(lambda->getVariableName());

    for(int i = 1; i < lambdas.size(); i++)
        lambdas[i - 1]->setBody(lambdas[i]);
    lambdas.back()->setBody(body);
    return lambdas.front();
}

std::shared_ptr<Expression> ExpressionParser::parseIdentifier(Parser &parser) {
    Token identifier = parser.expect(Token::IDENTIFIER);

    return parser.getDefinitionStack().find(identifier)->createCopy();
}
