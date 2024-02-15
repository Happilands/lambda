//
// Created by daanp on 06/02/2024.
//

#include "StatementParser.h"
#include "ExpressionParser.h"
#include "lambda/parse/exception/UnexpectedTokenException.h"
#include "lambda/syntax/expressions/Abstraction.h"

std::shared_ptr<Statement> StatementParser::parseStatement(Parser &parser) {
    Token next = parser.peek();

    switch (next.type) {
        case Token::IDENTIFIER:{
            if(next.content == "import")
                parseImport(parser);
            else if(next.content == "print")
                return parsePrint(parser);
            else if(next.content == "play")
                return parsePlay(parser);
            else
                return parseAssignment(parser);
            break;
        }
        default:{
            throw UnexpectedTokenException(next);
        }
    }

    return nullptr;
}

void StatementParser::parseImport(Parser &parser) {
    Token keyword = parser.expect(Token::IDENTIFIER);

    if(keyword.content != "import")
        throw SyntaxException("Expected 'import' keyword", keyword);

    Token string = parser.expect(Token::STRING_LITERAL);
    parser.expect(Token::TERMINATOR);

    std::filesystem::path base = *string.position.filename;
    base = base.remove_filename();
    std::filesystem::path completed = base.string() + string.content;
    completed = completed.lexically_normal();

    parser.importFile(completed);
}

std::shared_ptr<Print> StatementParser::parsePrint(Parser &parser) {
    Token keyword = parser.expect(Token::IDENTIFIER);

    if(keyword.content != "print")
        throw SyntaxException("Expected 'print' keyword", keyword);

    std::shared_ptr<Expression> expression = ExpressionParser::parseSequence(parser, {Token::TERMINATOR});
    std::shared_ptr<Print> print = std::make_shared<Print>(expression);

    parser.expect(Token::TERMINATOR);
    return print;
}

std::shared_ptr<Play> StatementParser::parsePlay(Parser &parser) {
    Token keyword = parser.expect(Token::IDENTIFIER);

    if(keyword.content != "play")
        throw SyntaxException("Expected 'play' keyword", keyword);

    Token state = parser.expect(Token::IDENTIFIER);
    Token update = parser.expect(Token::IDENTIFIER);
    Token render = parser.expect(Token::IDENTIFIER);
    parser.expect(Token::TERMINATOR);

    std::shared_ptr<Expression> stateAbstraction = parser.getDefinitionStack().find(state);
    std::shared_ptr<Expression> updateAbstraction = parser.getDefinitionStack().find(update);
    std::shared_ptr<Expression> renderAbstraction = parser.getDefinitionStack().find(render);

    return std::make_shared<Play>(stateAbstraction, updateAbstraction, renderAbstraction);
}

std::shared_ptr<Assignment> StatementParser::parseAssignment(Parser &parser) {
    Token nameToken = parser.expect(Token::IDENTIFIER);
    Token assignment = parser.expect(Token::ASSIGNMENT);
    std::shared_ptr<Expression> expression = ExpressionParser::parseSequence(parser, {Token::TERMINATOR});
    parser.expect(Token::TERMINATOR);

    Expression::ReductionLevel type;
    if(assignment.content == ":=")
        type = Expression::DEFINED;
    else if(assignment.content == "*=")
        type = Expression::EVALUATED;
    else if(assignment.content == "<=")
        type = Expression::REDUCED;
    else
        throw SyntaxException(std::format("Unrecognized assignment: '{}'", assignment.content), assignment);

    std::shared_ptr<Abstraction> abstraction = std::make_shared<Abstraction>(nameToken.content, expression);

    std::shared_ptr<Assignment> statement = std::make_shared<Assignment>(type, abstraction);

    parser.getDefinitionStack().push(nameToken.content, abstraction);

    return statement;
}
