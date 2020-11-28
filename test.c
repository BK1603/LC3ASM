#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

void print_binary(int x) {
  for (int i = 0; i < 16; i++) {
    printf("%d", x & 0x1);
    x >>= 1;
  }
  printf("\n");
}

int main() {
  char str[50] = "LDI R0 1023";
  int x = parse_line(str);
  print_binary(x);
  return 0;
}
