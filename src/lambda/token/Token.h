//
// Created by daanp on 01/02/2024.
//

#ifndef LAMBDA_TOKEN_H
#define LAMBDA_TOKEN_H

#include <string>
#include <memory>

struct FilePosition{
public:
    std::shared_ptr<std::string> filename; // better to use const char* to conserve memory
    int line;
    int character;
};

struct Token{
public:
    enum Type {
        ASSIGNMENT,
        IDENTIFIER,
        LAMBDA,
        DOT,
        OPEN_BRACKET,
        CLOSE_BRACKET,
        TERMINATOR,
        STRING_LITERAL,
        COMMENT
    };

    static Type getTokenType(const std::string& content);
    static std::string type2Representation(Type type);

public:
    std::string content;
    Type type;
    FilePosition position;
};

#endif //LAMBDA_TOKEN_H
