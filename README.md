An interpreter for program language "brainfuck"

### How to run?

#### Hello world!

open a shell in the local directory

```shell
make # build interpreter program
./main helloworld.txt # then use it to run brainfuck code in txt
```

#### run my code self

open a shell in the local directory
write brainfuck code in a file
for instance, write it in file "mycode.txt"

```shell
make
./main mycode.txt 
```

if you don't crete a new file like "mycode.txt" for your brainfuck code, you can write the code in helloworld.txt. then run it like "Hello world!" example.
