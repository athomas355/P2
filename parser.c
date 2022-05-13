#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "node.h"
#include "scanner.h"
#include "testTree.h"
#include "parser.h"

static FILE* file_ptr;
static token tk;
extern char *token_names[];

node * createNode(node_type label) {
	node* new_node = (node*)malloc(sizeof(node));

	new_node->label = label;

	token token_1 = { .tok_type = NULL_tk, .label = "", .line_number = 0 };
	token token_2 = { .tok_type = NULL_tk, .label = "", .line_number = 0 };
	token token_3 = { .tok_type = NULL_tk, .label = "", .line_number = 0 };
	token token_4 = { .tok_type = NULL_tk, .label = "", .line_number = 0 };

	new_node->token_1 = token_1;
	new_node->token_2 = token_2;
	new_node->token_3 = token_3;
	new_node->token_4 = token_4;

	new_node->non_terminal_1 = NULL;
	new_node->non_terminal_2 = NULL;
	new_node->non_terminal_3 = NULL;

	return new_node;
}

node* parser(FILE* file) {
	file_ptr = file;
	node* root;

	lookahead_char(file_ptr);
	
	tk = scanner(file_ptr);

	root = S();
	
	//if (tk.tok_type != EOF_tk) {
	//	printf("Parser ERROR: Recieved a token '%s' after the EOF_tk\n", token_names[tk.tok_type]);
	//}

	printf("Parser Completed Successfully\n");
	return root;
}

node* S() {
	node* node = createNode(S_nd);
	if (tk.tok_type == NAME_tk) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		if (tk.tok_type == ID_tk) {
			node->token_2 = tk;
			tk = scanner(file_ptr);

			if (tk.tok_type == SPOT_tk) {
				node->token_3 = tk;
				tk = scanner(file_ptr);

				if (tk.tok_type == ID_tk) {
					node->token_4 = tk;
					tk = scanner(file_ptr);

					node->non_terminal_1 = R();
					node->non_terminal_2 = E();

					return node;
				}
				printf("Parser ERROR:S: Incorrect token\n");
				exit(-1);
			}
			printf("Parser ERROR:S: Incorrect token\n");
			exit(-1);
		}
		printf("Parser ERROR:S: Incorrect token\n");
		exit(-1);
	}
	printf("Parser ERROR:S: Incorrect token\n");
	exit(-1);
}

node* R() {
	node* node = createNode(R_nd);

	if (tk.tok_type == PLACE_tk) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		node->non_terminal_1 = A();
		node->non_terminal_2 = B();

		if (tk.tok_type == HOME_tk) {
			node->token_2 = tk;
			tk = scanner(file_ptr);

			return node;
		}
		printf("Parser ERROR:R: Incorrect token\n");
		exit(-1);
	}
	printf("Parser ERROR:R: Incorrect token\n");
	exit(-1);
}

node* E() {
	node* node = createNode(E_nd);

	if (tk.tok_type == SHOW_tk) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		if (tk.tok_type == ID_tk) {
			node->token_2 = tk;
			tk = scanner(file_ptr);

			return node;
		}
		printf("Parser ERROR: E: Incorrect token\n");
		exit(-1);
	}
	printf("Parser ERROR: E: Incorrect token\n");
	exit(-1);
}

node* A() {
	node* node = createNode(A_nd);

	if (tk.tok_type == NAME_tk) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		if (tk.tok_type == ID_tk) {
			node->token_2 = tk;
			tk = scanner(file_ptr);

			return node;
		}
		printf("Parser ERROR: A: Incorrect token\n");
		exit(-1);
	}
	printf("Parser ERROR: A: Incorrect token\n");
	exit(-1);
}

node* B() {
	node* node = createNode(B_nd);

	if (tk.tok_type == OP_tk && !strcmp(tk.label, ".")) {	//try tk.label if that doesn't work
		node->token_1 = tk;
		tk = scanner(file_ptr);

		node->non_terminal_1 = C();

		if (tk.tok_type == OP_tk && !strcmp(tk.label, ".")) {
			node->token_2 = tk;
			tk = scanner(file_ptr);

			node->non_terminal_2 = B();

			return node;
		}
		else {
			printf("Parser ERROR: B: Incorrect token\n");
			exit(-1);
		}
	}
	else if (tk.tok_type == OP_tk && !strcmp(tk.label, "/")) {

		node->non_terminal_2 = D();
		node->non_terminal_3 = B();

		return node;
		
	}
	else if (tk.tok_type == ASSIGN_tk) {

		node->non_terminal_2 = D();
		node->non_terminal_3 = B();

		return node;

	}
	else if (tk.tok_type == SPOT_tk || tk.tok_type == MOVE_tk) {

		node->non_terminal_2 = D();
		node->non_terminal_3 = B();

		return node;

	}
	else if (tk.tok_type == FLIP_tk) {

		node->non_terminal_2 = D();
		node->non_terminal_3 = B();

		return node;

	}
	else if (tk.tok_type == SHOW_tk) {

		node->non_terminal_2 = D();
		node->non_terminal_3 = B();

		return node;

	}
	else if (tk.tok_type == OP_tk && !strcmp(tk.label, "{")) {

		node->non_terminal_2 = D();
		node->non_terminal_3 = B();

		return node;

	}
	else {
		token temp = tk;
		strcpy(temp.label, "Empty");
		node->token_1 = temp;

		return node;
	}
}

node* C() {
	node* node = createNode(C_nd);

	if (tk.tok_type == OP_tk && !strcmp(tk.label, "{")) {
		node->non_terminal_1 = F();

		return node;
	}
	else if (tk.tok_type == HERE_tk) {
		node->non_terminal_1 = G();

		return node;
	}
	else {
		printf("Parser ERROR: C: Incorrect token\n");
		exit(-1);
	}
}

node* D() {
	node* node = createNode(D_nd);

	if (tk.tok_type == OP_tk && !strcmp(tk.label, "/")) {
		node->non_terminal_1 = H();

		return node;
	}
	else if (tk.tok_type == ASSIGN_tk) {
		node->non_terminal_1 = J();

		return node;
	}
	else if (tk.tok_type == SPOT_tk) {
		node->non_terminal_1 = K();

		return node;
	}
	else if (tk.tok_type == FLIP_tk) {
		node->non_terminal_1 = L();

		return node;
	}
	else if (tk.tok_type == SHOW_tk) {
		node->non_terminal_1 = E();

		return node;
	}
	else if (tk.tok_type == OP_tk && !strcmp(tk.label, "{")) {
		node->non_terminal_1 = F();

		return node;
	}
	else {
		printf("Parser ERROR: D: Incorrect token\n");
		exit(-1);
	}
	
}

node* F() {
	node* node = createNode(F_nd);

	if (tk.tok_type == OP_tk && !strcmp(tk.label, "{")) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		if (tk.tok_type == IF_tk) {
			node->token_2 = tk;
			tk = scanner(file_ptr);

			if (tk.tok_type == ID_tk) {
				node->token_3 = tk;
				tk = scanner(file_ptr);

				node->non_terminal_1 = T();
				node->non_terminal_2 = W();
				node->non_terminal_3 = D();
				
				if (tk.tok_type == OP_tk && !strcmp(tk.label, "}")) {
					node->token_4 = tk;
					tk = scanner(file_ptr);

					return node;
				}
				printf("Parser ERROR: F: Incorrect token\n");
				exit(-1);
			}
			printf("Parser ERROR: F: Incorrect token\n");
			exit(-1);
		}
		else if (tk.tok_type == DO_tk) {
			node->token_2 = tk;
			tk = scanner(file_ptr);

			if (tk.tok_type == AGAIN_tk) {
				node->token_3 = tk;
				tk = scanner(file_ptr);

				node->non_terminal_1 = D();
				node->non_terminal_2 = T();
				node->non_terminal_3 = W();

				if (tk.tok_type == OP_tk && !strcmp(tk.label, "}")) {
					node->token_4 = tk;
					tk = scanner(file_ptr);

					return node;
				}
				printf("Parser ERROR: F: Incorrect token\n");
				exit(-1);
			}
			printf("Parser ERROR: F: Incorrect token\n");
			exit(-1);
		}
		printf("Parser ERROR: F: Incorrect token\n");
		exit(-1);
	}
	printf("Parser ERROR: F: Incorrect token\n");
	exit(-1);
}

node* G() {
	node* node = createNode(G_nd);

	if (tk.tok_type == HERE_tk) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		if (tk.tok_type == NUM_tk) {
			node->token_2 = tk;
			tk = scanner(file_ptr);

			if (tk.tok_type == THERE_tk) {
				node->token_3 = tk;
				tk = scanner(file_ptr);

				return node;
			}
			printf("Parser ERROR:G: Incorrect token\n");
			exit(-1);
		}
		printf("Parser ERROR:G: Incorrect token\n");
		exit(-1);
	}
	printf("Parser ERROR:G: Incorrect token\n");
	exit(-1);
}

node* T() {
	node* node = createNode(T_nd);

	if (tk.tok_type == OP_tk && !strcmp(tk.label, "<<")) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		return node;
	}
	else if (tk.tok_type == OP_tk && !strcmp(tk.label, "<-")) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		return node;
	}
	else {
		printf("Parser ERROR: T: Incorrect token\n");
		exit(-1);
	}
}

node* V() {
	node* node = createNode(V_nd);

	if (tk.tok_type == OP_tk && !strcmp(tk.label, "+")) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		return node;
	}
	else if (tk.tok_type == OP_tk && !strcmp(tk.label, "%")) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		return node;
	}
	else if (tk.tok_type == OP_tk && !strcmp(tk.label, "&")) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		return node;
	}
	else {
		printf("Parser ERROR: V: Incorrect token\n");
		exit(-1);
	}
}

node* H() {
	node* node = createNode(H_nd);

	if (tk.tok_type == OP_tk && !strcmp(tk.label, "/")) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		node->non_terminal_1 = Z();
		
		return node;
	}
	printf("Parser ERROR: H: Incorrect token\n");
	exit(-1);
}

node* J() {
	node* node = createNode(J_nd);

	if (tk.tok_type == ASSIGN_tk) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		if (tk.tok_type == ID_tk) {
			node->token_2 = tk;
			tk = scanner(file_ptr);

			node->non_terminal_1 = D();

			return node;
		}
		printf("Parser ERROR: J: Incorrect token\n");
		exit(-1);
	}
	printf("Parser ERROR: J: Incorrect token\n");
	exit(-1);
}

node* K() {
	node* node = createNode(K_nd);
	
	if (tk.tok_type == SPOT_tk) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		if (tk.tok_type == NUM_tk) {
			node->token_2 = tk;
			tk = scanner(file_ptr);

			if (tk.tok_type == SHOW_tk) {
				node->token_3 = tk;
				tk = scanner(file_ptr);

				if (tk.tok_type == NUM_tk) {
					node->token_4 = tk;
					tk = scanner(file_ptr);

					return node;
				}
				printf("Parser ERROR: K: Incorrect token\n");
				exit(-1);
			}
			printf("Parser ERROR: K: Incorrect token\n");
			exit(-1);
		}
		printf("Parser ERROR: K: Incorrect token\n");
		exit(-1);
	}
	else if (tk.tok_type == MOVE_tk) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		if (tk.tok_type == ID_tk) {
			node->token_2 = tk;
			tk = scanner(file_ptr);

			if (tk.tok_type == SHOW_tk) {
				node->token_3 = tk;
				tk = scanner(file_ptr);

				if (tk.tok_type == ID_tk) {
					node->token_4 = tk;
					tk = scanner(file_ptr);

					return node;
				}
				printf("Parser ERROR: K: Incorrect token\n");
				exit(-1);
			}
			printf("Parser ERROR: K: Incorrect token\n");
			exit(-1);
		}
		printf("Parser ERROR: K: Incorrect token\n");
		exit(-1);
	}
	else {
		printf("Parser ERROR: K: Incorrect token\n");
		exit(-1);
	}
}

node* L() {
	node* node = createNode(L_nd);
	
	if (tk.tok_type == FLIP_tk) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		if (tk.tok_type == ID_tk) {
			node->token_1 = tk;
			tk = scanner(file_ptr);

			return node;
		}
		printf("Parser ERROR: L: Incorrect token\n");
		exit(-1);
	}
	printf("Parser ERROR: L: Incorrect token\n");
	exit(-1);
}

node* W() {
	node* node = createNode(W_nd);

	if (tk.tok_type == NUM_tk) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		if (tk.tok_type == OP_tk && !strcmp(tk.label, ".")) {
			node->token_2 = tk;
			tk = scanner(file_ptr);

			return node;
		}
		else if (tk.tok_type == OP_tk && !strcmp(tk.label, "+")) {
			node->token_2 = tk;
			tk = scanner(file_ptr);

			if (tk.tok_type == NUM_tk) {
				node->token_3 = tk;
				tk = scanner(file_ptr);

				return node;
			}
			printf("Parser ERROR: W: Incorrect token\n");
			exit(-1);
		}
		else if (tk.tok_type == OP_tk && !strcmp(tk.label, "%")) {
			node->token_2 = tk;
			tk = scanner(file_ptr);

			if (tk.tok_type == NUM_tk) {
				node->token_3 = tk;
				tk = scanner(file_ptr);

				return node;
			}
			printf("Parser ERROR: W: Incorrect token\n");
			exit(-1);
		}
		else if (tk.tok_type == OP_tk && !strcmp(tk.label, "&")) {
			node->token_2 = tk;
			tk = scanner(file_ptr);

			if (tk.tok_type == NUM_tk) {
				node->token_3 = tk;
				tk = scanner(file_ptr);

				return node;
			}
			printf("Parser ERROR: W: Incorrect token\n");
			exit(-1);
		}
		else {
			printf("Parser ERROR: W: Incorrect token\n");
			exit(-1);
		}
	}
	printf("Parser ERROR: W: Incorrect token\n");
	exit(-1);
}

node* Z() {
	node* node = createNode(Z_nd);

	if (tk.tok_type == ID_tk) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		return node;
	}
	else if (tk.tok_type == NUM_tk) {
		node->token_1 = tk;
		tk = scanner(file_ptr);

		return node;
	}
	else {
		printf("Parser ERROR: Z: Incorrect token\n");
		exit(-1);
	}
}