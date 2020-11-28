#ifndef LC3_H
#define LC3_H

/* registers */
enum {
  R_R0 = 0,
  R_R1,
  R_R2,
  R_R3,
  R_R4,
  R_R5,
  R_R6,
  R_R7,
};

/* instruction set */
enum {
  OP_BR=0,    /* branch */ //BR RBX ...., BR->OP_BR, opcode write.
  OP_ADD,
  OP_LD,
  OP_ST,
  OP_JSR,     /* jump register */
  OP_AND,     /* bitwise and */
  OP_LDR,     /* load register */
  OP_STR,     /* store register */
  OP_RTI,     /* unused */
  OP_NOT,
  OP_LDI,     /* load indirect */
  OP_STI,     /* store indirect */
  OP_JMP,
  OP_RES,     /* reserved */
  OP_LEA,
  OP_TRAP
};

/* flags */
enum {
  FL_POS = 1 << 0,
  FL_ZRO = 1 << 1,
  FL_NEG = 1 << 2,
};

#endif
