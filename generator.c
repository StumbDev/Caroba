#include "generator.h"
#include <string.h>

#define BUFFER_SIZE 4096

static char output[BUFFER_SIZE];
static int output_pos = 0;

static void append_str(const char* str) {
    int len = strlen(str);
    if (output_pos + len < BUFFER_SIZE - 1) {
        strcpy(output + output_pos, str);
        output_pos += len;
    }
}

static void generate_expression(Node* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_EXPRESSION:
            if (node->token) {
                append_str(node->token->value);
            }
            break;
            
        case NODE_CALL:
            // Generate function call
            if (node->token) {
                append_str(node->token->value);
                append_str("(");
                for (int i = 0; i < node->children_count; i++) {
                    generate_expression(node->children[i]);
                    if (i < node->children_count - 1) {
                        append_str(", ");
                    }
                }
                append_str(")");
            }
            break;
            
        default:
            break;
    }
}

static void generate_statement(Node* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_VAR_DECL:
            append_str("CarobaVar* ");
            generate_expression(node->children[0]);
            append_str(" = ");
            generate_expression(node->children[1]);
            append_str(";\n");
            break;
            
        case NODE_FUNCTION:
            append_str("\nint ");
            generate_expression(node->children[0]);
            append_str("() {\n");
            for (int i = 1; i < node->children_count; i++) {
                append_str("    ");
                generate_statement(node->children[i]);
            }
            append_str("}\n");
            break;
            
        default:
            generate_expression(node);
            append_str(";\n");
            break;
    }
}

char* generate_code(Node* ast) {
    output_pos = 0;
    output[0] = '\0';
    
    // Add includes
    append_str("#include \"caroba.h\"\n\n");
    
    // Generate code for each node
    for (int i = 0; i < ast->children_count; i++) {
        generate_statement(ast->children[i]);
    }
    
    return strdup(output);
} 