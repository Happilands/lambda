//
// Created by daanp on 01/02/2024.
//

#ifndef LAMBDA_TOKENIZER_H
#define LAMBDA_TOKENIZER_H

#include <vector>
#include <string>
#include <filesystem>

#include "Token.h"

class Tokenizer {
public:
    static std::vector<Token> tokenize(const std::string& code, const std::filesystem::path& path);
    static std::vector<Token> tokenize(const std::filesystem::path& path);

    [[maybe_unused]] static void printTokens(const std::vector<Token>& tokens);
};


#endif //LAMBDA_TOKENIZER_H
