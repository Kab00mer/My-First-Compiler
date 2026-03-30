#ifndef WRITER_H
#define WRITER_H

#include "parser.h"

struct Writer {
	struct NodeReturn* root;	
	char* assembly;
};

struct Writer* writer_create(struct NodeReturn* root);
void writer_turn_tree_to_assembly(struct Writer* w);
void concat(char* s1, char* s2);

#endif
