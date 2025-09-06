#include "lexer.h"
#include <cctype>   

Lexer::Lexer(const std::string& input) : input(input), pos(0) {}

void Lexer::skipwhitespace(){
    while(pos<input.size() && std::isspace(input[pos])) ++pos;
}

char Lexer::peek() const{
    return pos < input.size() ? input[pos] : '\0';
}

char Lexer::advance(){
    return pos < input.size() ? input[pos++] : '\0';
}

Token Lexer::number(){
    size_t start = pos;
    
    while(pos<input.size() && std::isdigit(input.at(pos))) ++pos;
    if(input[pos] != '.') // no decimal shi
        return Token{TokenType::INT,input.substr(start,pos-start)};
    
    ++pos; // skip "."

    while(pos<input.size() && std::isdigit(input.at(pos))) ++pos;
    return Token{TokenType::FLOAT,input.substr(start,pos-start)};
}

Token Lexer::nextToken(){
    skipwhitespace();
    char curr = peek(); //input[pos]
    if(curr =='\0') return Token{TokenType::EndOfInput, ""};
    if(std::isdigit(curr)) return number();

    switch(curr){
        case '+': advance(); return Token{TokenType::plus, "+"};
        case '-': advance(); return Token{TokenType::Minus, "-"};
        case '*': advance(); return Token{TokenType::Multiply, "*"};
        case '/': advance(); return Token{TokenType::Divide, "/"};
        case '^': advance(); return Token{TokenType::Power, "^"};
        case '(': advance(); return Token{TokenType::LParen, "("};
        case ')': advance(); return Token{TokenType::RParen, ")"};
        default:  advance(); return Token{TokenType::Invalid, std::string(1, curr)};
    }
}