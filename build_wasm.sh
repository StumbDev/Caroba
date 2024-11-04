#!/bin/bash

# Ensure emscripten is installed
if ! command -v emcc &> /dev/null; then
    echo "Error: emscripten not found. Please install it first."
    exit 1
fi

# Compile to WASM
emcc caroba_wasm.c lexer.c parser.c preprocessor.c generator.c \
    -I${EMSDK}/upstream/emscripten/cache/sysroot/include \
    -o public/caroba.js \
    -s WASM=1 \
    -s EXPORTED_FUNCTIONS='["_compile_caroba", "_free_result", "_malloc", "_free"]' \
    -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
    -s ALLOW_MEMORY_GROWTH=1 \
    -O3

echo "WASM build complete!" 