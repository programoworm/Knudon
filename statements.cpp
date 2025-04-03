#include "./headers/statements.h"
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <stack>
#include <iostream>

// Global symbol table for variable storage
std::unordered_map<std::string, double> symbolTable;

void PrintStatement::execute() {
    std::istringstream stream(message);
    std::ostringstream evaluatedMessage;
    std::string token;
    std::string expression;

    // std::cout << "[DEBUG] Executing PrintStatement with message: " << message << std::endl;

    while (stream >> token) {
        // std::cout << "[DEBUG] Processing token: " << token << std::endl;

        if (token == "*" || token == "+" || token == "-" || token == "/") {
            // If it's an operator, add it to the expression
            expression += token + " ";
        } else if (symbolTable.find(token) != symbolTable.end()) {
            // If it's a variable, add its value to the expression
            expression += std::to_string(symbolTable[token]) + " ";
        } else if (std::isdigit(token[0])) {
            // If it's a number, add it to the expression
            expression += token + " ";
        } else if (token == ",") {
            // If it's a comma, evaluate the current expression and reset
            if (!expression.empty()) {
                try {
                    double result = evaluateExpression(expression);
                    // std::cout << "[DEBUG] Evaluated expression: " << expression << " = " << result << std::endl;
                    evaluatedMessage << result << " ";
                } catch (const std::runtime_error& e) {
                    std::cerr << "[ERROR] Failed to evaluate expression: " << expression << " (" << e.what() << ")\n";
                }
                expression.clear();
            }
            evaluatedMessage << ", ";
        } else if (token.front() == '"' && token.back() == '"') {
            // If it's a string literal, add it directly
            evaluatedMessage << token.substr(1, token.size() - 2) << " ";
        } else {
            // If it's a standalone variable or malformed token, add it directly
            if (!expression.empty()) {
                try {
                    double result = evaluateExpression(expression);
                    // std::cout << "[DEBUG] Evaluated expression: " << expression << " = " << result << std::endl;
                    evaluatedMessage << result << " ";
                } catch (const std::runtime_error& e) {
                    std::cerr << "[ERROR] Failed to evaluate expression: " << expression << " (" << e.what() << ")\n";
                }
                expression.clear();
            }
            evaluatedMessage << token << " ";
        }
    }

    // Evaluate any remaining expression
    if (!expression.empty()) {
        try {
            double result = evaluateExpression(expression);
            // std::cout << "[DEBUG] Evaluated final expression: " << expression << " = " << result << std::endl;
            evaluatedMessage << result << " ";
        } catch (const std::runtime_error& e) {
            std::cerr << "[ERROR] Failed to evaluate final expression: " << expression << " (" << e.what() << ")\n";
        }
    }

    // std::cout << "[DEBUG] Final evaluated message: " << evaluatedMessage.str() << std::endl;
    std::cout << evaluatedMessage.str() << std::endl;
}

double evaluateExpression(const std::string& expr) {
    // std::cout << "[DEBUG] Evaluating expression: " << expr << std::endl;

    std::istringstream stream(expr);
    std::stack<double> values;
    std::stack<char> operators;

    auto applyOperator = [](double a, double b, char op) -> double {
        // std::cout << "[DEBUG] Applying operator: " << op << " on " << a << " and " << b << std::endl;
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': 
                if (b == 0) throw std::runtime_error("Division by zero.");
                return a / b;
            default: throw std::runtime_error("Invalid operator.");
        }
    };

    auto precedence = [](char op) -> int {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    };

    std::string token;
    while (stream >> token) {
        // std::cout << "[DEBUG] Token in expression: " << token << std::endl;

        if (std::isdigit(token[0])) {
            values.push(std::stod(token));
        } else if (symbolTable.find(token) != symbolTable.end()) {
            values.push(symbolTable[token]);
        } else if (token == "+" || token == "-" || token == "*" || token == "/") {
            while (!operators.empty() && precedence(operators.top()) >= precedence(token[0])) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOperator(a, b, op));
            }
            operators.push(token[0]);
        } else {
            throw std::runtime_error("Invalid token in expression: " + token);
        }
    }

    while (!operators.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        values.push(applyOperator(a, b, op));
    }

    double result = values.top();
    // std::cout << "[DEBUG] Final result of expression: " << result << std::endl;
    return result;
}

void ExpressionStatement::execute() {
    // Parse and evaluate the expression, then store the result in the symbol table
    size_t equalPos = expression.find('=');
    if (equalPos == std::string::npos) {
        throw std::runtime_error("Invalid expression: " + expression);
    }

    std::string variable = expression.substr(0, equalPos - 1);
    std::string expr = expression.substr(equalPos + 1);

    // Evaluate the expression
    double value = evaluateExpression(expr);

    // Store the result in the symbol table
    symbolTable[variable] = value;

    // std::cout << "Evaluating expression: " << expression << " = " << value << std::endl;
}

// Explicit instantiations to force vtable generation
PrintStatement psInstance("dummy");
ExpressionStatement esInstance("dummy");

void forceVTableGeneration() {
    PrintStatement ps("dummy");
    ExpressionStatement es("dummy");
}
