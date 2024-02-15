//
// Created by daanp on 01/02/2024.
//

#include <fstream>
#include <iostream>
#include <iomanip>
#include <regex>
#include <format>

#include "Tokenizer.h"

std::string identifiers = "([A-Za-z0-9][A-Za-z0-9\\-_]*)";
std::string multiline_comments = "(/\\*((.|\n)*?)\\*/)";
std::string comments = "(//.*)";
std::string operators = "(λ|:=|<=|\\*=|[.;()])";
std::string strings = R"(("[^"]*"))";

std::regex token_matcher(std::format("{}|{}|{}|{}|{}",
                                     comments,
                                     multiline_comments,
                                     operators,
                                     identifiers,
                                     strings
));

std::vector<Token> Tokenizer::tokenize(const std::string &code, const std::filesystem::path& path) {
    std::shared_ptr<std::string> shared_filename = std::make_shared<std::string>(path.string());

    std::vector<Token> tokens;
    std::sregex_token_iterator it(code.begin(), code.end(), token_matcher);
    std::sregex_token_iterator reg_end;

    int line = 1;
    int character = 0;
    int position = 0;

    for (; it != reg_end; ++it) {
        size_t match_position = std::distance(code.begin(), it->first);

        for(; position < match_position; position++){
            if(code[position] == '\n'){
                line++;
                character = 0;
            }
            else{
                character++;
            }
        }

        Token token;
        token.content = it->str();
        token.type = Token::getTokenType(token.content);

        token.position.filename = shared_filename;
        token.position.line = line;
        token.position.character = character;

        if(token.type == Token::STRING_LITERAL)
            token.content = token.content.substr(1, token.content.size() - 2);

        if(token.type != Token::COMMENT)
            tokens.push_back(token);
    }
    return tokens;
}

std::vector<Token> Tokenizer::tokenize(const std::filesystem::path& path) {
    std::ifstream t(path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return tokenize(buffer.str(), path);
}

[[maybe_unused]] void Tokenizer::printTokens(const std::vector<Token> &tokens) {
    for(int i = 0; i < tokens.size(); i++){
        auto& token = tokens[i];

        std::cout << std::setw(8 + (token.type == Token::LAMBDA))
                  << token.content.substr(0, 8);

        if(i % 10 == 9)
            std::cout << std::endl;
    }
}
