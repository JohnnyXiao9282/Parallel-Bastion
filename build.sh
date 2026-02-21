#!/bin/bash

echo "=== Building Parallel Bastion ==="

# Check if SDL2 is installed
if ! command -v sdl2-config &> /dev/null; then
    echo "SDL2 not found. Installing..."
    if [[ "$OSTYPE" == "darwin"* ]]; then
        brew install sdl2
    elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
        sudo apt-get install libsdl2-dev
    fi
fi

# Create build directory
mkdir -p build
cd build

# Configure and build
cmake ..
cmake --build .

echo ""
echo "=== Build complete ==="
echo "Run with: ./build/parallel_bastion"
