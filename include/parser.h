#pragma once

#include <memory>
#include "lexer.h"
#include <string>

enum class ExprType {
    INT,
    FLOAT,
    Unary,
    Binary,
    Grouped
};

inline std::string printExprType(ExprType type) {
    switch (type) {
        case ExprType::INT: return "INT";
        case ExprType::FLOAT: return "FLOAT";
        case ExprType::Unary: return "Unary";
        case ExprType::Binary: return "Binary";
        case ExprType::Grouped: return "Grouped";
        default: return "Unknown";
    }
}

struct Expr {
    virtual ~Expr() = default; //run both destru
    virtual ExprType type() const = 0; // tell me who y are?
    virtual std::string info() const = 0; // for debug
};

// 123 456
struct IntExpr : Expr {
    std::string value;
    ExprType type() const override {return ExprType::INT;}
    std::string info() const override { return "IntExpr: " + value; }
};

// 0.1 3.14
struct FloatExpr : Expr {
    std::string value;
    ExprType type() const override {return ExprType::FLOAT;}
    std::string info() const override { return "FloatExpr: " + value; }
};

// op right
struct UnaryExpr : Expr {
    Token op;
    std::unique_ptr<Expr> right;
    ExprType type() const override {return ExprType::Unary;}
    std::string info() const override { return "UnaryExpr: " + op.value; }
};

// left op right
struct BinaryExpr : Expr {
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;
    ExprType type() const override {return ExprType::Binary;}
    std::string info() const override { return "BinaryExpr: left :" + left->info() + " op :" + op.value + " right : " +  right->info(); }
};

// ( expr )
struct GroupedExpr : Expr {
    std::unique_ptr<Expr> expr;
    ExprType type() const override {return ExprType::Grouped;}
    std::string info() const override { return "GroupedExpr: expr: " + expr->info(); }

};

class parser {
public:
    explicit parser(Lexer& lexer); //const
    std::unique_ptr<Expr> parserExpression();
    const Token& currentToken() const { return curr; }
private:
    Lexer& lexer;
    Token curr;

    void advance(); // advance fxxx
    std::unique_ptr<Expr> parsePrimary();
    std::unique_ptr<Expr> parseUnary();
    std::unique_ptr<Expr> parseGrouped();
    std::unique_ptr<Expr> parseBinary(std::unique_ptr<Expr> left, int precedence);

    int getPrecedence(const Token& tok); // precedence
};
