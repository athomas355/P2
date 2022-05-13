#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "node.h"
#include "testTree.h"


int level = 0;

char *token_names[] = {
    
    //keywords
    "AGAIN_tk ", "IF_tk", "ASSIGN_tk", "MOVE_tk", "SHOW_tk", "FLIP_tk", 
    "NAME_tk", "HOME_tk", "DO_tk", "SPOT_tk", "PLACE_tk", "HERE_tk", "THERE_tk",

    //tokens
    "ID_tk", "NUM_tk", "OP_tk", "EOF_tk"
};

static char *label_names[] = {
    //non-terminals
    "S", "R", "E", "A", "B", "C", "D",
    "F", "G", "T", "V", "H", "J", "K",
    "L", "W", "Z",

    //terminals
    "NAME", "IDENTIFIER", "SPOT", "PLACE", "HOME",
    "SHOW," "PERIOD", "LBRACK", "RBRACK", "IF",
    "DO", "AGAIN", "HERE", "NUMBER", "THERE", "ARR2", "ARRMINUS",
    "PLUS", "PERCENT", "AND", "SLASH", "ASSIGN",
    "MOVE", "FLIP"
};

void traversePreorder(node *node, int level) {
    if (node != NULL) {
        goToNode(node, level);
        traversePreorder(node->non_terminal_1, level + 1);
        traversePreorder(node->non_terminal_2, level + 1);
        traversePreorder(node->non_terminal_3, level + 1);
    }
}

void goToNode(node *node, int level) {
    printf("%*s%s\n", level * 2, "", label_names[node->label]);
    
    if (node->token_1.tok_type != NULL_tk) {
        printf(" %*s{%s, %s}\n", level * 2, "", token_names[node->token_1.tok_type], node->token_1.label);
    }
    if (node->token_2.tok_type != NULL_tk) {
        printf(" %*s{%s, %s}\n", level * 2, "", token_names[node->token_2.tok_type], node->token_2.label);
    }
    if (node->token_3.tok_type != NULL_tk) {
        printf(" %*s{%s, %s}\n", level * 2, "", token_names[node->token_3.tok_type], node->token_3.label);
    }
    if (node->token_4.tok_type != NULL_tk) {
        printf(" %*s{%s, %s}\n", level * 2, "", token_names[node->token_4.tok_type], node->token_4.label);
    }
    
    printf("\n");
}