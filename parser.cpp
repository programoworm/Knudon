#include "./headers/parser.h"
#include "./headers/statements.h"
#include <stdexcept>
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

std::vector<std::shared_ptr<Statement>> Parser::parse() {
    std::vector<std::shared_ptr<Statement>> statements;

    // Handle 'start' token
    if (!match(TokenType::START)) {
        throw std::runtime_error("Program must begin with 'start'.");
    }

    while (!isAtEnd()) {
        if (peek().type == TokenType::END) {
            // Ensure 'end' token is present and stop parsing
            advance();
            break;
        }

        try {
            statements.push_back(statement());
        } catch (const std::runtime_error& e) {
            // Debugging output for errors
            // std::cerr << "Parser error: " << e.what() << " at token: " << peek().lexeme << "\n";
            throw;
        }
    }

    // Ensure we are at the end of the file
    if (!isAtEnd()) {
        throw std::runtime_error("Program must end with 'end'.");
    }

    return statements;
}

bool Parser::isAtEnd() {
    return peek().type == TokenType::END_OF_FILE;
}

const Token& Parser::advance() {
    if (!isAtEnd()) current++;
    // Debugging output
    // std::cout << "Advance to token: " << peek().lexeme << " (Type: " << static_cast<int>(peek().type) << ")\n";
    return previous();
}

const Token& Parser::peek() {
    return tokens[current];
}

const Token& Parser::previous() {
    return tokens[current - 1];
}

bool Parser::match(TokenType type) {
    if (isAtEnd() || peek().type != type) return false;
    advance();
    return true;
}

const Token& Parser::consume(TokenType type, const std::string& errorMessage) {
    if (match(type)) return previous();
    throw std::runtime_error(errorMessage);
}

std::shared_ptr<Statement> Parser::statement() {
    if (match(TokenType::PRINT)) return printStatement();
    return expressionStatement();
}

std::shared_ptr<Statement> Parser::printStatement() {
    std::string message;

    // Parse multiple arguments separated by commas
    do {
        if (peek().type == TokenType::STRING) {
            // Handle string literals
            message += advance().lexeme + " ";
        } else {
            // Parse expressions (e.g., val * 3 or val * x)
            message += parseExpression(false) + " "; // Do not consume semicolon here
        }
    } while (match(TokenType::COMMA));

    // Ensure the semicolon is consumed at the end of the print statement
    consume(TokenType::SEMICOLON, "Expected ';' at the end of the 'print' statement.");
    return std::make_shared<PrintStatement>(message);
}

std::shared_ptr<Statement> Parser::expressionStatement() {
    auto identifier = consume(TokenType::IDENTIFIER, "Expected identifier.");
    // Debugging output
    // std::cout << "Parsing expression statement for identifier: " << identifier.lexeme << "\n";

    if (match(TokenType::EQUAL)) {
        // Handle assignment
        auto expression = parseExpression(); // Parse the right-hand side expression
        return std::make_shared<ExpressionStatement>(identifier.lexeme + " = " + expression);
    }
    throw std::runtime_error("Expected '=' after identifier.");
}

std::string Parser::parseExpression(bool consumeSemicolon) {
    // Parse a simple expression (e.g., numbers, identifiers, or arithmetic operations)
    std::string expression;
    while (!isAtEnd() && peek().type != TokenType::SEMICOLON && peek().type != TokenType::COMMA) {
        expression += advance().lexeme + " ";
    }
    if (consumeSemicolon) {
        consume(TokenType::SEMICOLON, "Expected ';' at the end of the expression.");
    }
    return expression;
}
