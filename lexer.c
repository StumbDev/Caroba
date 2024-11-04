#include "lexer.h"

Lexer* lexer_create(const char* source) {
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->source = strdup(source);
    lexer->length = strlen(source);
    lexer->position = 0;
    lexer->line = 1;
    lexer->column = 1;
    return lexer;
}

static char lexer_peek(Lexer* lexer) {
    if (lexer->position >= lexer->length) return '\0';
    return lexer->source[lexer->position];
}

static char lexer_advance(Lexer* lexer) {
    char current = lexer_peek(lexer);
    lexer->position++;
    if (current == '\n') {
        lexer->line++;
        lexer->column = 1;
    } else {
        lexer->column++;
    }
    return current;
}

static Token* create_token(TokenType type, const char* value, int line, int column) {
    Token* token = malloc(sizeof(Token));
    token->type = type;
    token->value = strdup(value);
    token->line = line;
    token->column = column;
    return token;
}

Token* lexer_next_token(Lexer* lexer) {
    while (lexer_peek(lexer) != '\0') {
        char c = lexer_peek(lexer);
        
        // Skip whitespace
        if (isspace(c)) {
            lexer_advance(lexer);
            continue;
        }

        // Handle @ symbol
        if (c == '@') {
            lexer_advance(lexer);
            return create_token(TOKEN_AT, "@", lexer->line, lexer->column - 1);
        }

        // Handle identifiers
        if (isalpha(c) || c == '_') {
            char buffer[256] = {0};
            int i = 0;
            
            while (isalnum(lexer_peek(lexer)) || lexer_peek(lexer) == '_') {
                buffer[i++] = lexer_advance(lexer);
            }
            
            // Check if it's a keyword
            if (strcmp(buffer, "func") == 0 || 
                strcmp(buffer, "var") == 0 || 
                strcmp(buffer, "for") == 0 || 
                strcmp(buffer, "in") == 0) {
                return create_token(TOKEN_KEYWORD, buffer, lexer->line, lexer->column - strlen(buffer));
            }
            
            return create_token(TOKEN_IDENTIFIER, buffer, lexer->line, lexer->column - strlen(buffer));
        }

        // Handle string literals
        if (c == '"') {
            char buffer[256] = {0};
            int i = 0;
            lexer_advance(lexer); // Skip opening quote
            
            while (lexer_peek(lexer) != '"' && lexer_peek(lexer) != '\0') {
                buffer[i++] = lexer_advance(lexer);
            }
            
            if (lexer_peek(lexer) == '"') {
                lexer_advance(lexer); // Skip closing quote
            }
            
            return create_token(TOKEN_STRING, buffer, lexer->line, lexer->column - strlen(buffer) - 2);
        }

        // Handle other single characters
        char single_char[2] = {c, '\0'};
        lexer_advance(lexer);
        return create_token(TOKEN_OPERATOR, single_char, lexer->line, lexer->column - 1);
    }

    return create_token(TOKEN_EOF, "", lexer->line, lexer->column);
}

void lexer_destroy(Lexer* lexer) {
    free(lexer->source);
    free(lexer);
} 