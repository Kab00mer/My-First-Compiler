#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>

enum TokenType {
	TOKEN_RETURN,
	TOKEN_INT,
	TOKEN_SEMICOLON
};

struct Token {
	enum TokenType type;
	int value;
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
void tokenizer_append_token(struct Tokenizer* t, struct Token token);

#endif
