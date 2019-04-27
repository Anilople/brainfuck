#pragma once
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BufferNode {
	char value;
	struct BufferNode * previous;
	struct BufferNode * next;
};

// void BufferNodePrint(struct BufferNode * bufferNode)
// {
	// printf(
		// "%c %d\t0x%x\t0x%x\n",
		// bufferNode->value,
		// bufferNode->value,
		// (bufferNode->previous), 
		// (bufferNode->next)
	// );
// }

void BufferNodeInit(struct BufferNode * bufferNode)
{
	bufferNode->value = 0;
	bufferNode->previous = NULL;
	bufferNode->next = NULL;
}

char BufferNodeGetValue(struct BufferNode * bufferNode)
{
	return bufferNode->value;
}

void BufferNodeSetValue(struct BufferNode * bufferNode, char value)
{
	bufferNode->value = value;
}

void BufferNodeValueInc(struct BufferNode * bufferNode)
{
	bufferNode->value += 1;
}

void BufferNodeValueDec(struct BufferNode * bufferNode)
{
	bufferNode->value -= 1;
}

struct BufferNode * BufferNodeGetPrevious(struct BufferNode * bufferNode)
{
	return bufferNode->previous;
}

void BufferNodeSetPrevious(struct BufferNode * bufferNode, struct BufferNode * previous)
{
	bufferNode->previous = previous; // previous <- bufferNode
	previous->next = bufferNode; // previous -> bufferNode
}

struct BufferNode * BufferNodeGetNext(struct BufferNode * bufferNode)
{
	return bufferNode->next;
}

void BufferNodeSetNext(struct BufferNode * bufferNode, struct BufferNode * next)
{
	bufferNode->next = next; // bufferNode -> next
	next->previous = bufferNode; // bufferNode <- next
}

void interpreter(struct Node * node)
{
    static struct BufferNode * bufferNode = NULL;
	if(NULL == bufferNode) {
		// just run one time
		bufferNode = (struct BufferNode *) malloc(sizeof(struct BufferNode));
		BufferNodeInit(bufferNode);
	}
	
    for(; NULL != node; node = node->circleNext) {
		// BufferNodePrint(bufferNode);
        if(Circle == node->nodeType) {
            char value = (char) (node->token.value);
            switch (value)
            {
            case '>': // move to right
            {
				if(NULL != BufferNodeGetNext(bufferNode)) {
					bufferNode = BufferNodeGetNext(bufferNode);
				} else {
					struct BufferNode * newNext = (struct BufferNode *) malloc(sizeof(struct BufferNode));
					BufferNodeInit(newNext);
					BufferNodeSetNext(bufferNode, newNext);
					bufferNode = newNext;
				}
			}
                break;
            case '<': // move to left
            {
				if(NULL != BufferNodeGetPrevious(bufferNode)) {
					bufferNode = BufferNodeGetPrevious(bufferNode);
				} else {
					struct BufferNode * newPrevious = (struct BufferNode *) malloc(sizeof(struct BufferNode));
					BufferNodeInit(newPrevious);
					BufferNodeSetPrevious(bufferNode, newPrevious);
					bufferNode = newPrevious;
				}
			}
                break;
            case '+': // increment
                BufferNodeValueInc(bufferNode);
                break;
            case '-': // decrement
                BufferNodeValueDec(bufferNode);
                break;
            case '.': // output byte
                printf("%c", BufferNodeGetValue(bufferNode));
                break;
            case ',': // input byte
			{
				static char c;
				scanf("%c", &c);
				BufferNodeSetValue(bufferNode, c);
			}
                break;
            default:
                break;
            }
        } else {
            // content in []
            while(0 != BufferNodeGetValue(bufferNode)) {
                interpreter(node->squareNext);
            }
        }
    }
}