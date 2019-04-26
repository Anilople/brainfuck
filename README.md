An interpreter for program language "brainfuck"

### How to run?

#### Hello world!

open a shell in the local directory

```shell
make # lexer parser(include interpreter)
cat helloworld.txt | ./lexer.o | ./parser.o
```