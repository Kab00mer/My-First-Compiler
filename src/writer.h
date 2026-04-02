#ifndef WRITER_H
#define WRITER_H

#include "parser.h"

struct Writer {
	struct NodeProgram* root;	

	size_t assemblySize;
	size_t assemblyCapacity;
	char* assembly;

	size_t variableCount;
	size_t variableCapacity;
	char** variables;
};

struct Writer* writer_create(struct NodeProgram* root);
void writer_turn_tree_to_assembly(struct Writer* w);
void writer_append_to_assembly(struct Writer* w, char* str);

void writer_return(struct Writer* w, char* integer);
void writer_initialize_variable(struct Writer* w, char* expr1, char* expr2s);
void writer_access_mapped_value(struct Writer* w, char* varName);

void writer_print_assembly(struct Writer* w);

#endif
