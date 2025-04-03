#include "./headers/interpreter.h"

void Interpreter::interpret(const std::vector<std::shared_ptr<Statement>>& statements) {
    for (const auto& statement : statements) {
        statement->execute();
    }
}
