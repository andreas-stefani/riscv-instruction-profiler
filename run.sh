#!/bin/bash

declare -A sources=(
    [fib]="fibonacci.c"
    [cpy]="array_copy.c"
    [primef]="prime_factor.c"
    [qsort]="quicksort.c"
    [sieve]="sieve.c"
)

BASE_DIR=$(pwd)
export PATH=$PATH:$BASE_DIR/riscv/bin

rm -rf output
mkdir -p output

for name in "${!sources[@]}"; do
    riscv64-unknown-elf-gcc -static -Wall programs/${sources[$name]} -lm -o  output/${name}_riscv
done
echo -e "\nCompilation done. Saved in : output/\n"

for name in "${!sources[@]}"; do
    riscv64-unknown-elf-objdump -d output/${name}_riscv > output/${name}.dump
done
echo -e "\nDumps done. Saved in : output/\n"

python programs/analyse.py
