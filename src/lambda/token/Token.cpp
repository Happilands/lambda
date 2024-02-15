//
// Created by daanp on 05/02/2024.
//

#include "Token.h"

Token::Type Token::getTokenType(const std::string &content) {
    if(content.substr(0, 2) == "//") return Token::COMMENT;
    if(content.substr(0, 2) == "/*") return Token::COMMENT;
    if(content.substr(0, 1) == "\"") return Token::STRING_LITERAL;
    if(content == ":=") return Token::ASSIGNMENT;
    if(content == "<=") return Token::ASSIGNMENT;
    if(content == "*=") return Token::ASSIGNMENT;
    if(content == "λ") return Token::LAMBDA;
    if(content == ".") return Token::DOT;
    if(content == ";") return Token::TERMINATOR;
    if(content == "(") return Token::OPEN_BRACKET;
    if(content == ")") return Token::CLOSE_BRACKET;
    return Token::IDENTIFIER;
}

std::string Token::type2Representation(Token::Type type) {
    switch (type) {
        case LAMBDA:                return "λ";
        case DOT:                   return ".";
        case OPEN_BRACKET:          return "(";
        case CLOSE_BRACKET:         return ")";
        case TERMINATOR:            return ";";
        case ASSIGNMENT:            return "assignment";
        case STRING_LITERAL:        return "string literal";
        case IDENTIFIER:            return "identifier";
        case COMMENT:               return "comment";
    }
    return "";
}
