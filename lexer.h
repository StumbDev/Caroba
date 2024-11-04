#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TOKEN_AT,           // @
    TOKEN_IDENTIFIER,   // variable names, function names
    TOKEN_STRING,       // "string literals"
    TOKEN_NUMBER,       // numbers
    TOKEN_OPERATOR,     // operators like =, +, -
    TOKEN_PARENTHESIS, // (, )
    TOKEN_BRACE,       // {, }
    TOKEN_KEYWORD,     // func, var, for, in
    TOKEN_EOF          // end of file
} TokenType;

typedef struct {
    TokenType type;
    char* value;
    int line;
    int column;
} Token;

typedef struct {
    char* source;
    size_t length;
    size_t position;
    int line;
    int column;
} Lexer;

Lexer* lexer_create(const char* source);
Token* lexer_next_token(Lexer* lexer);
void lexer_destroy(Lexer* lexer);

#endif 