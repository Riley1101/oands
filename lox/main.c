#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void repl(void) {
  char line[1024];
  for (;;) {
    printf("> ");
    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }
    interpret(line);
  }
}

static char *readFile(const char *path) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(74);
  }

  fseek(file, 0L, SEEK_END);
  long fileSize = ftell(file);
  rewind(file);

  char *buffer = (char *)malloc((size_t)fileSize + 1);
  if (buffer == NULL) {
    fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
    exit(74);
  }

  size_t bytesRead = fread(buffer, sizeof(char), (size_t)fileSize, file);
  if (bytesRead < (size_t)fileSize) {
    fprintf(stderr, "Could not read file \"%s\".\n", path);
    exit(74);
  }
  buffer[bytesRead] = '\0';

  fclose(file);
  return buffer;
}

static void runFile(const char *path) {
  char *source = readFile(path);
  InterprectResult result = interpret(source);
  free(source);

  if (result == INTERPRET_COMPILE_ERROR)
    exit(65);
  if (result == INTERPRET_RUNTIME_ERROR)
    exit(70);
}

int main(int argc, char *argv[]) {
  initVM();

  if (argc == 1) {
    repl();
  } else if (argc == 2) {
    if (strcmp(argv[1], "--tokens") == 0) {
      size_t cap = 65536;
      size_t len = 0;
      char *buf = (char *)malloc(cap);
      if (!buf) {
        fprintf(stderr, "Out of memory.\n");
        exit(71);
      }
      for (;;) {
        size_t to_read = cap - len;
        if (to_read < 256) {
          cap *= 2;
          char *n = (char *)realloc(buf, cap);
          if (!n) {
            free(buf);
            fprintf(stderr, "Out of memory.\n");
            exit(71);
          }
          buf = n;
          to_read = cap - len;
        }
        size_t nread = fread(buf + len, 1, to_read, stdin);
        len += nread;
        if (nread < to_read)
          break;
      }
      buf[len] = '\0';
      debugScanTokens(buf);
      free(buf);
    } else {
      runFile(argv[1]);
    }
  } else if (argc == 3 && strcmp(argv[1], "--tokens") == 0) {
    char *source = readFile(argv[2]);
    debugScanTokens(source);
    free(source);
  } else {
    fprintf(stderr, "Usage: clox [path]\n");
    fprintf(stderr, "       clox --tokens [path]   dump tokens (file or stdin)\n");
    exit(64);
  }

  freeVM();
  return 0;
}
