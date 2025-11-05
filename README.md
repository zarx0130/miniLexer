# MiniLexer

C-based lexical analyzer that tokenizes source code files by identifying/categorizing different elements of programming languages (identifiers, keywords, operators, literals, comments)

# Features

1. Token Recognition - identifies token types including int/float, string/char, comment (single/multi line), reserved keywords, data types, operators (single/multi), & identifiers
2. Error Handling - handles file operations/token parsing
3. Flexible input - accepts source files as command-line args

# Token Types

INTEGER -- whole numbers (123, 42)
FLOAT -- decimal numbers (3.14, 2.0)
STRING -- string literals ("hello", "world")
CHAR  -- character literals ('a', 'z')
COMMENT -- single & multi-line comments (//, /**/)
TYPE -- data type keywords (int, float, void)
RESERVED -- language keywords (if, while, return)
OPERATOR -- operators (+, ==, <=, *)
IDENTIFIER -- variable/function names (count, calcSum)

# Compilation & Usage

gcc -o minilexer minilexer.c

./minilexer test1.c
./minilexer test2.c
./minilexer test3.c
./minilexer test4.c
./minilexer test5.c

# Supported Operators/Keywords

Arithmetic: +, -, *, /
Assignment: =, +=, -=
Comparison: ==, !=, <, >, <=, >=
Logical: &&, ||, !
Increment/Decrement: ++, --
Miscellaneous: (, ), {, }, ;, ,
boolean, char, const, double, float
int, long, short, void, volatile
Control flow: if, else, for, while, do, switch, case, break, continue
Functions: return, def, main
OOP: class, struct, new, this, super, extends
Access modifiers: public, private, protected, static
Exception handling: try, catch
Other: import, enum, default, false

# Example Output

Tokenizing: test1.c
-------------------
RESERVED: int
IDENTIFIER: x
OPERATOR: =
INTEGER: 5 (value: 5)
OPERATOR: ;

Tokenizing: test2.c
-------------------
OPERATOR: +
OPERATOR: -
OPERATOR: *
OPERATOR: (
OPERATOR: )
OPERATOR: ;
IDENTIFIER: c1

Tokenizing: test3.c
-------------------
OPERATOR: ==
OPERATOR: <=
OPERATOR: ++
OPERATOR: &&

Tokenizing: test4.c
-------------------
RESERVED: int
IDENTIFIER: x
OPERATOR: =
INTEGER: 123 (value: 123)
OPERATOR: ;
IDENTIFIER: count
OPERATOR: =
IDENTIFIER: count
OPERATOR: +
INTEGER: 1 (value: 1)
OPERATOR: ;

Tokenizing: test5.c
-------------------
RESERVED: int
RESERVED: main
OPERATOR: (
OPERATOR: )
OPERATOR: {
RESERVED: int
IDENTIFIER: x
OPERATOR: =
INTEGER: 5 (value: 5)
OPERATOR: ;
RESERVED: if
OPERATOR: (
IDENTIFIER: x
OPERATOR: >
INTEGER: 3 (value: 3)
OPERATOR: )
OPERATOR: {
RESERVED: return
IDENTIFIER: x
OPERATOR: ;
OPERATOR: }
OPERATOR: }

