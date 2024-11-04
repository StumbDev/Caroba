#include "caroba.h"

int main() {
    // Variable declaration
    CarobaVar* name = caroba_input("Enter your name: ");
    CarobaVar* age = caroba_input("Enter your age: ");

    // Print using standard function
    caroba_print("Hello, %s! You are %s years old.\n", name->value, age->value);

    // Memory management
    caroba_free(name);
    caroba_free(age);

    return 0;
} 