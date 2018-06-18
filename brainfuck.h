#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// // save brainfuck code here
// static char code[10000];
// static int codeIndex; // mark which char wound run

// static char memory[100];
// static int memoryIndex; // mark current memory

struct Brain
{
    char code[10000]; // save instruction
    int codeIndex; // mark which char wound run
    char memory[100]; // the memory brainfuck use
    int memoryIndex; // mark current memory
};

char currentCode(const struct Brain *brain)
{
    const char *code = brain->code;
    const int codeIndex = brain->codeIndex;
    return code[codeIndex];
}

char currentValue(const struct Brain *brain)
{
    const char *memory = brain->memory;
    const int memoryIndex = brain->memoryIndex;
    return memory[memoryIndex];
}

// go to next code should be
static void nextCode(struct Brain *brain)
{
    brain->codeIndex += 1;
}

// judge code run over or not
static int codeEnd(const struct Brain *brain)
{
    return currentCode(brain) == '\0';
}

// > ++ptr;
static void nextMemory(struct Brain *brain)
{
    brain->memoryIndex += 1;
}

// < --ptr;
static void previousMemory(struct Brain *brain)
{
    brain->memoryIndex -= 1;
    if(brain->memoryIndex < 0){
        printf("memory out of range\n");
        exit(0);
    }
    else{
        ;
    }
}

// + ++*ptr;
static void plusMemory(struct Brain *brain)
{
    if(currentValue(brain) == 255){
        printf("value over flow up\n");
    }
    else{
        ;
    }

    brain->memory[brain->memoryIndex] += 1;
}

// - --*ptr;
static void minusMemory(struct Brain *brain)
{
    if(currentValue(brain) == 0){
        printf("value over flow down\n");
    }
    else{
        ;
    }

    brain->memory[brain->memoryIndex] -= 1;
}

// . putchar(*ptr);
static void output(const struct Brain *brain)
{
    char value = currentValue(brain);
    putchar(value);
    // printf("%u\n", (unsigned)value);
}

static void setValue(struct Brain *brain, char value)
{
    brain->memory[brain->memoryIndex] = value;
}

// , *ptr =getch();
static void input(struct Brain *brain)
{
    char in = getchar();
    setValue(brain, in);
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
static void leftBracket(struct Brain *brain)
{
    if(currentCode(brain) != '['){
        printf("[ not in current code\n");
        exit(0);
    }
    else{
        if(currentValue(brain) == 0){ // jump
            int rightBracketIndex = nextRight(brain->code, brain->codeIndex);
            brain->codeIndex = rightBracketIndex + 1;
        }
        else{
            ;
        }
    }
}

// ] }
static void rightBracket(struct Brain *brain)
{
    if(currentCode(brain) != ']'){
        printf("] not in current code\n");
        exit(0);
    }
    else{
        if(currentValue(brain) != 0){ // jump
            int leftBracketIndex = previousLeft(brain->code, brain->codeIndex);
            brain->codeIndex = leftBracketIndex;
        }
        else{
            ;
        }
    }
}

// return -1 if there is no code to run
void brainfuckOnce(struct Brain *brain)
{
    switch(currentCode(brain))
    {
    case '>':
        nextMemory(brain);
        break;
    case '<':
        previousMemory(brain);
        break;
    case '+':
        plusMemory(brain);
        break;
    case '-':
        minusMemory(brain);
        break;
    case '.': // output
        output(brain);
        break;
    case ',': // input
        input(brain);
        break;
    case '[':
        leftBracket(brain);
        break;
    case ']':
        rightBracket(brain);
        break;
    default:
        break;
    }
}

void initBrainfuckCode(struct Brain *brain, const char *str)
{
    strcpy(brain->code, str);
    brain->codeIndex = 0;
    int i;
    for(i = 0; i < 100; i++)
    {
        brain->memory[i] = 0;
    }
    brain->memoryIndex = 0;
}

void printBrainfuckState(const struct Brain *brain)
{
    const int codeIndex = brain->codeIndex;
    const char *code = brain->code;
    printf("code index:%d\n", codeIndex);
    printf("code value:%c\n", code[codeIndex]);
    const int memoryIndex = brain->memoryIndex;
    const char *memory = brain->memory;
    printf("memory index:%u\n", memoryIndex);
    printf("memory value:%u\n", memory[memoryIndex]);
    printf("--------------------\n");
}

// void brainfuck(const char *str)
// {
//     getBrainfuckCode(str);
//     while( !codeEnd() )
//     {
//         brainfuckOnce();
//         nextCode();
//         //printBrainfuckState();
//     }
// }

void brainfuck(const char *str)
{
    struct Brain it;
    initBrainfuckCode(&it, str);
    while( !codeEnd(&it) )
    {
        brainfuckOnce(&it);
        nextCode(&it);
        // printBrainfuckState(&it);
        // char temp;
        // scanf("%c", &temp);
    }
}