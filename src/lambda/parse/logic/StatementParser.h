//
// Created by daanp on 06/02/2024.
//

#ifndef LAMBDA_STATEMENTPARSER_H
#define LAMBDA_STATEMENTPARSER_H

#include "lambda/syntax/statements/Statement.h"
#include "lambda/parse/Parser.h"

#include "lambda/syntax/statements/Print.h"
#include "lambda/syntax/statements/Assignment.h"
#include "lambda/syntax/statements/Play.h"

class StatementParser {
public:
    static std::shared_ptr<Statement> parseStatement(Parser& parser);
    static void parseImport(Parser& parser);
    static std::shared_ptr<Play> parsePlay(Parser& parser);
    static std::shared_ptr<Print> parsePrint(Parser& parser);
    static std::shared_ptr<Assignment> parseAssignment(Parser& parser);
};

#endif //LAMBDA_STATEMENTPARSER_H
