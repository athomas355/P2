#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "parser.h"
#include "testTree.h"

int main(int argc, char* argv[]) {
	
	//too many arguments
	if (argc > 2) {
		printf("ERROR: there were too many arguments only expected one or no arguments\n");
		exit(-1);
	}

	FILE* file_ptr = NULL;
	char* file_name = NULL;

	if (argc == 2) {
		
		file_name = (char*)malloc(sizeof(argv[1]));
		strcpy(file_name, argv[1]);

		file_ptr = fopen(file_name, "r");

		if (!file_ptr) {
			printf("ERROR: The file %s could not be opened.\n", file_name);
			exit(-1);
		}
	}
	else {
		file_ptr = stdin;
	}

	node* root = parser(file_ptr);
	//printf(" {%s, %s, %d}", token_names[root->token_1.tok_type], root->token_1.label, root->token_1.line_number);
	traversePreorder(root, 0);

	fclose(file_ptr);
	free(file_name);
	return 0;
}