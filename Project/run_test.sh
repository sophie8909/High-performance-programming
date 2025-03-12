#!/bin/bash

echo "Running Sudoku Solver for all input files..."



TEST_CASES=(
    "board_25x25"
    "board_36x36"
    "board_64x64"
)


# Input and output directories
INPUT_DIR="input"
SIM_EXEC="./sudoku"

echo "Running simulations with nthreads=$NTHREADS..."

for CASE in "${TEST_CASES[@]}"; do
    INPUT_FILE="${INPUT_DIR}/${CASE}.dat"

    # Extract N value from the filename
    N=$(echo "$CASE" | grep -o '[0-9]\+')

    echo "Running simulation for $CASE (N=$N)..."
    time $SIM_EXEC $INPUT_FILE 

    echo "========================================="
done


echo "All simulations completed!"
