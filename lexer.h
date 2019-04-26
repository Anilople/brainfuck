#pragma once

struct Token {
    int value; /* < > + - . , [ ] */
    int line; // which line token in
    int lineOffset; // token's index in this line [0, ...]
};

struct Token char2Token(char c, int line, int lineOffset);

/*
    #line lineOffset value
*/
void TokenPrint(struct Token token);

/*
    string to tokens
    and print them
*/
void lexer(int (*getNextChar)(void));