#!/bin/bash

echo "Running Sudoku Solver for all input files..."



TEST_CASES=(
    "board_25x25"
    "board_36x36"
    "board_64x64"
)

NTHREADS=12

# Input and output directories
INPUT_DIR="input"
# SIM_EXEC="./normal_parallel"
SIM_EXEC="./normal"
# SIM_EXEC="./bitmask_parallel"
# SIM_EXEC="./bitmask"
# SIM_EXEC="./bitmask_parallel_same"



echo "Running $SIM_EXEC simulations with nthreads=$NTHREADS..."

for CASE in "${TEST_CASES[@]}"; do
    INPUT_FILE="${INPUT_DIR}/${CASE}.dat"

    # Extract N value from the filename
    N=$(echo "$CASE" | grep -o '[0-9]\+')

    echo "Running simulation for $CASE (N=$N)..."
    time $SIM_EXEC $INPUT_FILE #$NTHREADS

    echo "========================================="
done


echo "All simulations completed!"
