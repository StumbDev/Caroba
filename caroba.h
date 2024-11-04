// Caroba Language Core Header
#ifndef CAROBA_H
#define CAROBA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Caroba type definitions
typedef struct CarobaVar {
    char* type;
    void* value;
    size_t size;
} CarobaVar;

// Type system
#define bruh void*     // Dynamic type
#define stfOut "stdout:"  // Standard output prefix

// Core functions
CarobaVar* caroba_print(const char* format, ...);
CarobaVar* caroba_input(const char* prompt);
CarobaVar* caroba_alloc(size_t size);
void caroba_free(CarobaVar* ptr);

// String operations
char* caroba_concat(const char* str1, const char* str2);
char* caroba_type_to_string(const char* type);

// Type system functions
CarobaVar* caroba_create_var(const char* type, void* value);
const char* caroba_get_type(CarobaVar* var);

#endif 