
expr: factor ((MUL/DIV) factor)*
factor: INTEGER

deriving the grammar of Expr = 10 * 2 / 5

factor MUL factor ((MUL/DIV) factor)*
factor MUL factor DIV factor
INTEGER MUL INTEGER DIV INTEGER
10 * 2 / 5


--------------------------
Write a grammar that describes arithmetic expressions containing any number of +, -, *, or / operators. With the grammar you should be able to derive expressions like “2 + 7 * 4”, “7 - 8 / 4”, “14 + 2 * 3 - 6 / 2”, and so on.

expr: factor ((ADD | SUB | MULT | DIV) factor)*
factor: INTEGER

-----------
CFG that handles associativity and the precedence of operators

expr: term((PLUS| MIN) term)*
term: factor((MUL | DIV) factor)*
factor: INTEGER

10 + 3 * 4 + 5

result = factor(10)
result = 10 + term(3 * 4)
result = 10 + term()

-----
CFG that handles parenthesis

expr: term((PLUS | MIN) term)*
term: factor((MUL | DIV) factor)*
factor: INTEGER | LPAREN expr RPAREN

(10 + 2) * 6

factor(lparent)
factor(10)
result = term(10)
result = 10 + term(2)
result = 12
