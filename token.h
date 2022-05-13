#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
	//null token
	NULL_tk = -1,

	//keyword tokens
	AGAIN_tk = 0, IF_tk, ASSIGN_tk, MOVE_tk, SHOW_tk, FLIP_tk, NAME_tk, HOME_tk, DO_tk, SPOT_tk, PLACE_tk, HERE_tk, THERE_tk,

	//tokens
	ID_tk, NUM_tk, OP_tk, EOF_tk
} token_type;

typedef struct {
	token_type tok_type;
	char label[9];
	int line_number;
}token;

#endif