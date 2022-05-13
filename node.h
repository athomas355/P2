#ifndef NODE_H
#define NODE_H
#include "token.h"

typedef enum {
	//nonterminals
	S_nd, R_nd, E_nd, A_nd, B_nd, C_nd, D_nd,
		F_nd, G_nd, T_nd, V_nd, H_nd, J_nd, K_nd,
		L_nd, W_nd, Z_nd,

	//terminals
	NAME_nd, IDENTIFIER_nd, SPOT_nd, PLACE_nd, HOME_nd,
		SHOW_nd, PERIOD_nd, LBRACK_nd, RBRACK_nd, IF_nd,
		DO_nd, AGAIN_nd, HERE_nd, NUMBER_nd, THERE_nd, ARR2_nd, ARRMINUS_nd,
		PLUS_nd, PERCENT_nd, AND_nd, SLASH_nd, ASSIGN_nd, 
		MOVE_nd, FLIP_nd
} node_type;

typedef struct node {
	node_type label;
	token token_1;
	token token_2;
	token token_3;
	token token_4;
	struct node* non_terminal_1;
	struct node* non_terminal_2;
	struct node* non_terminal_3;
	

} node;

#endif