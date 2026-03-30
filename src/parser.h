#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"

struct NodeExpression {
	int value;	
};

struct NodeReturn {
	struct NodeExpression* returnValue;	
};

struct Parser {
	struct Token* tokens;
	size_t tokenCount;
	struct NodeReturn root;
};

struct Parser* parser_create(struct Token* tokens, size_t tokenCount);
void parser_turn_tokens_to_tree(struct Parser* p);

#endif
