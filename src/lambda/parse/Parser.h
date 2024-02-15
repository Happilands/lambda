//
// Created by daanp on 02/02/2024.
//

#ifndef LAMBDA_PARSER_H
#define LAMBDA_PARSER_H

#include <vector>
#include <unordered_set>
#include <string>
#include <filesystem>

#include "lambda/syntax/statements/Statement.h"
#include "lambda/token/Token.h"
#include "DefinitionStack.h"

class Parser {
private:
    int index = 0;
    std::vector<Token> tokens;
    std::vector<std::shared_ptr<Statement>> statements;
    DefinitionStack definitionStack;

    std::unordered_set<std::filesystem::path> included_files;

public:
    void run();
    void parse();
    void importFile(const std::filesystem::path& path);

    Token peek() const;
    Token expect(Token::Type type);

    inline bool isEmpty() const { return index >= tokens.size(); };
    inline DefinitionStack& getDefinitionStack(){return definitionStack;}
};

#endif //LAMBDA_PARSER_H
