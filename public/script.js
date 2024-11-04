let wasmModule;

// Initialize WASM module
async function initWasm() {
    try {
        const response = await fetch('caroba.wasm');
        const bytes = await response.arrayBuffer();
        const wasmInstance = await WebAssembly.instantiate(bytes, {
            env: {
                memory: new WebAssembly.Memory({ initial: 256 }),
                abort: () => console.log('Abort!')
            }
        });
        wasmModule = wasmInstance.instance.exports;
    } catch (err) {
        console.error('Failed to load WASM:', err);
    }
}

document.addEventListener('DOMContentLoaded', async () => {
    // Initialize CodeMirror
    editor = CodeMirror.fromTextArea(document.getElementById('code'), {
        mode: 'text/x-c++src',
        theme: 'monokai',
        lineNumbers: true,
        autoCloseBrackets: true,
        matchBrackets: true,
        indentUnit: 4,
        tabSize: 4,
        lineWrapping: true,
        extraKeys: {
            'Ctrl-Enter': runCode
        }
    });

    // Initialize WASM
    await initWasm();

    // Run button click handler
    document.getElementById('runBtn').addEventListener('click', runCode);
});

async function runCode() {
    const outputElement = document.getElementById('output');
    const code = editor.getValue();
    
    try {
        outputElement.textContent = 'Compiling...';
        
        // Convert source code to C string
        const sourcePtr = wasmModule._malloc(code.length + 1);
        const sourceArray = new Uint8Array(wasmModule.memory.buffer);
        for (let i = 0; i < code.length; i++) {
            sourceArray[sourcePtr + i] = code.charCodeAt(i);
        }
        sourceArray[sourcePtr + code.length] = 0; // null terminator
        
        // Compile code using WASM
        const resultPtr = wasmModule._compile_caroba(sourcePtr);
        
        // Read result
        let result = '';
        let i = resultPtr;
        while (sourceArray[i] !== 0) {
            result += String.fromCharCode(sourceArray[i]);
            i++;
        }
        
        // Free memory
        wasmModule._free_result(resultPtr);
        wasmModule._free(sourcePtr);
        
        outputElement.textContent = result || 'Program compiled successfully!';
    } catch (err) {
        outputElement.textContent = `Error: ${err.message}`;
    }
} 