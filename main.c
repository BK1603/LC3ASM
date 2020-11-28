// Hopefully we will make an assembler today. That is able to assemble hello world
// in assembly. In the ideal case we will have two passes ready. Thank you. xD

#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

// MOV RAX, RDX
// ADD RAX, 8
// JMPZ LABEL1
//
//
// ...
// ...
//
// LABEL1:
// ...
// ..
//
//
// Syntax: Intel format.
// [Opcode] [Destination Operand] [Source Operand]
// ADD RAX, RCX, RBX
//
// ADD = 0001
// RAX = Register number
// RBX = Register number
// 000
// RCX = Register number
//
// BR = 0000
// n = 100
// BRn = 0000100
// BRz = 0000010
// BRp = 0000001
//
// LD RAX 000000110101
// RAX = [000000110101]
//
// LDR RAX RBX 000001110
// RAX = [RBX + 0000001110]
//
// Immediate type instructions
// Direct value
// ADD RAX, 7

int main(int argc, char **argv) {
  // Program should called with an asm file.
  if (argc != 2) {
    printf("ERROR: No file provided. Usage: ASM [filename]\n");
    return 1;
  }


  // Read the file.
  // TODO: make function read_file
  if (!check_file((const char *)argv[1])) {
    printf("ERROR: Could not read assembly file.\n");
    return 1;
  }

  FILE *ifp = fopen((const char *)argv[1], "r"); //lc3acm file.asm

  // TODO: Generate output file name
  char *output_file = gen_output_file((const char *)argv[1]); //file.asm -> file.out
  FILE *ofp = fopen((const char *)output_file, "wb");

  unsigned int len = 0;
  char *current_line;
  while((read  = getline(&current_line, &len, ifp))) {
    uint16_t instr;

    // TODO: create parse_line
    instr = parse_line(current_line); // main function. character line -> binary code.

    // write to ofp
    fwrite(instr, sizeof(instr), 1, ofp);
  }
  // First pass.
  // 1. Parse labels.
  // 2. Store in symbol table.
  //
  // Second pass.
  // For each line:
  // 1. Parse instruction name. ADD -> OpAdd.
  // 2. Registers
  // 3. Final instruction
  // 4. Output file.
  //
  // Write to second file
  return 0;
}
