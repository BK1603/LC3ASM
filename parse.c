#include "parse.h"
#include "asm.h"
#include <stdio.h>
#include <string.h>

int startsWith(const char *pre, const char *str) {
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? 0 : memcmp(pre, str, lenpre) == 0;
}

unsigned int parse_opcode(char *token) {
  if (strcmp(token, "ADD") == 0) {
    return OP_ADD;
  } else if (strcmp(token, "AND") == 0) {
    return OP_AND;
  } else if (strcmp(token, "NOT") == 0) {
    return OP_NOT;
  } else if (startsWith("BR", token)) {
    return OP_BR;
  } else if (strcmp("LD", token) == 0) {
    return OP_LD;
  } else if (strcmp("LDI", token) == 0) {
    return OP_LDI;
  } else if (strcmp("LDR", token) == 0) {
    return OP_LDR;
  } else if (strcmp("LEA", token) == 0) {
    return OP_LEA;
  } else if (strcmp("ST", token) == 0) {
    return OP_ST;
  } else if (strcmp("STI", token) == 0) {
    return OP_STI;
  } else if (strcmp("STR", token) == 0) {
    return OP_STR;
  } else if (strcmp("TRAP", token) == 0) {
    return OP_TRAP;
  }
  return -1;
}

unsigned int parse_imm5(char *token) {
  unsigned int x = atoi(token);
  if (x >= 32) {
    return -1;
  }
  return x;
}

unsigned int parse_imm6(char *token) {
  unsigned int x = atoi(token);
  if (x >= 64) {
    return -1;
  }
  return x;
}

unsigned int parse_imm8(char *token) {
  unsigned int x = atoi(token);
  if (x >= 512) {
    return -1;
  }
  return x;
}

unsigned int parse_imm9(char *token) {
  unsigned int x = atoi(token);
  if (x >= 512) {
    return -1;
  }
  return x;
}

unsigned int parse_reg(const char *reg) {
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

uint16_t parse_and() {
  uint16_t instr = 0;
  instr |= (OP_AND << 12);
  char space[2] = " ";

  char *token = strtok(NULL, space);
  unsigned int dr = parse_reg(token);
  instr |= (dr << 9);

  token = strtok(NULL, space);
  unsigned int sr1 = parse_reg(token);
  instr |= (sr1 << 6);

  token = strtok(NULL, space);
  if (token[1] == 'R') {
    unsigned int sr2 = parse_reg(token);
    instr |= sr2;
  } else {
    unsigned int imm5 = parse_imm5(token);
    instr |= (1 << 5);
    instr |= imm5;
  }

  return instr;
}

// 1001 DR SR 11111
uint16_t parse_not() {
  uint16_t instr = 0;
  instr |= (OP_NOT << 12);
  char space[2] = " ";

  char *token = strtok(NULL, space);
  unsigned int dr = parse_reg(token);
  instr |= (dr << 9);

  token = strtok(NULL, space);
  unsigned int sr = parse_reg(token);
  instr |= (dr << 6);

  instr |= 0x1F;
  return instr;
}

uint16_t parse_branch(char *token) {
  uint16_t instr = 0;
  char space[2] = " ";
  instr |= (OP_BR << 12);

  unsigned int flag;
  flag = ((token[2] == 'n') << 2) | ((token[2] == 'z') << 1) | (token[2] == 'p');
  instr |= (flag << 9);

  token = strtok(NULL, space);
  unsigned int imm9 = parse_imm9(token);
  instr |= imm9;

  return instr;
}

uint16_t parse_ld() {
  unsigned int instr = 0;
  char space[2] = " ";
  instr |= (OP_LD << 12);

  char *token = strtok(NULL, space);
  unsigned int dr = parse_reg(token);
  instr |= (dr << 9);
  printf("%d\n", dr);

  token = strtok(NULL, space);
  unsigned int imm9 = parse_imm9(token);
  instr |= imm9;

  return instr;
}

uint16_t parse_ldi() {
  uint16_t instr = 0;
  char space[2] = " ";
  instr |= (OP_LDI << 12);

  char *token = strtok(NULL, space);
  unsigned int dr = parse_reg(token);
  instr |= (dr << 9);

  token = strtok(NULL, space);
  unsigned int imm9 = parse_imm9(token);
  instr |= imm9;

  return instr;
}

uint16_t parse_ldr() {
  uint16_t instr = 0;
  char space[2] = " ";
  instr |= (OP_LDR << 12);

  char *token = strtok(NULL, space);
  unsigned int dr = parse_reg(token);
  instr |= (dr << 9);

  token = strtok(NULL, space);
  unsigned int br = parse_reg(token);
  instr |= (dr << 6);

  token = strtok(NULL, space);
  unsigned int imm6 = parse_imm6(token);
  instr |= imm6;

  return instr;
}

uint16_t parse_lea() {
  uint16_t instr = 0;
  char space[2] = " ";
  instr |= (OP_LEA << 12);

  char *token = strtok(NULL, space);
  unsigned int dr = parse_reg(token);
  instr |= (dr << 9);

  token = strtok(NULL, space);
  unsigned int imm9 = parse_imm9(token);
  instr |= imm9;

  return instr;
}

uint16_t parse_st() {
  uint16_t instr = 0;
  char space[2] = " ";
  instr |= (OP_ST << 12);

  char *token = strtok(NULL, space);
  unsigned int sr = parse_reg(token);
  instr |= (sr << 9);

  token = strtok(NULL, space);
  unsigned int imm9 = parse_imm9(token);
  instr |= imm9;

  return instr;
}

uint16_t parse_sti() {
  uint16_t instr = 0;
  char space[2] = " ";
  instr |= (OP_STI << 12);

  char *token = strtok(NULL, space);
  unsigned int sr = parse_reg(token);
  instr |= (sr << 9);

  token = strtok(NULL, space);
  unsigned int imm9 = parse_imm9(token);
  instr |= imm9;

  return instr;
}

uint16_t parse_str() {
  uint16_t instr = 0;
  char space[2] = " ";
  instr |= (OP_STR << 12);

  char *token = strtok(NULL, space);
  unsigned int sr = parse_reg(token);
  instr |= (sr << 9);

  token = strtok(NULL, space);
  unsigned int br = parse_reg(token);
  instr |= (br << 6);

  token = strtok(NULL, space);
  unsigned int imm6 = parse_reg(token);
  instr |= imm6;

  return instr;
}

uint16_t parse_trap() {
  uint16_t instr = 0;
  char space[2] = " ";
  instr |= (OP_TRAP << 12);

  char *token = strtok(NULL, space);
  unsigned int trap8 = parse_imm8(token);
  instr |= trap8;
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
  opcode = parse_opcode(token);
  switch (opcode) {
    case OP_ADD:
      return parse_add();
    case OP_AND:
      return parse_and();
    case OP_NOT:
      return parse_not();
    case OP_BR:
      return parse_branch(token);
    case OP_JMP:
      // return parse_jump();
    case OP_JSR:
      // return parse_jsr();
    case OP_LD:
      return parse_ld();
    case OP_LDI:
      return parse_ldi();
    case OP_LDR:
      return parse_ldr();
    case OP_LEA:
      return parse_lea();
    case OP_ST:
      return parse_st();
    case OP_STI:
      return parse_sti();
    case OP_STR:
      return parse_str();
    case OP_TRAP:
     return parse_trap();
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
