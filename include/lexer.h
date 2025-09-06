#pragma once

#include <string>
#include <vector>

enum class TokenType {// fr struct Token 
    INT,
    FLOAT,
    plus, Minus,
    Multiply, Divide,
    Power,
    LParen, RParen,
    EndOfInput,
    Invalid
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    explicit Lexer(const std::string& input); //shutup compiler, me string
    Token nextToken();

    std::string input; ///full 
    size_t pos;
    
    ///whitespace
    void skipwhitespace();

    ///peek cur
    char peek() const;

    ///Advance/vroomvroom
    char advance();

    //parse a numeric token (int/decimal)
    Token number();
};