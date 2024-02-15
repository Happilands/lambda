//
// Created by daanp on 06/02/2024.
//

#ifndef LAMBDA_INTERPRETEXCEPTION_H
#define LAMBDA_INTERPRETEXCEPTION_H

#include <stdexcept>

class InterpretException
        : public std::exception{
private:
    std::string message;
public:
    explicit InterpretException(std::string message)
        : message(std::move(message)){
    }

public:
    [[nodiscard]] const char* what() const noexcept override{
        return message.c_str();
    }
};

#endif //LAMBDA_INTERPRETEXCEPTION_H
