
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