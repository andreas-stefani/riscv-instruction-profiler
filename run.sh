#!/bin/bash

declare -A sources=(
    [fib]="programs/fibonacci.c"
    [cpy]="programs/array_copy.c"
    [primef]="programs/prime_factor.c"
    [qsort]="programs/quicksort.c"
    [sieve]="programs/sieve.c"
)
BASE_DIR=$(pwd)
export PATH=$PATH:$BASE_DIR/riscv/bin
rm -rf output
mkdir -p output/bins
mkdir -p output/traces

for name in "${!sources[@]}"; do
    riscv64-unknown-elf-gcc -static -Wall ${sources[$name]} -lm -o  output/bins/${name}_riscv
done

echo -e "\nCompilation done. Saved in : output/bins/\n"

for name in "${!sources[@]}"; do
    echo -e "\nTracing $name...\n"
    qemu-riscv64 -d in_asm ./output/bins/${name}_riscv 2> output/traces/${name}_trace.txt
done

echo -e "\nDone. Saved in : output/traces/\n"

for name in "${!sources[@]}"; do
    riscv64-unknown-elf-objdump -d output/bins/${name}_riscv > output/${name}.dump
done

echo -e "\nDumps done. Saved in : output/\n"

python programs/analyse.py
