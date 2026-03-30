#include "input_output.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct InputOutput* input_output_create(char* inputPath) {
	struct InputOutput* io = malloc(sizeof(struct InputOutput));	

	io->inputPath = inputPath;
	io->inputSize = strlen(inputPath);
	io->contentsSize = 0;
	io->outputSize = 0;

	return io;
}

void input_output_read_input_file(struct InputOutput* io) {
	size_t capacity = 2;
	io->contents = malloc(capacity);
	FILE* inputFilePtr = fopen(io->inputPath, "r");

	int ch;
	while ((ch = fgetc(inputFilePtr)) != EOF) {
		if (io->contentsSize + 2 > capacity) {
			capacity += 20;		
			io->contents = realloc(io->contents, capacity);
		}
		io->contents[io->contentsSize] = ch;
		io->contentsSize += 1;
	}

	io->contents = realloc(io->contents, io->contentsSize + 1);
	io->contents[io->contentsSize] = '\0';
	fclose(inputFilePtr);
}

void input_output_create_output_path(struct InputOutput* io) {
	io->outputSize = io->inputSize + 3;
	io->outputPath = malloc(io->outputSize);

	size_t i = 0;
	while (i < io->inputSize) {
		io->outputPath[i] = io->inputPath[i];
		++i;
	}

	io->outputPath[i - 1] = 'a';
	io->outputPath[i] = 's';
	io->outputPath[i + 1] = 'm';
	io->outputPath[i + 2] = '\0';
}

void input_output_write_assembly(struct InputOutput* io, char* assembly) {
	FILE* outputFilePtr = fopen(io->outputPath, "w");
	
	fprintf(outputFilePtr, "%s", assembly);

	fclose(outputFilePtr);
}
