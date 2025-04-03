#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include "tokens.h"
#include "statements.h"

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    std::vector<std::shared_ptr<Statement>> parse();

private:
    const std::vector<Token>& tokens;
    size_t current = 0;

    bool isAtEnd();
    const Token& advance();
    const Token& peek();
    const Token& previous();
    bool match(TokenType type);
    const Token& consume(TokenType type, const std::string& errorMessage);

    std::string parseExpression(bool consumeSemicolon = true); 

    std::shared_ptr<Statement> statement();
    std::shared_ptr<Statement> printStatement();
    std::shared_ptr<Statement> expressionStatement();
};

#endif // PARSER_H