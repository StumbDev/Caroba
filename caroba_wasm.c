#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "preprocessor.h"
#include "generator.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

EMSCRIPTEN_KEEPALIVE
char* compile_caroba(const char* source) {
    // First preprocess the source to convert @ syntax to C
    char* processed_source = preprocess_caroba(source);
    
    // Then proceed with lexing and parsing
    Lexer* lexer = lexer_create(processed_source);
    Parser* parser = parser_create(lexer);
    Node* ast = parser_parse(parser);
    
    // Generate output
    char* result = generate_code(ast);
    
    // Cleanup
    parser_destroy(parser);
    lexer_destroy(lexer);
    free(processed_source);
    
    return result;
}

// Helper function to free memory from JavaScript
EMSCRIPTEN_KEEPALIVE
void free_result(char* ptr) {
    free(ptr);
} 