#include "parser.h"
#include <stdexcept>
#include <iostream>
#include <cctype>

// Constructor
parser::parser(Lexer &lexer) : lexer(lexer)
{
    advance(); // 1st token
}

// we go next tkn
void parser::advance()
{
    curr = lexer.nextToken();
}

// Operator precedence
int parser::getPrecedence(const Token &tok)
{
    switch (tok.type)
    {
    case TokenType::plus:
    case TokenType::Minus:
        return 1;
    case TokenType::Multiply:
    case TokenType::Divide:
        return 2;
    case TokenType::Power:
        return 3;
    default:
        return -1;
    }
}

// full Expr preced.. climbing
// parse expression
//    -> parsePrimary Number ya ( )
//    -> parseBinary
//       left? parse expression
//       op prase op
//       if no op
//       right? parse expression
std::unique_ptr<Expr> parser::parserExpression()
{
    auto left = parsePrimary();

    // if op found
    if (getPrecedence(curr) > 0)
    {
        left = parseBinary(std::move(left), 0);
    }

    std::cout << "Parsed expression: " << left->info() << std::endl;

    return left;
}

// Unary
std::unique_ptr<Expr> parser::parseUnary()
{
    Token op = curr;
    advance();
    auto right = parserExpression();
    auto node = std::make_unique<UnaryExpr>();
    node->op = op;
    node->right = std::move(right);
    return node;
}

std::unique_ptr<Expr> parser::parseBinary(std::unique_ptr<Expr> left, int precedence)
{
    while (true)
    {
        int currPrec = getPrecedence(curr);
        // End of file or lower precedence
        if (currPrec < precedence || curr.type == TokenType::EndOfInput)
            break;

        Token op = curr;
        advance();

        int nextPrec = currPrec + (op.type == TokenType::Power ? 0 : 1);
        auto right = parsePrimary();
        // 2 + 2 * 4
        if (getPrecedence(curr) > 0)
        {
            right = parseBinary(std::move(right), nextPrec);
        }

        auto binNode = std::make_unique<BinaryExpr>();
        binNode->left = std::move(left);
        binNode->op = op;
        binNode->right = std::move(right);
        left = std::move(binNode);
    }
    std::cout << "Parsed binary: " << left->info() << std::endl;
    return left;
}

std::unique_ptr<Expr> parser::parseGrouped()
{
    if (curr.type != TokenType::LParen)
    {
        throw std::runtime_error("Expected '(', got: '" + curr.value + "'");
    }
    advance(); // consume '('

    auto expr = parserExpression(); // parse inner expression

    if (curr.type != TokenType::RParen)
    {
        throw std::runtime_error("Expected ')', got: '" + curr.value + "'");
    }
    advance(); // consume ')'

    auto node = std::make_unique<GroupedExpr>();
    node->expr = std::move(expr);
    return node;
}

std::unique_ptr<Expr> parser::parsePrimary()
{
    if (curr.type == TokenType::INT)
    {
        auto node = std::make_unique<IntExpr>();
        node->value = curr.value;
        advance();
        std::cout << "Parsed primary: " << node->info() << std::endl;
        return node;
        
    }

    if (curr.type == TokenType::FLOAT)
    {
        auto node = std::make_unique<FloatExpr>();
        node->value = curr.value;
        advance();
        std::cout << "Parsed primary: " << node->info() << std::endl;
        return node;
    }

    if (curr.type == TokenType::LParen)
    {
        auto expr = parseGrouped();
        std::cout << "Parsed primary: " << expr->info() << std::endl;
        return expr;
    }

    // if we find op we parse unary
    if (curr.type == TokenType::plus || curr.type == TokenType::Minus)
    {
        auto expr = parseUnary();
        std::cout << "Parsed primary: " << expr->info() << std::endl;
        return expr;
    }

    if (curr.type == TokenType::EndOfInput)
    {
        throw std::runtime_error("Unexpected end of input");
    }

    if (curr.type == TokenType::Invalid)
    {
        throw std::runtime_error("Invalid token: '" + curr.value + "'");
    }

    throw std::runtime_error("Unexpected token: '" + curr.value + "'");
}
