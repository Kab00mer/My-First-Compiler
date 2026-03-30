#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenizer.h"
#include "parser.h"
//#include "writer.h"

int main(int argc, char** argv) {
	//making sure we have the right amount of argc
	if (argc != 2) {
		fprintf(stderr, "Wrong input. The Correct Input is...\n./mygcc <file.c>\n");
		return 1;
	}

	//reading chars from file
	size_t capacity = 2;
	char* buffer = malloc(capacity);
	FILE* inputFilePtr = fopen(*(argv + 1), "r");
	size_t size = 0;
	int ch;
	while ((ch = fgetc(inputFilePtr)) != EOF) {
		if (size + 2 > capacity) {
			capacity += 20;		
			buffer = realloc(buffer, capacity);
		}
		buffer[size] = ch;
		++size;
	}
	buffer = realloc(buffer, size);
	buffer[size] = '\0';
	fclose(inputFilePtr);

	for (size_t i = 0; i < size; ++i) {
		printf("%c", buffer[i]);
	}

	struct Tokenizer* t = tokenizer_create(buffer, size);
	tokenizer_turn_text_to_tokens(t);

	struct Parser* p = parser_create(t->tokens, t->tokenCount);
	parser_turn_tokens_to_tree(p);
	

	/*
	//getting the name of the obj file
	char* c = argv[1];
	int i = 0;
	while (c[i]) ++i;

	char objFileName[i + 3];
	for (int j = 0; j < i; ++j) {
		objFileName[j] = c[j];
	}
	objFileName[i - 1] = 'a';
	objFileName[i] = 's';
	objFileName[i + 1] = 'm';
	objFileName[i + 2] = '\0';

	//outputting assembly
	FILE* outputFilePtr = fopen(objFileName, "w");
	fclose(outputFilePtr);
	*/

	return 0;
}
