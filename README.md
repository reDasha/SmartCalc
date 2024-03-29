# SmartCalc

## Implementation of regular calculator in C with GUI based on QT libraries and modules.

- This program parses the input string of arithmetic expression in infix notation, converts it to postfix notation (reverse Polish notation) and performs calculations using Dijkstra's algorithm.

- The input string can contain the following arithmetic operations and mathematical functions: (a + b), a - b, a * b, a/b, a ^ b, a mod b, -a, +b, sqrt(x), ln (x), log(x), cos(x), sin(x), tan(x), acos(x), asin(x), atan(x).

- The program can calculate arbitrary arithmetic expressions in parentheses in infix notation by replacing the value of the variable x with a number, as well as plot a graph of the function specified by the expression in infix notation with the variable x.

 <img src=https://github.com/reDasha/SmartCalc/blob/main/screenshot_calc1.png alt="drawing" width="500"/>

# To try on
```
$ git clone https://github.com/reDasha/SmartCalc.git
$ cd SmartCalc
$ make install
```
- You can enter up to 255 characters. The calculation will be performed after you enter the calculation expression and press `=`.
