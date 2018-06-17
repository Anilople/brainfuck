#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// save brainfuck code here
static char code[10000];
static int codeIndex; // mark which char wound run

static char memory[100];
static int memoryIndex; // mark current memory

char currentCode()
{
    return code[codeIndex];
}

char currentValue()
{
    return memory[memoryIndex];
}

// go to next code should be
static void nextCode()
{
    codeIndex++;
}

static int codeEnd()
{
    return currentCode() == '\0';
}

// > ++ptr;
static void nextMemory()
{
    memoryIndex++;
}

// static void previousCode()
// {
//     codeIndex--;
//     if(codeIndex < 0){
//         printf("memory out of range\n");
//         exit(0);
//     }
//     else{
//         ;
//     }
// }

// < --ptr;
static void previousMemory()
{
    memoryIndex--;
    if(memoryIndex < 0){
        printf("memory out of range\n");
        exit(0);
    }
    else{
        ;
    }
}

// + ++*ptr;
static void plusMemory()
{
    if(memory[memoryIndex] == 255){
        printf("value over flow up\n");
    }
    else{
        ;
    }

    memory[memoryIndex]++;
}

// - --*ptr;
static void minusMemory()
{
    if(memory[memoryIndex] == 0){
        printf("value over flow down\n");
    }
    else{
        ;
    }
    memory[memoryIndex]--;
}

// . putchar(*ptr);
static void output()
{
    char value = memory[memoryIndex];
    putchar(value);
    // printf("%u\n", (unsigned)value);
}

// , *ptr =getch();
static void input()
{
    char in = getchar();
    memory[memoryIndex] = in;
}

// find ']' in next codes
static int nextRight(const char *code, int nowIndex)
{
    while(code[nowIndex] != '\0' && code[nowIndex] != ']')
    {
        nowIndex++;
    }

    if(code[nowIndex] == ']'){
        return nowIndex;
    }
    else{
        printf("cannot find right square bracket\n");
        exit(0);
    }
}

// find '[' in previous codes
static int previousLeft(const char *code, int nowIndex)
{
    while(nowIndex >= 0 && code[nowIndex] != '[')
    {
        nowIndex--;
    }
    if(nowIndex >= 0){
        // it mean that we find '['
        return nowIndex;
    }
    else{
        printf("cannot find left square bracket\n");
        exit(0);
    }
}

// [ while (*ptr) {
static void leftBracket()
{
    if(currentCode() != '['){
        printf("[ not in current code\n");
        exit(0);
    }
    else{
        if(currentValue() == 0){ // jump
            int rightBracketIndex = nextRight(code, codeIndex);
            codeIndex = rightBracketIndex + 1;
        }
        else{
            ;
        }
    }
}

// ] }
static void rightBracket()
{
    if(currentCode() != ']'){
        printf("] not in current code\n");
        exit(0);
    }
    else{
        if(currentValue() != 0){ // jump
            int leftBracketIndex = previousLeft(code, codeIndex);
            codeIndex = leftBracketIndex;
        }
        else{
            ;
        }
    }
}

// return -1 if there is no code to run
int brainfuckOnce()
{
    switch(currentCode())
    {
    case '>':
        nextMemory();
        break;
    case '<':
        previousMemory();
        break;
    case '+':
        plusMemory();
        break;
    case '-':
        minusMemory();
        break;
    case '.': // output
        output();
        break;
    case ',': // input
        input();
        break;
    case '[':
        leftBracket();
        break;
    case ']':
        rightBracket();
        break;
    default:
        break;
    }

    if(codeEnd()){
        // printf("there is no code to run\n");
        return -1;
    }
    else{
        nextCode();
        return 1;
    }
}

void getBrainfuckCode(const char *str)
{
    strcpy(code, str);
}

void printBrainfuckState()
{
    printf("code index:%d\n", codeIndex);
    printf("code value:%c\n", code[codeIndex]);
    printf("memory index:%u\n", memoryIndex);
    printf("memory value:%u\n", memory[memoryIndex]);
    printf("--------------------\n");
}

void brainfuck(const char *str)
{
    getBrainfuckCode(str);
    while(brainfuckOnce() != -1)
    {
        //printBrainfuckState();
    }
}