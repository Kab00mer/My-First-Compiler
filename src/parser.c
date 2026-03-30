#include "parser.h"
#include <stdlib.h>

struct Parser* parser_create(struct Token* tokens, size_t tokenCount) {
	struct Parser* p = malloc(sizeof(struct Parser));
	
	p->tokens = tokens;
	p->tokenCount = tokenCount;

	return p;
}

void parser_turn_tokens_to_tree(struct Parser* p) {
		
}
