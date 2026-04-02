#include <stdio.h>

#include "input_output.h"
#include "tokenizer.h"
#include "parser.h"
#include "writer.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Wrong input. The Correct Input is...\n./mygcc <file.c>\n");
		return 1;
	}

	//reading c file
	struct InputOutput* io = input_output_create(argv[1]);
	input_output_read_input_file(io);

	//tokenizing
	struct Tokenizer* t = tokenizer_create(io->contents, io->contentsSize);
	tokenizer_turn_text_to_tokens(t);
	tokenizer_print_tokens(t);

	//parsing
	struct Parser* p = parser_create(t->tokens, t->tokenCount);
	parser_turn_tokens_to_tree(p);
	parser_print_tree(p);
	
	//writing assembly
	struct Writer* w = writer_create(p->root);
	writer_turn_tree_to_assembly(w);
	writer_print_assembly(w);

	//outputing assembly file
	input_output_create_output_path(io);
	input_output_write_assembly(io, w->assembly);

	printf("Compiling complete; Result is in %s\n", io->outputPath);

	return 0;
}
