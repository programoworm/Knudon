#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <memory>
#include "statements.h"

class Interpreter {
public:
    void interpret(const std::vector<std::shared_ptr<Statement>>& statements);
};

#endif
