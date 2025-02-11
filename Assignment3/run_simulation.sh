#!/bin/bash

# Set executable names
SIM_EXEC="./galsim"
COMP_EXEC="./compare_gal_files/compare_gal_files"

# Define input parameters
STEPS=200
DELTA_T=0.00001
MODE=0

# Define test cases
TEST_CASES=(
    "ellipse_N_00010"
    "ellipse_N_00100"
    "ellipse_N_00500"
    "ellipse_N_01000"
    "ellipse_N_02000"
)

# Input and output directories
INPUT_DIR="./input_data"
OUTPUT_DIR="./result.gal"
REF_DIR="./ref_output_data"

for CASE in "${TEST_CASES[@]}"; do
    INPUT_FILE="${INPUT_DIR}/${CASE}.gal"
    REF_FILE="${REF_DIR}/${CASE}_after200steps.gal"

    # Extract N value from the filename
    N=$(echo "$CASE" | grep -o '[0-9]\+')

    echo "Running simulation for $CASE (N=$N)..."
    time $SIM_EXEC $N $INPUT_FILE $STEPS $DELTA_T $MODE

    echo "Comparing result with reference file..."
    $COMP_EXEC $N $OUTPUT_DIR $REF_FILE

    echo "========================================="
done

FINAL_CASE="ellipse_N_03000"
N=3000
INPUT_FILE="${INPUT_DIR}/${FINAL_CASE}.gal"
REF_FILE="${REF_DIR}/${FINAL_CASE}_after100steps.gal"
echo "Running simulation for $FINAL_CASE (N=N)..."
time $SIM_EXEC $N $INPUT_FILE $STEPS $DELTA_T $MODE
echo "Comparing result with reference file..."
$COMP_EXEC $N $OUTPUT_DIR $REF_FILE


echo "All simulations completed!"
