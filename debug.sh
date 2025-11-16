#!/bin/bash
#
# Debug script - compiles with debug symbols and runs GDB
#

set -e  # Exit on error

echo "=== Compiling with debug symbols ==="
cd "$(dirname "$0")"

# Clean previous build
rm -rf build

# Compile with debug flags
cmake -B build -S . \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_CXX_FLAGS="-g -O0"

cmake --build ./build

echo ""
echo "=== Starting GDB ==="
echo "Useful GDB commands:"
echo "  - 'run' or 'r' to start the program"
echo "  - 'break main' or 'b main' to set breakpoint at main"
echo "  - 'break src/main.cpp:15' to break at line 15"
echo "  - 'next' or 'n' to step over"
echo "  - 'step' or 's' to step into"
echo "  - 'continue' or 'c' to continue execution"
echo "  - 'print variable' or 'p variable' to inspect"
echo "  - 'quit' or 'q' to exit"
echo ""

# Run GDB with the compiled binary
exec gdb ./build/shell "$@"
