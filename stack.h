#ifndef STACK_H
#define STACK_H

#include "token.h"

typedef struct id_elem {
	token tk;
	struct id_elem* next;
} id_elem;

typedef struct {
	int size;
	id_elem *top;
}id_stack;

void push(token);
void pop();
void find(token, int);

#endif