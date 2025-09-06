Still inprogress ehe!, i'll clean the mess after m done fr, i promise :)

(っ◔◡◔)っ  include/lexer.h (Dry run) <--

input "3 + 4.5 * (2 - 1)"

init -> "3 + 4.5 * (2 - 1)" 
pos 0

1. space nah, peek 3 Token{Number, "3"}, pos 1 
2...... n likewise till EOL


(っ◔◡◔)っ  include/parser.h (explained) <--

1. we have a enum class ExprType <-- This enum is used to identify what kind of expression node you're dealing with — useful during evaluation or debugging.

2. AST (Polymorphic tree)  Basic expl-> https://www.youtube.com/watch?v=wINY109MG10
    Base class 
    struct Expr{
        virtual ~Expr() ensures proper cleanup when deleting derived objects. // runs both destructor

        type() is a pure virtual function — every subclass must implement it to identify its type.
    }

3. baby class NumberExpr represents literal numbers '32' or '3.14' we have val holding the number as a string, type overrides and tell hey mesa number (think of this as a leaf node)

4. baby class UaryExpr represents '-x' or '+x', we have op for -> '-,+',    then the 'x' it's operating on <-- RIGHT, Finally the type 'hey mesa unary'

5. baby Binary is simply doing <left> <any-operator> <right> 

<img width="1919" height="762" alt="image" src="https://github.com/user-attachments/assets/df6e29ca-a380-49f2-9bb0-7b01e30404a8" />
