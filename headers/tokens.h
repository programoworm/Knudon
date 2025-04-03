#ifndef TOKENS_H
#define TOKENS_H

#include <string>

enum class TokenType {
    START, END, PRINT,
    IDENTIFIER, NUMBER, STRING,
    PLUS, MINUS, STAR, SLASH, EQUAL, COMMA,
    END_OF_FILE, SEMICOLON
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;

    Token(TokenType type, const std::string& lexeme, int line)
        : type(type), lexeme(lexeme), line(line) {}
};

#endif
