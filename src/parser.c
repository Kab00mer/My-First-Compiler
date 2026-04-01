#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

struct Parser* parser_create(struct Token* tokens, size_t tokenCount) {
	struct Parser* p = malloc(sizeof(struct Parser));
	
	p->tokens = tokens;
	p->tokenCount = tokenCount;
	p->root = NULL;

	return p;
}

struct NodeStatement* node_statement_create(enum StatementType type, size_t expressionCount) {
	struct NodeStatement* statement = malloc(sizeof(struct NodeStatement) 
			+ sizeof(char*) * expressionCount);

	statement->type = type; 
	statement->expressionCount = expressionCount;

	return statement;
}

void parser_turn_tokens_to_tree(struct Parser* p) {
	for (size_t i = 0; i < p->tokenCount; ++i) {
		if (p->tokens[i].type == TOKEN_RETURN && i + 2 < p->tokenCount
				&& (p->tokens[i + 1].type == TOKEN_INT || p->tokens[i + 1].type == TOKEN_IDENTIFIER)
				&& p->tokens[i + 2].type == TOKEN_SEMICOLON) {

			struct NodeStatement* s = node_statement_create(STATEMENT_RETURN, 1);
			s->expressions[0] = p->tokens[i + 1].value;

			parser_append_statement(p, s);

			i += 2;
		} else if (p->tokens[i].type == TOKEN_TYPE_INT && i + 4 < p->tokenCount
				&& p->tokens[i + 1].type == TOKEN_IDENTIFIER
				&& p->tokens[i + 2].type == TOKEN_EQUALS
				&& (p->tokens[i + 3].type == TOKEN_INT || p->tokens[i + 3].type == TOKEN_IDENTIFIER)
				&& p->tokens[i + 4].type == TOKEN_SEMICOLON) {

			struct NodeStatement* s = node_statement_create(STATEMENT_INITIALIZE, 2);
			s->expressions[0] = p->tokens[i + 1].value;
			s->expressions[1] = p->tokens[i + 3].value;

			parser_append_statement(p, s);
			
			i += 4;

		} else {
			fprintf(stderr, "Parsing Tokens Failed: Make sure you are using proper syntax");
		}
	}
}

void parser_append_statement(struct Parser* p, struct NodeStatement* s) {
	if (!p->root) {
		p->root = malloc(sizeof(struct NodeProgram));
		p->root->statementCount = 0;
		p->root->statementCapacity = 5;
		p->root->statements = malloc(sizeof(struct NodeStatement) * p->root->statementCapacity);
	}

	if (p->root->statementCount + 1 > p->root->statementCapacity) {
		p->root->statementCapacity += 5;
		p->root->statements = realloc(p->root->statements, 
				sizeof(struct NodeStatement) * p->root->statementCapacity);
	}

	p->root->statements[p->root->statementCount] = s;
	p->root->statementCount += 1;
}

void parser_print_tree(struct Parser* p) {
	printf("Nodes that are currently in the parser:\nNodePogram:\n");
	for (size_t i = 0; i < p->root->statementCount; ++i) {
		switch (p->root->statements[i]->type) {
			case STATEMENT_RETURN :
				printf("NodeStatement->Return->(%s)\n", p->root->statements[i]->expressions[0]);
				break;
			case STATEMENT_INITIALIZE :
				printf("NodeStatement->Initialize->(");
				printf("%s and ", p->root->statements[i]->expressions[0]);
				printf("%s)\n", p->root->statements[i]->expressions[1]);
		}
	}
	printf("\n");
}
