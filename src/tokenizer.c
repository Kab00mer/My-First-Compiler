#include "tokenizer.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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
			int intBuilder = ch - '0';
			size_t j = i + 1;
			bool exit = false;
			while (j < t->textSize && !exit) {
				char ch2 = *(t->text + j);
				if (ch2 >= '0' && ch2 <= '9') {
					intBuilder *= 10;
					intBuilder += ch2 - '0';
					++j;
				} else {
					exit = true;
				}
			}
			i = j - 1;
			struct Token token = { TOKEN_INT, intBuilder };
			tokenizer_append_token(t, token);

		} else if (ch == ';') {
			struct Token token = { TOKEN_SEMICOLON, 0 };
			tokenizer_append_token(t, token);
		} else if (ch != ' ') {
			size_t builderCapacity = 10;
			size_t builderSize = 0;
			char* strBuilder = malloc(builderCapacity);
			
			size_t j = i;
			bool exit = false;
			while (j < t->textSize && !exit) {
				char ch2 = *(t->text + j);
				if (ch2 != ' ') {
					if (builderCapacity <= builderSize + 1) {
						builderCapacity += 10;
						strBuilder = realloc(strBuilder, builderCapacity);
					}
					*(strBuilder + j - i) = ch2;
					++builderSize;
					++j;

				} else {
					exit = true;
				}
			}
			strBuilder[builderSize] = '\0';

			if (strcmp(strBuilder, "return") == 0) {
				struct Token token = { TOKEN_RETURN, 0 };
				tokenizer_append_token(t, token);
			}
			free(strBuilder);
		}
	}
}

void tokenizer_append_token(struct Tokenizer* t, struct Token token) {
	if (t->tokenCapacity <= t->tokenCount + 1) {
		t->tokenCapacity += 10;
		t->tokens = realloc(t->tokens, t->tokenCapacity * sizeof(struct Token));
	}
	t->tokens[t->tokenCount] = token;
	++t->tokenCount;
}
