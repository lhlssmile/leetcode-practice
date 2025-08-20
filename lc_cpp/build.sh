#!/bin/bash
set -e

# This script is located in lc_cpp, so we cd to its directory first.
cd "$(dirname "$0")"

# Check if a file path is provided.
if [ -z "$1" ]; then
    echo "Error: No file path provided to build.sh"
    exit 1
fi

# The input path is a Windows path, convert it.
FILE_PATH_WSL=$(wslpath "$1")

echo "--- Building file: $FILE_PATH_WSL ---"

# Create build directory, run cmake and make.
mkdir -p build
cd build
cmake -DMAIN_FILE_PATH="$FILE_PATH_WSL" ..
make

echo "--- Build finished successfully ---"
