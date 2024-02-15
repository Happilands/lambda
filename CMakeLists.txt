cmake_minimum_required(VERSION 3.26)
project(lambda)

set(CMAKE_CXX_STANDARD 23)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

include_directories(src)

add_executable(lambda src/main.cpp
        src/lambda/token/Tokenizer.cpp
        src/lambda/token/Tokenizer.h
        src/lambda/token/Token.h
        src/lambda/parse/Parser.cpp
        src/lambda/parse/Parser.h
        src/lambda/syntax/statements/Statement.h
        src/lambda/parse/DefinitionStack.cpp
        src/lambda/parse/DefinitionStack.h
        src/lambda/syntax/statements/Print.h
        src/lambda/interpret/Interpreter.cpp
        src/lambda/interpret/Interpreter.h
        src/lambda/token/Token.cpp
        src/lambda/parse/logic/ExpressionParser.cpp
        src/lambda/parse/logic/ExpressionParser.h
        src/lambda/syntax/expressions/Expression.h
        src/lambda/syntax/expressions/Lambda.h
        src/lambda/syntax/expressions/Application.h
        src/lambda/syntax/expressions/Variable.h
        src/lambda/parse/logic/StatementParser.cpp
        src/lambda/parse/logic/StatementParser.h
        src/lambda/syntax/statements/Assignment.h
        src/lambda/parse/exception/ParseException.h
        src/lambda/parse/exception/SyntaxException.h
        src/lambda/parse/exception/EOFException.h
        src/lambda/parse/exception/UnexpectedTokenException.h
        src/lambda/interpret/exception/InterpretException.h
        src/lambda/syntax/expressions/Abstraction.h
        src/util/Stopwatch.h
        src/lambda/syntax/expressions/Variable.cpp
        src/lambda/syntax/statements/Play.cpp
        src/lambda/syntax/statements/Play.h
)
