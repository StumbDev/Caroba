#include "parser.h"

Parser* parser_create(Lexer* lexer) {
    Parser* parser = malloc(sizeof(Parser));
    parser->lexer = lexer;
    parser->current_token = lexer_next_token(lexer);
    return parser;
}

static void parser_advance(Parser* parser) {
    parser->current_token = lexer_next_token(parser->lexer);
}

static Node* create_node(NodeType type, Token* token) {
    Node* node = malloc(sizeof(Node));
    node->type = type;
    node->token = token;
    node->children = NULL;
    node->children_count = 0;
    return node;
}

static void add_child(Node* parent, Node* child) {
    parent->children_count++;
    parent->children = realloc(parent->children, sizeof(Node*) * parent->children_count);
    parent->children[parent->children_count - 1] = child;
}

static Node* parse_function(Parser* parser) {
    Node* func_node = create_node(NODE_FUNCTION, parser->current_token);
    parser_advance(parser); // Skip @func
    
    // Parse function name
    if (parser->current_token->type == TOKEN_IDENTIFIER) {
        add_child(func_node, create_node(NODE_EXPRESSION, parser->current_token));
        parser_advance(parser);
    }
    
    // Parse function body
    // ... (implement parsing of function body)
    
    return func_node;
}

Node* parser_parse(Parser* parser) {
    Node* program = create_node(NODE_PROGRAM, NULL);
    
    while (parser->current_token->type != TOKEN_EOF) {
        if (parser->current_token->type == TOKEN_AT) {
            parser_advance(parser);
            if (strcmp(parser->current_token->value, "func") == 0) {
                add_child(program, parse_function(parser));
            }
            // Add other @ cases
        }
        parser_advance(parser);
    }
    
    return program;
}

void parser_destroy(Parser* parser) {
    free(parser);
} 