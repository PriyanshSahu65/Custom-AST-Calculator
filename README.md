(っ◔◡◔)っ
# 🧮 Custom AST Cala

A C++ calculator that uses a **custom lexer**, a **recursive descent parser**, and builds an **Abstract Syntax Tree (AST)** to evaluate expressions with full operator precedence. No switch-case shortcuts — just real parsing power.

---

## ✂️ Lexer — `lexer.cpp`

Breaks input into tokens:
- Numbers → `INT`, `FLOAT`
- Operators → `+`, `-`, `*`, `/`, `^`
- Parentheses → `(`, `)`
- Whitespace is skipped
- Invalid characters are flagged

**Example:**
```
Input: "2 + 3.5 * (4 - 1)"
Tokens: INT(2), plus(+), FLOAT(3.5), Multiply(*), LParen, INT(4), Minus(-), INT(1), RParen
```

---

## 🧩 Parser — `parser.cpp`

Uses **precedence climbing** to build an AST:
- `parsePrimary()` handles numbers, parentheses, and unary ops
- `parseBinary()` builds binary expression nodes based on operator precedence
- `parseGrouped()` handles nested expressions like `(2 + 3)`
- `parserExpression()` kicks off the full parse

**Example AST for `2 + 3 * 4`:**
```
     +
    / \
   2   *
      / \
     3   4
```

---

## 🧮 Evaluation

Once the AST is built, it’s walked recursively to compute the result:
- Each node (IntExpr, FloatExpr, BinaryExpr, etc.) knows how to evaluate itself
- Operator precedence is respected automatically by the tree structure

---

## 📦 Example Flow

```cpp
Lexer lexer("2 + 3 * (4 - 1)");
parser p(lexer);
auto ast = p.parserExpression();
double result = ast->evaluate(); // returns 11
```

---

## 🌿 TL;DR

🧠 Custom AST parser  
✂️ Tokenized by custom lexer  
🪄 Expression-aware evaluation  
🧮 Built from scratch for precision and learning

---

## 📺 Learn ASTs Visually

1. [Abstract Syntax Tree Implementation With Example In ...](https://www.youtube.com/watch?v=xDqmlyWhvko)
2. [Understanding Abstract Syntax Trees with ASTExplorer](https://www.youtube.com/watch?v=_ZOY7bxJ_Yc)
3. [Understand Abstract Syntax Trees - ASTs - in Practical and ...](https://www.youtube.com/watch?v=tM_S-pa4xDk)
4. [What Is An Abstract Syntax Tree, With WealthFront Engineer ...](https://www.youtube.com/watch?v=wINY109MG10)
5. [Transform Content With Abstract Syntax Trees — Learn With ...](https://www.youtube.com/watch?v=acb2osL1VPE)
6. [Providing AST Definitions - Programming Language From ...](https://www.youtube.com/watch?v=4oQ-ZPaQs3k)
7. [Powerful Python source code processing with "ast"](https://www.youtube.com/watch?v=2tOr_0k8EYE)


<img width="1919" height="762" alt="image" src="https://github.com/user-attachments/assets/df6e29ca-a380-49f2-9bb0-7b01e30404a8" />
