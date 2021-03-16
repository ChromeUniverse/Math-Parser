# The Calculator

## An infix/postfix mathematical expresison parser and evaluator

This calculator can read infix math expressions, convert them to Reverse Polish Notation and evaluate the expression's result.

Based on an implementation of Edsger Dijkstra's [_Shunting Yard algorithm_](https://en.wikipedia.org/wiki/Shunting-yard_algorithm).

Example input:

`234.5 / ( -123.12 + 7.8 ) * 2.5`

Converted to RPN:

`234.5 -123.12 7.8 + / 2.5 *`

Expression result:

`-5.08368`


## Usage

1. Clone this repo

`git clone https://github.com/ChromeUniverse/Math-Parser.git`

2. Compile source files

* Infix to postfix converter:
  `g++ shunting_yard.cpp -o shunting_yard`

* RPN evaluator:
  `g++ rpn.cpp -o rpn`

* Full calculator:
  `g++ calc.cpp -o calc`
  

3. Run executable

_Note: check executable file permissions, you might need to use_ `chmod`


## Supported operations:

* Addition
* Subtraction
* Multiplication
* Division
* Exponentiation
* Multiple parentheses

## To-Do

* Add unary operators
* Add funtions (e.g. trig functions, logarithms, etc.)
* Add support for symbolic expression evualation (i.e. variables)
* Add graph plotting
