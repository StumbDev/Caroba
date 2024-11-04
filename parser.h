#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum {
    NODE_PROGRAM,
    NODE_FUNCTION,
    NODE_VAR_DECL,
    NODE_FOR_LOOP,
    NODE_EXPRESSION,
    NODE_CALL
} NodeType;

typedef struct Node {
    NodeType type;
    Token* token;
    struct Node** children;
    int children_count;
} Node;

typedef struct {
    Lexer* lexer;
    Token* current_token;
} Parser;

Parser* parser_create(Lexer* lexer);
Node* parser_parse(Parser* parser);
void parser_destroy(Parser* parser);

#endif 