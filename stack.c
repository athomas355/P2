#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

static const int STACK_SIZE = 100;
static id_stack stack = { .size = 0, .top = NULL };

void push(token tk) {
	if (stack.size == STACK_SIZE) {
		printf("STACK OVERFLOW)\n");
		exit(-1);
	}

	id_elem *new_elem = (id_elem*)malloc(sizeof(id_elem));
	new_elem->tk.tok_type = tk.tok_type;
	strcpy(new_elem->tk.label, tk.label);
	new_elem->tk.line_number = tk.line_number;

	new_elem->next = stack.top;
	stack.top = new_elem;
	stack.size++;
}

void pop() {
	if (stack.size > 0) {
		id_elem* temp = stack.top;
		stack.top = temp->next;
		free(temp);
		stack.size--;
	}
	else {
		printf("STACK EMPTY\n");
		exit(-1);
	}
}

void find(token tk, int error) {
	int height;
	id_elem *current_elem = stack.top;

	for (height = 0; height < stack.size; height++) {
		if (strcmp(tk.label, current_elem->tk.label) == 0) {
			if (error == 1) {
				printf("Static Semantic ERROR: Variable '%s' was already define\n", tk.label);
				exit(-1);
			}
			if (error == 2) {
				return;
			}
		}

		current_elem = current_elem->next;
	}

	if (error == 2) {
		printf("Static Semantic ERROR: Variable '%s' was used before the definition\n", tk.label);
		exit(-1);
	}
}