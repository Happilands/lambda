//
// Created by daanp on 06/02/2024.
//

#ifndef LAMBDA_SYNTAXEXCEPTION_H
#define LAMBDA_SYNTAXEXCEPTION_H

#include <format>

#include "ParseException.h"
#include "lambda/token/Token.h"

class SyntaxException
        : public ParseException{
private:
    std::string message;

public:
    SyntaxException(const std::string& exception, const Token& token) {
        message = std::format("In file {}:{}:{}:\nSyntaxError: {}",
                              *token.position.filename, token.position.line, token.position.character,
                              exception);
    }

public:
    [[nodiscard]] const char* what() const noexcept override{
        return message.c_str();
    }
};

#endif //LAMBDA_SYNTAXEXCEPTION_H
