#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

#include <stdlib.h>
#include <stdio.h>

struct Token scanToken()
{
    int line;
    int lineOffset;
    char value;
    scanf("%d\t%d\t%c", &line, &lineOffset, &value);
    return char2Token(value, line, lineOffset);
}

struct Node NodeInit(enum NodeType nodeType, struct Token token)
{
    struct Node node;
    node.nodeType = nodeType;
    node.token = token;
    node.circleNext = NULL;
    node.squareNext = NULL;
    return node;
}

int NodesEmpty(const struct Nodes * nodes)
{
    return NULL == nodes->head;
}

void NodeAppendCircle(struct Node * node, struct Node * circleNext)
{
    node->circleNext = circleNext;
}

void NodeSetSquare(struct Node * node, struct Node * squareNext)
{
    node->nodeType = Square;
    node->squareNext = squareNext;
}

struct Nodes NodesInit()
{
    struct Nodes nodes;
    nodes.head = NULL;
    nodes.last = NULL;
    return nodes;
}

int NodeLength(struct Node * node)
{
    int length = 0;
    for(; NULL != node; node = node->circleNext) {
        length += 1;
    }
    return length;
}

void NodePrintOrigin(struct Node * node)
{
    for(; NULL != node; node = node->circleNext) {
        if(Circle == node->nodeType) {
            printf("%c", (char) (node->token.value));
        } else {
            printf("[");
            NodePrintOrigin(node->squareNext);
            printf("]");
        }
    }
}

void NodePrint(int id, int subid, struct Node * node)
{
    int nowSubid = 0;
    printf("%d\t%d:", id, subid);
    for(struct Node * temp = node; NULL != temp; temp = temp->circleNext) {
        if(Circle == temp->nodeType) {
            printf("%c", (char) (temp->token.value));
        } else {
            printf("[%d %d]", id + 1, nowSubid);
            nowSubid += 1;
        }
    }
    printf("\n");

    nowSubid = 0;
    // now print token in square
    for(struct Node * temp = node; NULL != temp; temp = temp->circleNext) {
        if(Circle == temp->nodeType) {

        } else {
            NodePrint(id + 1, nowSubid, temp->squareNext);
            nowSubid += 1;
        }
    }
}

void NodesAppend(struct Nodes * nodes, struct Node * circleNext)
{
    if(NULL == nodes->last) {
        nodes->head = circleNext;
        nodes->last = circleNext;
    } else {
        NodeAppendCircle(nodes->last, circleNext);
        // after append circle, should change nodes->last
        nodes->last = circleNext;
    }
}

struct Nodes * parser(int (*haveNextToken)(), struct Token (*getNextToken)())
{
    struct Nodes * nodes = (struct Nodes *) malloc(sizeof(struct Nodes));
    *nodes = NodesInit();

    static int squareNumber = 0;

    while(haveNextToken()) {
        struct Token token = getNextToken();
        int value = token.value;

        struct Node * node;

        switch (value)
        {
        case '>':
            node = (struct Node *) malloc(sizeof(struct Node));
            *node = NodeInit(Circle, token);
            NodesAppend(nodes, node);
            break;
        case '<':
            node = (struct Node *) malloc(sizeof(struct Node));
            *node = NodeInit(Circle, token);
            NodesAppend(nodes, node);
            break;
        case '+':
            node = (struct Node *) malloc(sizeof(struct Node));
            *node = NodeInit(Circle, token);
            NodesAppend(nodes, node);
            break;
        case '-':
            node = (struct Node *) malloc(sizeof(struct Node));
            *node = NodeInit(Circle, token);
            NodesAppend(nodes, node);
            break;
        case '.':
            node = (struct Node *) malloc(sizeof(struct Node));
            *node = NodeInit(Circle, token);
            NodesAppend(nodes, node);
            break;
        case ',':
            node = (struct Node *) malloc(sizeof(struct Node));
            *node = NodeInit(Circle, token);
            NodesAppend(nodes, node);
            break;
        case '[': {
            squareNumber += 1;
            struct Nodes * nodesInSquare = parser(haveNextToken, getNextToken);
            
            // make node to be a Square node
            node = (struct Node *) malloc(sizeof(struct Node));
            NodeSetSquare(node, nodesInSquare->head);
            // append square node
            NodesAppend(nodes, node);
            
            // free memory
            free(nodesInSquare);
            break;
        }
        case ']':
            squareNumber -= 1;
            if(squareNumber >= 0) {
                // balance [] pair
                return nodes;
            } else {
                // not balance [] pair
                printf("] without [ previous! line %d offset %d\n!", token.line, token.lineOffset);
                exit(1);
            }
            break;
        default:
            break;
        }
    }

    return nodes;
}

int haveNextToken()
{
    return !feof(stdin);
}

struct Token getNextToken()
{
    return scanToken();
}

int main(int argc, char * argv[])
{
    struct Nodes * nodes = parser(haveNextToken, getNextToken);
    // NodePrint(0, 0, nodes->head);
    // printf("\n#########################################\n");
    // NodePrintOrigin(nodes->head);
    interpreter(nodes->head);
    return 0;
}