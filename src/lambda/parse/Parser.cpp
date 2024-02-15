//
// Created by daanp on 02/02/2024.
//

#include <stdexcept>

#include "Parser.h"
#include "lambda/token/Tokenizer.h"
#include "logic/StatementParser.h"

#include "lambda/parse/exception/EOFException.h"
#include "lambda/parse/exception/SyntaxException.h"

void Parser::parse() {
    while (!isEmpty()){
        auto statement = StatementParser::parseStatement(*this);
        if(statement)
            statements.push_back(statement);
    }
}

void Parser::importFile(const std::filesystem::path& path) {
    if(!included_files.insert(path.lexically_normal()).second)
        return;

    std::vector<Token> t = Tokenizer::tokenize(path);
    tokens.insert(tokens.begin() + index, t.begin(), t.end());
}

Token Parser::peek() const {
    if(isEmpty()){
        throw EOFException();
    }

    return tokens[index];
}

Token Parser::expect(Token::Type type) {
    if(isEmpty())
        throw EOFException(type);

    Token token = tokens[index];

    if(token.type != type){
        throw SyntaxException(std::format("Expected '{}' but found '{}'",
                                          Token::type2Representation(type), token.content), token);
    }
    index++;
    return token;
}

#include "lambda/interpret/Interpreter.h"

void Parser::run() {
    Interpreter interpreter;
    for(auto & statement : statements){
        statement->run(interpreter);
    }
}