#include "evaluator.h"
#include <stdexcept>
#include <cmath>

double Evaluator::evaluate(const Expr* expr) {
    if (auto intNode = dynamic_cast<const IntExpr*>(expr)) {
        return std::stod(intNode->value);
    }

    if (auto floatNode = dynamic_cast<const FloatExpr*>(expr)) {
        return std::stod(floatNode->value);
    }

    if (auto binNode = dynamic_cast<const BinaryExpr*>(expr)) {
        double left = evaluate(binNode->left.get());
        double right = evaluate(binNode->right.get());

        switch (binNode->op.type) {
        case TokenType::plus:     return left + right;
        case TokenType::Minus:    return left - right;
        case TokenType::Multiply: return left * right;
        case TokenType::Divide:   return left / right;
        case TokenType::Power:    return std::pow(left, right);
        default: throw std::runtime_error("cuh! unknown binary operator");
        }
    }

    if (auto unaryNode = dynamic_cast<const UnaryExpr*>(expr)) {
        double val = evaluate(unaryNode->right.get());
        switch (unaryNode->op.type) {
        case TokenType::plus:  return val;
        case TokenType::Minus: return -val;
        default: throw std::runtime_error("cuh! unknown unary operator");
        }
    }

    if (auto groupNode = dynamic_cast<const GroupedExpr*>(expr)) {
        return evaluate(groupNode->expr.get());
    }

    throw std::runtime_error("cuh! unknown expression type");
}
