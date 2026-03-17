# RISC-V Instruction Usage Profiler
**Andreas Stefani** - University of Cyprus, Computer Science

## About
A small tool I built to analyze which RISC-V instructions are actually used by real programs, and which ones are never touched.
The motivation comes from the paper Professor H. Volos sent me on FlexIC/RISSP, that talks about how extreme edge devices can get away with a minimal instruction subset rather than implementing the full ISA.
Reference: https://dl.acm.org/doi/10.1145/3725843.3756036

## How it works
Five C benchmark programs stress different aspects of a CPU:

| Program | What it stresses |
|---------|-----------------|
| `fibonacci.c` | Recursive call stack (fib(42), naive) |
| `array_copy.c` | Memory bandwidth (100M element copy) |
| `prime_factor.c` | Integer arithmetic (trial division on large semiprime) |
| `quicksort.c` | Mixed — comparisons, swaps, recursion (1000 × 1000 loops) |
| `sieve.c` | Array indexing and branching (Sieve of Eratosthenes, 10M) |

All benchmark input sizes are defined as compile-time constants (`#define`) at the top of each source file.

`run.sh` cross-compiles all five to RISC-V using `riscv64-unknown-elf-gcc`, disassembles the binaries with `objdump`, and runs `analyse.py` to analyze the results.

`analyse.py` compares the instructions found in each binary against the full RV64I+M instruction set and reports which instructions are used, unused, and never touched across any benchmark.

## Results

Out of 83 instructions in RV64I+M, **27 are never used** across any benchmark.
This suggests a FlexIC chip targeting these workloads could drop them with no impact on correctness.

| Benchmark | Instructions Used | Instructions Missing |
|-----------|:-----------------:|:--------------------:|
| `fibonacci.c` | 51 | 32 |
| `array_copy.c` | 51 | 32 |
| `prime_factor.c` | 53 | 30 |
| `quicksort.c` | 54 | 29 |
| `sieve.c` | 52 | 31 |
| **Union (any benchmark)** | **56** | **27** |

Never used across all benchmarks:
`call` `divu` `divuw` `divw` `ebreak` `lb` `lwu` `mulh` `mulhsu` `mulhu`
`remu` `remuw` `remw` `seqz` `sgtz` `slt` `slti` `sltiu` `sltu` `sltz`
`snez` `sra` `sraw` `srlw` `tail` `xor` `xori`

## Usage
```bash
./run.sh
```
Output is saved in `output/`.

## Requirements
`riscv64-unknown-elf-gcc` and `qemu-riscv64` must be on your PATH.
A prebuilt toolchain can be found at https://github.com/riscv-collab/riscv-gnu-toolchain

## Notes
This is static analysis - it checks which instructions appear in the binary, not how many times they execute at runtime.
Dynamic profiling (e.g. via spike) is a natural next step and something I plan to explore further.
