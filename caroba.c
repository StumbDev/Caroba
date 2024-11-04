#include "caroba.h"
#include <stdarg.h>

// Implementation of core functions
CarobaVar* caroba_print(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    
    return NULL; // Return NULL since print doesn't need to return a value
}

CarobaVar* caroba_input(const char* prompt) {
    printf("%s", prompt);
    
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        // Remove trailing newline
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
        
        // Create new CarobaVar
        CarobaVar* var = malloc(sizeof(CarobaVar));
        var->type = "string";
        var->value = strdup(buffer);
        return var;
    }
    
    return NULL;
}

CarobaVar* caroba_alloc(size_t size) {
    CarobaVar* var = malloc(sizeof(CarobaVar));
    var->type = "raw";
    var->value = malloc(size);
    return var;
}

void caroba_free(CarobaVar* ptr) {
    if (ptr) {
        free(ptr->value);
        free(ptr);
    }
} 