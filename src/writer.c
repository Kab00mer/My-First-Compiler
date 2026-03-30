#include "writer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Writer* writer_create(struct NodeReturn* root) {
	struct Writer* w = malloc(sizeof(struct Writer));
	w->root = root;
	return w;
}

void writer_turn_tree_to_assembly(struct Writer* w) {
	char* assembly = malloc(10000);
	concat(assembly, "global _start\n_start:\n");
	concat(assembly, "    mov rax, 60\n");
	concat(assembly, "    mov rdi, ");

	char buffer[5];
	sprintf(buffer, "%d", w->root->returnValue->value);
	concat(assembly, buffer);

	concat(assembly, "\n    syscall");
	assembly[strlen(assembly)] = '\0';

	w->assembly = assembly;
}

void concat(char* s1, char* s2) {
	s1 += strlen(s1);
	while (*s1 = *s2) {
		++s1;
		++s2;
	}
}
