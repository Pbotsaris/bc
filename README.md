# my_bc 

`my_bc` takes in an expression consisted of the operators `*`, `/`, `+`, `-`, `%` and numeric literals. The program then parsers through the input and evaluates result of the mathematical expression.

Floating point numbers are **not** supported.


## build 

    make


## clean
    
    make clean  


## run
    
    ./bin/my_bc "3+2*2"


## Parsing

Parsing is achieved via a [recursive descent parser](https://en.wikipedia.org/wiki/Recursive_descent_parser) implementation. Results are stored in an AST and evaluted by recursing through the tree.

Though not part of the current implementation, a printing is available to vizualize the resulting tree. Printing is possible with the following:

      tree_t ast; 
      ast.root = parser.parse(&parser, &tokenizer, argv[1]);
      ast.print(&ast);


## The modulo operator

   `%` in C is a remainder operator as defined by C99. So for negative numbers, operations such as `-77 % 2` would result in `-2`. The modulo operation, however, would equate to `3`.
   
   In `my_bc` the `%` refers to modulo operator, not the remainder operator.
