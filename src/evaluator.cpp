#include "evaluator.h"
#include <cmath>
#include <stdexcept>

double Evaluator::evaluate(const Expr* expr) {
    switch (expr->type()) {
        case ExprType::INT: {
            auto* num = static_cast<const IntExpr*>(expr);
            return std::stod(num->value);
        }
        case ExprType::FLOAT: {
            auto* num = static_cast<const FloatExpr*>(expr);
            return std::stod(num->value);
        }
        case ExprType::Unary: {
            auto* unary = static_cast<const UnaryExpr*>(expr);
            double val = evaluate(unary->right.get());
            if (unary->op.type == TokenType::Minus) return -val;
            if (unary->op.type == TokenType::plus) return val;
            throw std::runtime_error("Unknown unary operator: " + unary->op.value);
        }
        case ExprType::Grouped: {
            auto* group = static_cast<const GroupedExpr*>(expr);
            return evaluate(group->expr.get());
        }
        case ExprType::Binary: {
            auto* bin = static_cast<const BinaryExpr*>(expr);
            double left = evaluate(bin->left.get());
            double right = evaluate(bin->right.get());

            switch (bin->op.type) {
                case TokenType::plus: return left + right;
                case TokenType::Minus: return left - right;
                case TokenType::Multiply: return left * right;
                case TokenType::Divide: return left / right;
                case TokenType::Power: return std::pow(left, right);
                default:
                    throw std::runtime_error("Unknown binary operator: " + bin->op.value);
            }
        }
    }
    throw std::runtime_error("Unknown expression type");
}
