# BC

## Notes

There are basically 3 structures which sumarizes well what the code is doing. 

- `tokenizer`. This struct holds the string with the expression to be tokenized in the `str` field as well as the the position of the cursor in `cursor`. This struct also encapsulates 2 "methods" `tokenizer.load` to load a string to the tokenizer and `tokenizer.get_next_token` to get the next token from the loaded string.
- `token`. Token structs are the ouput from the tokenizer. 
- `parser` the parser struct has a `lookahead` field which is basically the next token to be parsed. It parsers all tokens in a expression (only numerical literals and operators) using the "method" `parser.parse` and outputs an AST of nodes `node`.
- `node` these are the nodes of the AST.

The field `value` in the `token` struct is being used for both the numerical literal and operators. For that reason I am casting the `char` type to `long int` when storing in the struct and casting it back out when printing.

Note that there is a `tree` struct which are currently not being used. When I first kicked off the project I though I'd need one but I will probably not need it as the parser will already output a tree or an AST.

`main.c` has printf to test the parsing as well as some commented code with the old tree I had. Please ignore those.
