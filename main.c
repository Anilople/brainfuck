#include<stdio.h>
#include "brainfuck.h"

int main(int argc, char **argv)
{
    if(argc > 1){
        char *filename = argv[1];
        // printf("file name:%s\n", filename);
        FILE *file = fopen(filename, "r");
        if(NULL == file){
            printf("Open file error! [%s]", filename);
            exit(0);
        }
        static char code[10000];
        int codeLen = 0;
        char in;
        while(EOF != fscanf(file, "%c", &in))
        {
            // printf("in:%c\n", in);
            code[codeLen] = in;
            codeLen += 1;
        }
        code[codeLen]='\0';
        codeLen += 1;
        // printf("receive:\n%s\n", code);
        brainfuck(code);
    }
    else{
        printf("lack brainfuck code file\n");
    }
    return 0;
}