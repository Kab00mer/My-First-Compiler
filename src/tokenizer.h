#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>

enum TokenType {
	TOKEN_RETURN,
	TOKEN_INT,
	TOKEN_SEMICOLON,
	
	TOKEN_EQUALS,
	TOKEN_TYPE_INT,
	TOKEN_IDENTIFIER
};

struct Token {
	enum TokenType type;
	char* value;
};

struct Tokenizer {
	char* text;
	size_t textSize;

	struct Token* tokens;
	size_t tokenCount;
	size_t tokenCapacity;
};

struct Tokenizer* tokenizer_create(char* text, size_t size);	
void tokenizer_turn_text_to_tokens(struct Tokenizer* t);
char* build_str(char* start);
void tokenizer_append_token(struct Tokenizer* t, struct Token token);
void tokenizer_print_tokens(struct Tokenizer* t);

#endif
