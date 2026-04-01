#ifndef WRITER_H
#define WRITER_H

#include "parser.h"

struct Writer {
	struct NodeReturn* root;	
	char* assembly;
};

struct Writer* writer_create(struct NodeReturn* root);

void writer_turn_tree_to_assembly(struct Writer* w);
void writer_initialize_variable(struct Writer* w);
void writer_add_to_assembly(struct Writer* w, char* str);

void writer_print_assembly(struct Writer* w);

#endif
