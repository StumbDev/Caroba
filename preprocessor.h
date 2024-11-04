#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convert Caroba syntax to valid C code
char* preprocess_caroba(const char* source);

// Mapping of Caroba to C types/functions
#define VAR_TYPE "CarobaVar"
#define PRINT_FUNC "caroba_print"
#define INPUT_FUNC "caroba_input"
#define ALLOC_FUNC "caroba_alloc"
#define FREE_FUNC "caroba_free"

#endif 