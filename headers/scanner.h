#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include "tokens.h"

class Scanner {
public:
    explicit Scanner(const std::string& source);
    std::vector<Token> scanTokens();

private:
    std::string source;
    size_t start = 0;
    size_t current = 0;
    int line = 1;

    bool isAtEnd();
    char advance();
    void addToken(TokenType type, const std::string& lexeme = "");
    char peek();
    void scanToken();
    void handleNumber();
    void handleIdentifier();

    std::vector<Token> tokens;
};

#endif
