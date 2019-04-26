
main: brainfuck.h main.c
	gcc main.c -o main.o

lexer.o: lexer.h lexer.c
	gcc -Wall lexer.c -o lexer.o

parser.o: parser.h parser.c interpreter.h
	gcc -Wall parser.c -o parser.o

clean:
	rm *.o