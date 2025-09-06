#include <iostream>
#include <string>
// using namespace std

/*
int main(){
    std::string input;

    std::cout << "typeshi here!, type 'q' to quit \n ";

    while(true){
        std::cout << ">";
        std::getline(std::cin, input);

        if(input=="q") break;
        if(input.empty()) continue;

        //placeholder fr : Lex -> par - > eval
        std::cout << "Echo: " << input << "\n";
    }
    std::cout<<"Bye Bye!";
    return 0;
}
*/

/*
#include "lexer.h"
int main() {
    std::string input;
    std::getline(std::cin, input);
    Lexer lexer(input);

    Token token;
    while ((token = lexer.nextToken()).type != TokenType::EndOfInput) {
        std::cout << "Token: " << token.value << " | Type: " << static_cast<int>(token.type) << "\n";
    }
}
*/

#include "lexer.h"
#include "parser.h"
#include <vector>
#include <memory>

// AST
void printAST(const Expr* expr) {
    switch (expr->type()) {
        case ExprType::INT: {
            auto* num = static_cast<const IntExpr*>(expr);
            std::cout << num->value;
            break;
        }
        case ExprType::Grouped: {
            auto* group = static_cast<const GroupedExpr*>(expr);
            std::cout << "(";
            printAST(group->expr.get());
            std::cout << ")";
            break;
        }
        case ExprType::FLOAT: {
            auto* num = static_cast<const FloatExpr*>(expr);
            std::cout << num->value;
            break;
        }
        case ExprType::Unary: {
            auto* unary = static_cast<const UnaryExpr*>(expr);
            std::cout << "(" << unary->op.value;
            printAST(unary->right.get());
            std::cout << ")";
            break;
        }
        case ExprType::Binary: {
            auto* bin = static_cast<const BinaryExpr*>(expr);
            std::cout << "(";
            printAST(bin->left.get());
            std::cout << " " << bin->op.value << " ";
            printAST(bin->right.get());
            std::cout << ")";
            
            break;
        }
    }
}
int main() {
    std::string input;
    std::getline(std::cin,input);
    Lexer lexer(input);
    parser p(lexer);

    try {
        std::unique_ptr<Expr> ast = p.parserExpression();
        // Check for unexpected input after parsing (only at top level)
        if (p.currentToken().type != TokenType::EndOfInput) {
            throw std::runtime_error("Unexpected input after expression");
        }
        std::cout << "Parsed AST: ";
        printAST(ast.get());
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Parser error: " << e.what() << std::endl;
    }

    return 0;
}

