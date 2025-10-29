
expr: factor ((MUL/DIV) factor)*
factor: INTEGER

deriving the grammar of Expr = 10 * 2 / 5

factor MUL factor ((MUL/DIV) factor)*
factor MUL factor DIV factor
INTEGER MUL INTEGER DIV INTEGER
10 * 2 / 5