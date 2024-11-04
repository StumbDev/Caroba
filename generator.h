#ifndef GENERATOR_H
#define GENERATOR_H

#include "parser.h"

// Generate C code from AST
char* generate_code(Node* ast);

#endif 