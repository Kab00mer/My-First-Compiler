#include "tokenizer.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct Tokenizer* tokenizer_create(char* text, size_t size) {
	struct Tokenizer* t = malloc(sizeof(struct Tokenizer));

	t->text = text;
	t->textSize = size;
	t->tokenCapacity = 10;
	t->tokenCount = 0;
	t->tokens = malloc(t->tokenCapacity * sizeof(struct Token));

	return t;
}

void tokenizer_turn_text_to_tokens(struct Tokenizer* t) {
	for (size_t i = 0; i < t->textSize; ++i) {
		char ch = *(t->text + i);
		if (ch >= '0' && ch <= '9') {
			char* integer = build_str(t->text + i);
			struct Token token = { TOKEN_INT, integer };
			tokenizer_append_token(t, token);
			i += strlen(integer) - 1;

		} else if (ch == ';') {
			struct Token token = { TOKEN_SEMICOLON, "" };
			tokenizer_append_token(t, token);

		} else if (ch == '=') {
			struct Token token = { TOKEN_EQUALS, "" };
			tokenizer_append_token(t, token);

		} else if (ch != ' ' && ch != '\n') {
			char* str = build_str(t->text + i);

			if (strcmp(str, "return") == 0) {
				struct Token token = { TOKEN_RETURN, "" };
				tokenizer_append_token(t, token);
				i += strlen(str) - 1;
				free(str);

			} else if (strcmp(str, "int") == 0) {
				struct Token token = { TOKEN_TYPE_INT, "" };
				tokenizer_append_token(t, token);
				i += strlen(str) - 1;
				free(str);

			} else {
				struct Token token = { TOKEN_IDENTIFIER, str };
				tokenizer_append_token(t, token);
				i += strlen(str) - 1;
			}
		}
	}
}

char* build_str(char* start) {
	size_t builderCapacity = 10;
	size_t builderSize = 0;
	char* strBuilder = malloc(builderCapacity);
			
	size_t j = 0;
	bool exit = false;
	char ch2;
	while (!exit) {
		ch2 = *(start + j);
		if (ch2 != ' ' && ch2 != '=' && ch2 != ';' && ch2 != '\0') {
			if (builderCapacity <= builderSize + 1) {
				builderCapacity += 10;
				strBuilder = realloc(strBuilder, builderCapacity);
			}
			*(strBuilder + j) = ch2;
			++builderSize;
			++j;

		} else {
			exit = true;
		}
	}
	strBuilder[builderSize] = '\0';

	return strBuilder;
}

void tokenizer_append_token(struct Tokenizer* t, struct Token token) {
	if (t->tokenCapacity <= t->tokenCount + 1) {
		t->tokenCapacity += 10;
		t->tokens = realloc(t->tokens, t->tokenCapacity * sizeof(struct Token));
	}
	t->tokens[t->tokenCount] = token;
	++t->tokenCount;
}

void tokenizer_print_tokens(struct Tokenizer* t) {
	printf("Tokens that are currently in the tokenizer:\n");

	for (size_t i = 0; i < t->tokenCount; ++i) {
		switch(t->tokens[i].type) {
			case TOKEN_RETURN:
				printf("TOKEN_RETURN\n");
				break;
			case TOKEN_INT:
				printf("TOKEN_INT\n");
				break;
			case TOKEN_SEMICOLON:
				printf("TOKEN_SEMICOLON\n\n");
				break;
			case TOKEN_EQUALS:
				printf("TOKEN_EQUALS\n");
				break;
			case TOKEN_TYPE_INT:
				printf("TOKEN_TYPE_INT\n");
				break;
			case TOKEN_IDENTIFIER:
				printf("TOKEN_IDENTIFIER\n");
		}
	}
}




