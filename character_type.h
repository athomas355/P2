#ifndef CHARACTER_TYPE_H
#define CHARACTER_TYPE_H

typedef enum {
	ENDOFFILE, WS, UPPER, LOWER, NUM, SINGLEOP, ARR, ARR2, ARRMINUS, COMMENT
} character_type;

typedef struct {
	char value;
	int col;
	int line_number;
} character;

#endif