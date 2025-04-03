#ifndef STATEMENTS_H
#define STATEMENTS_H

#include <string>

class Statement {
public:
    virtual ~Statement() = default;
    virtual void execute() = 0;
};

class PrintStatement : public Statement {
public:
    explicit PrintStatement(const std::string& message) : message(message) {}
    void execute() override;
    virtual ~PrintStatement() = default;

private:
    std::string message;
};

class ExpressionStatement : public Statement {
public:
    explicit ExpressionStatement(const std::string& expression) : expression(expression) {}
    void execute() override;
    virtual ~ExpressionStatement() = default;

private:
    std::string expression;
};

// Declare the evaluateExpression function
double evaluateExpression(const std::string& expr);

#endif
