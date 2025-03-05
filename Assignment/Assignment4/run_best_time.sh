#!/bin/bash

# Set executable names
SIM_EXEC="./galsim"

# Define input parameters
STEPS=100
DELTA_T=0.00001
MODE=0
NTHREADS_LIST=(1 2 4 6 8 12 14 16)
# Define test cases
TEST_CASES="ellipse_N_05000"

# Input and output directories
INPUT_DIR="./input_data"
OUTPUT_DIR="./result.gal"
REF_DIR="./ref_output_data"



for NTHREADS in "${NTHREADS_LIST[@]}"; do
    echo "Running simulations with nthreads=$NTHREADS..."
    INPUT_FILE="${INPUT_DIR}/${TEST_CASES}.gal"

    # Extract N value from the filename
    N=$(echo "$TEST_CASES" | grep -o '[0-9]\+')

    echo "Running simulation for $CASE (N=$N)..."
    time $SIM_EXEC $N $INPUT_FILE $STEPS $DELTA_T $MODE $NTHREADS

    echo "========================================="
done


echo "All simulations completed!"
