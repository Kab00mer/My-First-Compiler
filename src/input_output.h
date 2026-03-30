#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stddef.h>

struct InputOutput {
	char* inputPath;
	size_t inputSize;

	char* contents;
	size_t contentsSize;

	char* outputPath;
	size_t outputSize;
};

struct InputOutput* input_output_create(char* inputPath);
void input_output_read_input_file(struct InputOutput* io);
void input_output_create_output_path(struct InputOutput* io);
void input_output_write_assembly(struct InputOutput* io, char* assembly);

#endif
