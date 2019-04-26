#include "lexer.h"

#include <stdio.h>

struct Token char2Token(char c, int line, int lineOffset)
{
    struct Token token;
    token.value = (int) (c);
    token.line = line;
    token.lineOffset = lineOffset;
    return token;
}

void TokenPrint(struct Token token)
{
    printf("%d\t%d\t%c\n", token.line, token.lineOffset, (char)(token.value));
}

void lexer(int (*getNextChar)(void))
{
    int currentLine = 0;
    int lineOffset = 0;
    for(int c = getNextChar(); EOF != c; c = getNextChar()) {
        switch (c)
        {
        case '\n':
            currentLine += 1;
            lineOffset = 0;
            break;
        case '>':
        case '<':
        case '+':
        case '-':
        case '.':
        case ',':
        case '[':
        case ']': {
            struct Token token = char2Token(c, currentLine, lineOffset);
            lineOffset += 1;
            TokenPrint(token);
            break;
        }
        default:
            break;
        }
    }
}

int main(int argc, char * argv[])
{
    lexer(getchar);
    return 0;
}