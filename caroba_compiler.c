#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

void compile_file(const char* filename) {
    // Read source file
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Read file content
    char* source = malloc(size + 1);
    fread(source, 1, size, file);
    source[size] = '\0';
    fclose(file);
    
    // Create lexer and parser
    Lexer* lexer = lexer_create(source);
    Parser* parser = parser_create(lexer);
    
    // Parse the program
    Node* ast = parser_parse(parser);
    
    // Generate C code
    // ... (implement code generation)
    
    // Cleanup
    parser_destroy(parser);
    lexer_destroy(lexer);
    free(source);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return 1;
    }
    
    compile_file(argv[1]);
    return 0;
} 