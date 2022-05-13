#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include "token.h"
#include "character_type.h"

void lookahead_char(FILE*);
token scanner(FILE*);
token fsaTableResult(FILE*);
character filter(FILE*);
int getColNum(char);
void printToken(token tok);

#endif