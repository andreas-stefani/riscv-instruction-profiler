import os
import pandas as pd

# Full RV64I + M extension instruction set
RV64I = {
    # Loads
    'lb', 'lh', 'lw', 'ld', 'lbu', 'lhu', 'lwu',
    # Stores
    'sb', 'sh', 'sw', 'sd',
    # Arithmetic immediate
    'addi', 'addiw', 'slti', 'sltiu', 'xori', 'ori', 'andi',
    'slli', 'srli', 'srai', 'slliw', 'srliw', 'sraiw',
    # Arithmetic register
    'add', 'addw', 'sub', 'subw', 'sll', 'sllw', 'slt', 'sltu',
    'xor', 'srl', 'srlw', 'sra', 'sraw', 'or', 'and',
    # Multiply/Divide (M extension)
    'mul', 'mulh', 'mulhsu', 'mulhu', 'div', 'divu', 'rem', 'remu',
    'mulw', 'divw', 'divuw', 'remw', 'remuw',
    # Branches
    'beq', 'bne', 'blt', 'bge', 'bltu', 'bgeu',
    # Jumps
    'jal', 'jalr',
    # Upper immediate
    'lui', 'auipc',
    # System
    'ecall', 'ebreak',
    # Pseudoinstructions
    'li', 'mv', 'ret', 'j', 'beqz', 'bnez', 'bgtz', 'bltz', 'blez', 'bgez',
    'nop', 'not', 'neg', 'seqz', 'snez', 'sltz', 'sgtz', 'call', 'tail',
}

OUTPUT_DIR = 'output'
benchmarks = ['fib', 'cpy', 'primef', 'qsort', 'sieve']

all_used = {}
for name in benchmarks:
    path = os.path.join(OUTPUT_DIR, f'{name}.dump')
    used = set()
    with open(path) as f:
        for line in f:
            parts = line.split()
            if len(parts) >= 3 and parts[0].endswith(':'):
                mnemonic = parts[2]
                if mnemonic in RV64I:
                    used.add(mnemonic)
    all_used[name] = used

union_used = set().union(*all_used.values())
never_used = RV64I - union_used

print("=" * 60)
print("RISC-V Instruction Subset Analysis")
print(f"Total instructions in RV64I+M : {len(RV64I)}")
print(f"Instructions used (any benchmark) : {len(union_used)}")
print(f"Instructions NEVER used : {len(never_used)}")
print("=" * 60)
print(f"\nNever used across all benchmarks:")
print(f"  {sorted(never_used)}\n")

print("=" * 60)
print("Per-benchmark subset:")
print("=" * 60)
for name in benchmarks:
    used   = all_used[name]
    unused = RV64I - used
    print(f"\n{name} — uses {len(used)}, missing {len(unused)}:")
    print(f"  {sorted(unused)}\n")

