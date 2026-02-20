#include "compiler.h"
#include "scanner.h"
#include <stdio.h>

void compile(const char *source) {
  initScanner(source);

  for (;;) {
    Token token = scanToken();
    if (token.type == TOKEN_EOF)
      break;
    printf("%d '%.*s'\n", token.type, token.length, token.start);
  }
}
