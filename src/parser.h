#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"

enum StatementType {
	STATEMENT_RETURN,
	STATEMENT_INITIALIZE,
	STATEMENT_ASSIGNMENT
};

struct NodeStatement {
	enum StatementType type;
	size_t expressionCount;
	char* expressions[];
};

struct NodeProgram {
	size_t statementCount;
	size_t statementCapacity;
	struct NodeStatement** statements;
};

struct Parser {
	size_t tokenCount;
	struct Token* tokens;
	struct NodeProgram* root;
};

struct Parser* parser_create(struct Token* tokens, size_t tokenCount);
struct NodeStatement* node_statement_create(enum StatementType type, size_t expressionCount);

void parser_turn_tokens_to_tree(struct Parser* p);
void parser_append_statement(struct Parser* p, struct NodeStatement* s);

void parser_print_tree(struct Parser* p);

#endif
