#include "compiler.h"
#include "scanner.h"
#include <stdio.h>

void compile(const char *source) {
  initScanner(source);
  int line = -1;
  for (;;) {
    Token token = scanToken();
    printf("%2d '%.*s'\n", token.type, token.length, token.start);
    if (token.line != line) {
      printf("%4d \n", token.line);
      line = token.line;
    } else {
      printf("    | \n");
    }

    if (token.type == TOKEN_EOF) {
      break;
    }
  }
}
