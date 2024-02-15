//
// Created by daanp on 06/02/2024.
//

#ifndef LAMBDA_UNEXPECTEDTOKENEXCEPTION_H
#define LAMBDA_UNEXPECTEDTOKENEXCEPTION_H

#include <format>

#include "SyntaxException.h"
#include "lambda/token/Token.h"

class UnexpectedTokenException
        : public SyntaxException{

public:
    explicit UnexpectedTokenException(const Token &token)
            : SyntaxException(std::format("Found unexpected token '{}'",
                                          token.content), token) {
    }
};

#endif //LAMBDA_UNEXPECTEDTOKENEXCEPTION_H
