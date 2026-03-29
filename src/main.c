#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TokenType {
	_return,
	_int,
	_semicolon
};

struct Token {
	enum TokenType type;
	int value;
};

struct Token* tokenize(char buffer[]) {
	struct Token* tokens = malloc(10);
	size_t token_capacity = 9;
	char* builder = malloc(10);
	size_t capacity = 9;
	
	size_t size = 0;
	char ch = *buffer;
	while (ch) {
		if (ch != ' ') {
			if (size + 1 >= capacity) {
				capacity *= 2;
				builder = realloc(capacity);
			}
			*builder = ch;
			++builder;
		} else {
			if (strcmp(builder, "return") == 0) {
				
			}

			capacity = 9;
			builder = ralloc(capacity + 1);
		}
		++buffer;
		ch = *buffer;
	}

	return tokens;
}



int main(int argc, char* argv[]) {
	//making sure we have a file to compile
	if (argc != 2) {
		fprintf(stderr, "Wrong input. The Correct Input is...\n./mygcc <file.c>\n");
		return 1;
	}

	//reading chars from file
	size_t capacity = 2;
	char* buffer = malloc(capacity);

	FILE* inputFilePtr = fopen(argv[1], "r");
	size_t size = 0;
	int ch;
	while ((ch = fgetc(inputFilePtr)) != EOF) {
		if (size + 2 > capacity) {
			capacity *= 2;		
			buffer = realloc(buffer, capacity);
		}
		buffer[size] = ch;
		++size;
	}
	buffer[size] = '\0';
	fclose(inputFilePtr);

	//turn the string into tokens
	struct Token* tokens = tokenize(buffer);
	free(buffer);	

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

	return 0;
}
