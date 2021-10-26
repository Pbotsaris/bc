# BC

## Notes

Currently program can basic parse a numeric expression (inc parethesis) into an AST. Not much in terms of syntax error handling and no edge cases.

There are basically 4 structures which sumarizes well what the code is doing. 

- `tokenizer`. This struct holds the string with the expression to be tokenized in the `str` field as well as the the position of the cursor in `cursor`. This struct also encapsulates 2 "methods" `tokenizer.load` to load a string to the tokenizer and `tokenizer.get_next_token` to get the next token from the loaded string.
- `token`. Token structs are the ouput from the tokenizer. 
- `parser` the parser struct has a `lookahead` field which is basically the next token to be parsed. It parsers all tokens in a expression (only numerical literals and operators) using the "method" `parser.parse` and outputs an AST of nodes `node`.
- `node` these are the nodes of the AST.

The field `value` in the `token` struct is being used for both the numerical literal and operators. For that reason I am casting the `char` type to `long int` when storing in the struct and casting it back out when printing.

Note that there is also a `tree` struct to store the resulting AST from the parsing process. This struct has very basic functionality such as printing and freeing the tree. Some fields of this struct are not being used / need clean up.

--
Another note: You will notice that in the parser module the function `multiplicative_expression` that is evaluating mutiplcation and division is called within the `additive_expression`. This is to ensure that multiplication and division always take precedence. The same logic is applied with expression with parenthesis.
