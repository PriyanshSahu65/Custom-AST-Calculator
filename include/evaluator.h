#pragma once
#include <memory>
#include "lexer.h"
#include "parser.h"

class Evaluator {
public:
    static double evaluate(const Expr* expr);
};
