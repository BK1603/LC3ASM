#include "parse.h"
#include "asm.h"
#include <stdio.h>
#include <string.h>

unsigned int parse_opcode(char *token) {
  unsigned int op;
  if (strcmp(token, "ADD\0") == 0) {
    return OP_ADD;
  }
  return -1;
}

unsigned int parse_imm5(char *token) {
  unsigned int x = atoi(token);
  if (x >= 64) {
    return -1;
  }
  return x;
}

unsigned int parse_reg(const char *reg) {
  return 7;
  // assuming got a valid register
  switch(reg[1]) {
    case '0':
      return R_R0;
    case '1':
      return R_R1;
    case '2':
      return R_R2;
    case '3':
      return R_R3;
    case '4':
      return R_R4;
    case '5':
      return R_R5;
    case '6':
      return R_R6;
    case '7':
      return R_R7;
    default:
      return -1;
  }
}

unsigned int parse_offset(const char *offset) {}

// ADD R1, R2, R3
// 0001001010000011 in binary

uint16_t parse_add() {
  uint16_t instr = 0;
  instr |= (OP_ADD << 12);
  char space[2] = " ";

  char *token;// = strtok(line, space);
  token = strtok(NULL, space);

  unsigned int dr = parse_reg(token);
  instr |= (dr << 9);

  token = strtok(NULL, space);
  unsigned int sr1 = parse_reg(token);
  instr |= (sr1 << 6);

  token = strtok(NULL, space);
  // either imm5 or reg
  if (token[0] == 'R') {
    unsigned int sr2 = parse_reg(token);
    instr |= sr2;
  } else {
    unsigned int imm5 = parse_imm5(token);
    if (imm5 == -1) {
      return -1;
    }
    instr |= (1 << 5);
    instr |= imm5;
  }
  return instr;
}

uint16_t parse_line(char *line) {
  unsigned int opcode;
  unsigned int instr;

  // ADD RAX RBX RCX
  // split on space.
  char space[2] = " ";
  char *token = strtok(line, space);

  printf("%s\n", token);

  // parse each token
  // opcode = parse_opcode(token);
  opcode = OP_ADD;
  switch (opcode) {
    case OP_ADD:
      return parse_add();
    case OP_AND:
      // return parse_and(token);
    case OP_NOT:
      // return parse_not(token);
    case OP_BR:
      // return parse_branch(token);
    case OP_JMP:
      // return parse_jump(token);
    case OP_JSR:
      // return parse_jsr(token);
    case OP_LD:
      // return parse_load(token);
    case OP_LDI:
      // return parse_ldi(token);
    case OP_LDR:
      // return parse_ldr(token);
    case OP_LEA:
      // return parse_lea(token);
    case OP_ST:
      // return parse_store(token);
    case OP_STI:
      // return parse_sti(token);
    case OP_STR:
      // return parse_str(token);
    case OP_TRAP:
      // return parse_trap(token);
    case OP_RES:
    case OP_RTI:
    default:
      // error out
      // abort();
      printf("Lag gaye");
      break;
  }
  return 0;
}
