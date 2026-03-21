#!/bin/bash
# Build and run the Parallel Bastion game from project root
cd "$(dirname "$0")"
cmake --build build
./build/parallel_bastion
