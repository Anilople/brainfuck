#pragma once

#include "lexer.h"

enum NodeType {
    Circle, // > < + - . ,
    Square // [ ] pair
};

/*
    Circle node:
        nodeType = Circle
        token exist
        circleNext is NULL or not
        squareNext is NULL
    Square node:
        nodeType = Square
        token have no meaning
        circleNext is NULL or not
        squareNext is not NULL
*/
struct Node {
    enum NodeType nodeType;
    struct Token token;
    struct Node * circleNext;
    struct Node * squareNext; // for contents between '[' and ']'
};


struct Node NodeInit(enum NodeType nodeType, struct Token token);

int NodeLength(struct Node * node);

void NodePrintOrigin(struct Node * node);

void NodePrint(int id, int subid, struct Node * node);

// parameters are not NULL
void NodeAppendCircle(struct Node * node, struct Node * circleNext);

// parameters are not NULL
void NodeSetSquare(struct Node * node, struct Node * squareNext);

/*
    use Nodes to let append complex be O(1)
*/
struct Nodes {
    struct Node * head;
    struct Node * last;
};

struct Nodes NodesInit();

int NodesEmpty(const struct Nodes * nodes);

// parameters are not NULL
void NodesAppend(struct Nodes * nodes, struct Node * circleNext);

/*
    return Node linklist
*/
struct Nodes * parser(int (*haveNextToken)(), struct Token (*getNextToken)());