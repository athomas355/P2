#ifndef TESTTREE_H
#define TESTTREE_H
#include "node.h"

void traversePreorder(node*, int);
void goToNode(node*, int);
void staticSemantics(node*, int*);
void preorder(node*, int*);
void verifyNode(node*, int*);
extern char* token_names[];

#endif