#include "writer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

struct Writer* writer_create(struct NodeProgram* root) {
	struct Writer* w = malloc(sizeof(struct Writer));

	w->root = root;

	w->assemblySize = 0;
	w->assemblyCapacity = 100;
	w->assembly = malloc(w->assemblyCapacity);

	w->variableCount = 0;
	w->variableCapacity = 5;
	w->variables = malloc(sizeof(char*) * w->variableCapacity);

	return w;
}

void writer_turn_tree_to_assembly(struct Writer* w) {
	writer_append_to_assembly(w, "global _start\n_start:\n");

	bool codeReturned = false;

	for (size_t i = 0; i < w->root->statementCount; ++i) {
		struct NodeStatement* statement = w->root->statements[i];
		switch (statement->type) {
			case STATEMENT_RETURN :
				writer_return(w, statement->expressions[0]);
				codeReturned = true;
				break;
			case STATEMENT_INITIALIZE :
				writer_initialize_variable(w, statement->expressions[0], statement->expressions[1]);
				break;
		}
	}
	w->assembly[w->assemblySize] = '\0';
	
	//by defualt return 0 at the end of code
	if (!codeReturned) {
		writer_return(w, "0");
	}
}

void writer_append_to_assembly(struct Writer* w, char* str) {
	if (strlen(str) + w->assemblySize + 1 >= w->assemblyCapacity) {
		w->assemblyCapacity += strlen(str);
		w->assembly = realloc(w->assembly, w->assemblyCapacity);
	}

	char ch;
	while (ch = *str) {
		w->assembly[w->assemblySize] = ch;
		w->assemblySize += 1;
		++str;
	}
}

void writer_return(struct Writer* w, char* integer) {
	writer_append_to_assembly(w, "\n    mov rax, 60\n    mov rdi, ");

	(integer[0] >= '0' && integer[0] <= '9') ?	writer_append_to_assembly(w, integer)
		: writer_access_mapped_value(w, integer);

	writer_append_to_assembly(w, "\n    syscall\n");
}

void writer_initialize_variable(struct Writer* w, char* expr1, char* expr2) {
	writer_append_to_assembly(w, "    mov rax, ");

	(expr2[0] >= '0' && expr2[0] <= '9') ?	writer_append_to_assembly(w, expr2)
		: writer_access_mapped_value(w, expr2);
	
	writer_append_to_assembly(w, "\n    push rax\n");

	if (w->variableCount + 1 >= w->variableCapacity) {
		w->variableCapacity += 5;
		w->variables = realloc(w->variables, sizeof(char*) * w->variableCapacity);
	}

	w->variables[w->variableCount] = expr1;
	w->variableCount += 1;
}

void writer_access_mapped_value(struct Writer* w, char* varName) {
	bool found = false;
	size_t i = 0;
	while (!found && i < w->variableCount) {
		strcmp(varName, w->variables[i]) == 0 ? found = true : ++i;
	}

	if (found) {
		writer_append_to_assembly(w, "[rsp + ");
		char* offest;
		sprintf(offest, "%d", (int)(w->variableCount - (i + 1)) * 8);
		writer_append_to_assembly(w, offest);
		writer_append_to_assembly(w, "]");

	} else {
		fprintf(stderr, "Writing Error: There is no variable named \"%s\" in memory", varName);
	}
}

void writer_print_assembly(struct Writer* w) {
	printf("Assembly that is currently in the writer:\n%s\n", w->assembly);
}
