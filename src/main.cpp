#include <Windows.h>
#include <fstream>
#include <iostream>

#include "lambda/parse/Parser.h"
#include "lambda/parse/exception/ParseException.h"
#include "lambda/interpret/exception/InterpretException.h"
#include "util/Stopwatch.h"

enum ErrorCode{
    SUCCES = 0,
    NO_INPUT_FILE = 1,
    PARSE_ERROR = 2,
    INTERPRET_ERROR = 3
};

int parse(Parser& parser, const char* filename){
    try {
        parser.importFile(filename);
        parser.parse();
    }
    catch (ParseException& e){
        std::cerr << e.what();
        return PARSE_ERROR;
    }
    catch (std::overflow_error& e){
        std::cerr << "ParseError: Encountered stack overflow while parsing.";
    }
    return SUCCES;
}

int interpret(Parser& parser){
    try {
        parser.run();
    }
    catch (InterpretException& e){
        std::cerr << e.what();
        return INTERPRET_ERROR;
    }
    return SUCCES;
}

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    if(argc <= 1){
        std::cerr << "Error: No input file was given.";
        return NO_INPUT_FILE;
    }

    const char* filename = argv[1];
    int error_code;

    SetConsoleOutputCP(CP_UTF8);

    Parser parser;
    Stopwatch stopwatch;
    stopwatch.start();

    {
        error_code = parse(parser, filename);
        if (error_code) return error_code;
    }

    std::cout << std::format("Parsing Time: {}ms\n", stopwatch.elapsed());
    stopwatch.start();

    {
        error_code = interpret(parser);
        if (error_code) return error_code;
    }

    std::cout << std::format("Execution Time: {}ms\n", stopwatch.elapsed());

    return SUCCES;
}
