CC = gcc
CFLAGS = -Wall -Wextra -I.
DEPS = lexer.h parser.h caroba.h preprocessor.h generator.h
OBJ = lexer.o parser.o caroba_compiler.o caroba.o preprocessor.o generator.o

# Default target
all: caroba

# Compile object files
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Link the compiler
caroba: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Clean build files
clean:
	rm -f *.o caroba

.PHONY: all clean