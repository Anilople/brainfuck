#pragma once
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void interpreter(struct Node * node)
{
    static int bufferLength = 0;
    static char * buffer = NULL;
    static int index = 0;
    for(; NULL != node; node = node->circleNext) {

        if(index >= bufferLength) {
            // memory must increase
            int oldBufferLength = bufferLength;
            char * oldBuffer = buffer;

            int newBufferLength = (bufferLength + 1) * 2;
            char * newBuffer = (char *) malloc(newBufferLength * sizeof(char));
            
            if(NULL == newBuffer) {
                printf("no more memory to use!\n");
                exit(1);
            } else {
                memcpy(newBuffer, oldBuffer, oldBufferLength);
                // update bufferLength and buffer
                bufferLength = newBufferLength;
                buffer = newBuffer;
            }
        }

        if(Circle == node->nodeType) {
            char value = (char) (node->token.value);
            switch (value)
            {
            case '>': // move to right
                index += 1;
                if(index >= bufferLength) {

                }
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