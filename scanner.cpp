#include "./headers/scanner.h"
#include "./headers/tokens.h"
#include <cctype>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

Scanner::Scanner(const std::string& source) : source(source) {}

std::vector<Token> Scanner::scanTokens() {
    std::vector<Token> tokens;
    size_t start = 0, current = 0, line = 1;

    auto isAtEnd = [&]() { return current >= source.length(); };
    auto advance = [&]() { return source[current++]; };
    auto addToken = [&](TokenType type, const std::string& lexeme) {
        tokens.emplace_back(type, lexeme, line);
        // Debugging output
        // std::cout << "Token: " << lexeme << " (Type: " << static_cast<int>(type) << ", Line: " << line << ")\n";
    };

    while (!isAtEnd()) {
        start = current;
        char c = advance();

        if (std::isspace(c)) {
            if (c == '\n') line++;
            continue;
        }

        if (std::isalpha(c)) {
            // Handle identifiers
            while (!isAtEnd() && (std::isalnum(source[current]) || source[current] == '_')) {
                advance();
            }
            std::string lexeme = source.substr(start, current - start);
            if (lexeme == "start") addToken(TokenType::START, lexeme);
            else if (lexeme == "end") addToken(TokenType::END, lexeme);
            else if (lexeme == "print") addToken(TokenType::PRINT, lexeme);
            else addToken(TokenType::IDENTIFIER, lexeme);
            continue;
        }

        if (std::isdigit(c)) {
            // Handle numbers
            while (!isAtEnd() && std::isdigit(source[current])) {
                advance();
            }
            addToken(TokenType::NUMBER, source.substr(start, current - start));
            continue;
        }

        switch (c) {
            case '=': addToken(TokenType::EQUAL, "="); break;
            case '+': addToken(TokenType::PLUS, "+"); break;
            case '-': addToken(TokenType::MINUS, "-"); break;
            case '*': addToken(TokenType::STAR, "*"); break;
            case '/': addToken(TokenType::SLASH, "/"); break;
            case ',': addToken(TokenType::COMMA, ","); break;
            case ';': addToken(TokenType::SEMICOLON, ";"); break;
            case '"': {
                // Handle strings enclosed in double quotes
                while (!isAtEnd() && source[current] != '"') {
                    if (source[current] == '\n') line++;
                    advance();
                }
                if (isAtEnd()) throw std::runtime_error("Unterminated string.");
                advance(); // Consume closing "
                addToken(TokenType::STRING, source.substr(start + 1, current - start - 2));
                break;
            }
            default:
                throw std::runtime_error("Unexpected character: " + std::string(1, c));
        }
    }

    tokens.emplace_back(TokenType::END_OF_FILE, "", line);
    // Debugging output
    // std::cout << "Token: END_OF_FILE (Type: " << static_cast<int>(TokenType::END_OF_FILE) << ", Line: " << line << ")\n";
    return tokens;
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

char Scanner::advance() {
    return source[current++];
}

void Scanner::addToken(TokenType type, const std::string& lexeme) {
    tokens.emplace_back(type, lexeme.empty() ? source.substr(start, current - start) : lexeme, line);
}

char Scanner::peek() {
    return isAtEnd() ? '\0' : source[current];
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        case '+': addToken(TokenType::PLUS); break;
        case '*': addToken(TokenType::STAR); break;
        case '=': addToken(TokenType::EQUAL); break;
        case ',': addToken(TokenType::COMMA); break;
        case '"': {
            std::string value;
            while (peek() != '"' && !isAtEnd()) {
                value += advance();
            }
            advance(); // Consume closing "
            addToken(TokenType::STRING, value);
            break;
        }
        default:
            if (std::isdigit(c)) {
                handleNumber();
            } else if (std::isalpha(c)) {
                handleIdentifier();
            }
            break;
    }
}

void Scanner::handleNumber() {
    while (std::isdigit(peek())) advance();
    addToken(TokenType::NUMBER);
}

void Scanner::handleIdentifier() {
    while (std::isalnum(peek())) advance();
    std::string text = source.substr(start, current - start);
    if (text == "start") addToken(TokenType::START);
    else if (text == "end") addToken(TokenType::END);
    else if (text == "print") addToken(TokenType::PRINT);
    else addToken(TokenType::IDENTIFIER);
}
