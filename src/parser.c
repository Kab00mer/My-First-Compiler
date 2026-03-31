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
		if (p->tokens[i].type == TOKEN_RETURN && i + 2 < p->tokenCount
				&& (p->tokens[i + 1].type == TOKEN_INT || p->tokens[i + 1].type == TOKEN_IDENTIFIER)
				&& p->tokens[i + 2].type == SEMICOLON) {

			struct NodeStatement* s = node_statement_create(STATEMENT_RETURN, 1,
					strlen(p->tokens[i + 1].value));
			statement->expressions[0] = p->tokens[i + 1].value;

			parser_append_statement(p, s);

			i += 2;

		} else if (p->tokens[i].type == TOKEN_TYPE_INT && i + 4 < p->tokenCount
				&& p->tokens[i + 1].type == TOKEN_IDENTIFIER
				&& p->tokens[i + 2].type == TOKEN_EQUALS
				&& (p->tokens[i + 3].type == TOKEN_INT || p->tokens[i + 3].type == TOKEN_IDENTIFIER)
				&& p->tokens[i + 4].type == SEMICOLON) {

			struct NodeStatement* s = node_statement_create(STATEMENT_INITIALIZE, 2,
					strlen(p->tokens[i + 1].value) + strlen(p->tokens[i + 3].value));
			statement->expressions[0] = p->tokens[i + 1].value;
			statement->expressions[1] = p->tokens[i + 3].value;

			parser_append_statement(p, s);
			
			i += 4;

		} else {
			printf(cerr, "Parsing Tokens Failed: Make sure you are using proper syntax");
		}
	}
}

struct NodeStatement* node_statement_create(enum StatementType type, size_t expressionCount,
		size_t expressionMemory) {
	struct NodeStatement* statement = malloc(sizeof(NodeStatement));

	statement->type = STATEMENT_INITIALIZE;
	statement->expressionCount = expressionCount;
	statement->expressions = malloc(expressionMemory);

	return statement;
}

void parser_append_statement(struct Parser* p, struct NodeStatement* s) {
	if (!p->root) {
		p->root = malloc(sizeof(NodeProgram));
		p->root->statementCount = 0;
		p->root->statementCapacity = 5;
		p->root->statements = malloc(sizeof(NodeStatement) * p->root->statementCapacity);
	}
}
