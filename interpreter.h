#pragma once
#include "parser.h"
#include <stdio.h>

void interpreter(struct Node * node)
{
    static char buffer[10000];
    static int index = 0;
    for(; NULL != node; node = node->circleNext) {
        if(Circle == node->nodeType) {
            char value = (char) (node->token.value);
            switch (value)
            {
            case '>': // move to right
                index += 1;
                /* code */
                break;
            case '<': // move to left
                index -= 1;
                break;
            case '+': // increment
                buffer[index] += 1;
                break;
            case '-': // decrement
                buffer[index] -= 1;
                break;
            case '.': // output byte
                printf("%c", buffer[index]);
                break;
            case ',': // input byte
                scanf("%c", &(buffer[index]));
                break;
            default:
                break;
            }
        } else {
            // content in []
            while(0 != buffer[index]) {
                interpreter(node->squareNext);
            }
        }
    }
}