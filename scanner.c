#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"
#include "character_type.h"
#include "testTree.h"
#include "scanner.h"

const int num_keywords = 13;
const int length = 8;
int line_number = 1;
character next_char;

typedef enum {
	ERROR = -1,
	s1 = 0, s2
} state;

/*
	Rows:
	0 = initial state, 1 = ID, 2 = digit, 3 = single_op, 4 = double_op, 5 = :<, 6 = :=, 7 = :&

	Columns:
	EOF, WS, Uppercase letter, Lowercaser letter, number, Single_op, <, <, -, *

	Final States:
	1001 = EOFtk, 1002 = IDtk/KWtk, 1003 = NUMtk, 1004-1008 = OPtk, 2000 = comment
*/
int fsa_table[7][10] = {
	1001, 0, 1, 1, 2, 3, 4, -1, -1, 2000,
	1002, 1002, 1, 1, 1, 1002, 1002, 1002, 1002, 2000,
	1003, 1003, 1003, 1003, 2, 1003, 1003, 1003, 1003, 2000,
	1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 2000,
	-1, -1, -1, -1, -1, -1, 5, 5, 6, 2000,
	1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 2000,
	1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 2000
};

char* keywords[] = {
	"Again", "If", "Assign", "Move", "Show", "Flip", "Name", "Home", "Do", "Spot", "Place", "Here", "There"
};

void lookahead_char(FILE* file) {
	next_char = filter(file);
}

token scanner(FILE* file) {
	return fsaTableResult(file);
}

token fsaTableResult(FILE* file) {
	int state = 0;
	int next_state;
	token new_token;
	int m = 0;
	char str[9];
	memset(str, 0, sizeof(str));

	while (state < 1000) {
		next_state = fsa_table[state][next_char.col];

		if (next_state < 0) {
			printf("Scanner ERROR: Tokens cannot begin with '%c' on line %d", next_char.value, next_char.line_number);
			exit(-1);
		}

		switch (next_state) {
			case 1001:
				new_token.tok_type = EOF_tk;
				return new_token;
			case 1002:
				//keyword check
				if (!strcmp(new_token.label, "Again")) {
					new_token.tok_type = AGAIN_tk;

					return new_token;
				}
				else if (!strcmp(new_token.label, "If")) {
					new_token.tok_type = IF_tk;

					return new_token;
				}
				else if (!strcmp(new_token.label, "Assign")) {
					new_token.tok_type = ASSIGN_tk;

					return new_token;
				}
				else if (!strcmp(new_token.label, "Move")) {
					new_token.tok_type = MOVE_tk;

					return new_token;
				}
				else if (!strcmp(new_token.label, "Show")) {
					new_token.tok_type = SHOW_tk;

					return new_token;
				}
				else if (!strcmp(new_token.label, "Flip")) {
					new_token.tok_type = FLIP_tk;

					return new_token;
				}
				else if (!strcmp(new_token.label, "Name")) {
					new_token.tok_type = NAME_tk;

					return new_token;
				}
				else if (!strcmp(new_token.label, "Home")) {
					new_token.tok_type = HOME_tk;

					return new_token;
				}
				else if (!strcmp(new_token.label, "Do")) {
					new_token.tok_type = DO_tk;

					return new_token;
				}
				else if (!strcmp(new_token.label, "Spot")) {
					new_token.tok_type = SPOT_tk;

					return new_token;
				}
				else if (!strcmp(new_token.label, "Place")) {
					new_token.tok_type = PLACE_tk;

					return new_token;
				}
				else if (!strcmp(new_token.label, "Here")) {
					new_token.tok_type = HERE_tk;

					return new_token;
				}
				else if (!strcmp(new_token.label, "There")) {
					new_token.tok_type = THERE_tk;

					return new_token;
				}
				else {
					new_token.tok_type = ID_tk;
					return new_token;
				}
				
			case 1003:
				new_token.tok_type = NUM_tk;
				return new_token;
			case 1004:
				new_token.tok_type = OP_tk;
				return new_token;
			case 1005:
				new_token.tok_type = OP_tk;
				return new_token;
			case 1006:
				new_token.tok_type = OP_tk;
				return new_token;
			case 1007:
				new_token.tok_type = OP_tk;
				return new_token;
			case 2000:
				//comments
				return new_token;

			default:
				if (next_char.col != WS) {
					str[m] = next_char.value;
					m++;
					/*str[m] = '\0';
					m++;*/
					strcpy(new_token.label, str);
				}

				state = next_state;
				next_char = filter(file);

				if (strlen(str) == length) {
					strcpy(new_token.label, str);
					new_token.line_number = next_char.line_number;

					return new_token;
				}

		}

		/*if (next_state > 1000) {
			new_token.tok_type = state + num_keywords;
			printf("token.toktype = %d, token.label = %s\n", new_token.tok_type, new_token.label);
			strcpy(new_token.label, str);
			new_token.line_number = next_char.line_number;

			if (state == 1) {
				int i;
				for (i = 0; i < num_keywords; i++) {
					if (strcmp(keywords[i], new_token.label) == 0) {
						printf("token.toktype = %d, token.label = %s\n", new_token.tok_type, new_token.label);
						new_token.tok_type = i;
					}
				}
			}
			printf("token.toktype = %d, token.label = %s\n", new_token.tok_type, new_token.label);
			return new_token;
		}

		else {
			if (next_char.col != WS) {
				str[strlen(str)] = next_char.value;
				str[strlen(str) + 1] = '\0';
			}

			state = next_state;
			next_char = filter(file);



			printf("state = %d, next_char = %d, new_token.label = %s\n", state, next_char.value, new_token.label);
			if (strlen(str) == length) {
				new_token.tok_type = state + num_keywords;
				strcpy(new_token.label, str);
				new_token.line_number = next_char.line_number;

				return new_token;
			}
		} */
	}

	return new_token;
}

character filter(FILE* file) {
	character input;
	char current_char = fgetc(file);
	int col_num = getColNum(current_char);

	while (col_num == COMMENT) {
		do {
			current_char = fgetc(file);
			if (current_char == '\n') {
				line_number++;
			}
		} while (current_char != '*');
		current_char = fgetc(file);
		col_num = getColNum(current_char);
	}

	if (col_num >= ENDOFFILE && col_num <= ARRMINUS) {
		input.value = current_char;
		input.col = col_num;
		input.line_number = line_number;

		if (current_char == '\n') {
			line_number++;
		}

		return input;
	}
	else {
		printf("Scanner ERROR: Invalid character %c at line %d\n", current_char, line_number);
		exit(col_num);
	}
}

int getColNum(char x) {
	if (x == EOF) 
		return ENDOFFILE;
	if (isspace(x))
		return WS;
	if (isupper(x)) 
		return UPPER;
	if (islower(x)) 
		return LOWER;
	if (isdigit(x)) 
		return NUM;
	if (x == '&' || x == '+' || x == '/' || x == '%' || x == '.' || x == '{' || x == '}')
		return SINGLEOP;
	if (x == '<')
		return ARR;
	if (x == '-')
		return ARRMINUS;
	if (x == '*')
		return COMMENT;
	printf("Scanner ERROR: %c is not a valid character\n", x);
	exit(-1);
}
//void printToken(token tok) {
//	if (tok.tok_type == EOF_tk) {
//		printf("%s\n", token)
//	}
//}

