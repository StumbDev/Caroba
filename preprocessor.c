#include "preprocessor.h"

static char* replace_at_symbols(const char* source) {
    char* result = malloc(strlen(source) * 2); // Allocate extra space for replacements
    char* dest = result;
    
    while (*source) {
        if (*source == '@') {
            source++;
            if (strncmp(source, "var", 3) == 0) {
                strcpy(dest, VAR_TYPE);
                dest += strlen(VAR_TYPE);
                source += 3;
            } else if (strncmp(source, "print", 5) == 0) {
                strcpy(dest, PRINT_FUNC);
                dest += strlen(PRINT_FUNC);
                source += 5;
            } else if (strncmp(source, "input", 5) == 0) {
                strcpy(dest, INPUT_FUNC);
                dest += strlen(INPUT_FUNC);
                source += 5;
            } else if (strncmp(source, "alloc", 5) == 0) {
                strcpy(dest, ALLOC_FUNC);
                dest += strlen(ALLOC_FUNC);
                source += 5;
            } else if (strncmp(source, "free", 4) == 0) {
                strcpy(dest, FREE_FUNC);
                dest += strlen(FREE_FUNC);
                source += 4;
            }
        } else {
            *dest++ = *source++;
        }
    }
    *dest = '\0';
    return result;
}

char* preprocess_caroba(const char* source) {
    return replace_at_symbols(source);
} 