#include "parser.h"
#include <stdlib.h>

struct Parser* parser_create(struct Token* tokens, size_t tokenCount) {
	struct Parser* p = malloc(sizeof(struct Parser));
	
	p->tokens = tokens;
	p->tokenCount = tokenCount;

	return p;
}

void parser_turn_tokens_to_tree(struct Parser* p) {
	for (size_t i = 0; i < p->tokenCount; ++i) {
		if (p->tokens[i].type == TOKEN_RETURN 
				&& p->tokens[i + 1].type == TOKEN_INT
				&& p->tokens[i + 2].type == TOKEN_SEMICOLON) {

			struct NodeExpression* expression = malloc(sizeof(struct NodeExpression));
			expression->value = p->tokens[i + 1].value;

			struct NodeReturn* exit = malloc(sizeof(struct NodeReturn));
			exit->returnValue = expression;

			p->root = exit;

			i += 2;
		}
	}
}
