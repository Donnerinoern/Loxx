#include <cstdio>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string_view>
#include "main.h"
#include "scanner.h"
#include "token.h"

static bool hadError = false;

int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::cout << "Usage: loxx [script]\n";
        // std::exit(64);
        return 1;
    } else if (argc == 2) {
        std::string argAsString {argv[1]};
        run_file(argAsString);
        return 0;
    } else {
        run_prompt();
        return 0;
    }
}

void run_file(std::string& path) {
    std::ifstream fileStream{ path, std::ifstream::in };
    std::stringstream stringStream;
    stringStream << fileStream.rdbuf();
    run(stringStream.str());
    if (hadError) {
        std::exit(65);
    }
}

void run_prompt() {
    std::string input;
    for (;;) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == "") {
            break;
        }
        run(input);
        hadError = false;
    }
}

void run(std::string_view source) {
    Scanner scanner {source};
    std::list<Token> tokens {scanner.scan_tokens()};
    for (Token token : tokens) {
        std::cout << token.str();
    }
}

namespace Lox {

    void report(int line, std::string_view where, std::string_view message) {
        std::cerr << "[line " << line << "] Error" << where << ": " << message;
        hadError = true;
    }

    void error(int line, std::string_view message) {
        report(line, "", message);
    }

}
