//
// Created by daanp on 06/02/2024.
//

#ifndef LAMBDA_EOFEXCEPTION_H
#define LAMBDA_EOFEXCEPTION_H

#include <format>

#include "ParseException.h"
#include "lambda/token/Token.h"

class EOFException
        : public ParseException{
private:
    std::string message;

public:
    EOFException() {
        message = "SyntaxError: Unexpected end of file reached";
    }
    explicit EOFException(Token::Type type) {
        message = std::format("SyntaxError: Expected '{}' but reached end of file",
                              Token::type2Representation(type));
    }
public:
    [[nodiscard]] const char* what() const noexcept override{
        return message.c_str();
    }
};


#endif //LAMBDA_EOFEXCEPTION_H
