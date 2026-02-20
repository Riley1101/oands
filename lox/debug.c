#include "debug.h"
#include "chunk.h"
#include "scanner.h"
#include "value.h"
#include <stdint.h>
#include <stdio.h>

static int simpleInstruction(const char *name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}

static int constantInstruction(const char *name, Chunk *chunk, int offset) {
  uint8_t constant = chunk->code[offset + 1];

  printf(" %-16s @ %4d", name, constant);
  printValue(chunk->constants.values[constant]);
  printf("\n");
  // consume first OP_CONSTANT and CONSTANT_INDEX
  return offset + 2;
}

void disassembleChunk(Chunk *chunk, const char *name) {
  printf("== %s ==\n", name);

  for (int offset = 0; offset < chunk->count;) {
    offset = disassembleInstruction(chunk, offset);
  }
}

int disassembleInstruction(Chunk *chunk, int offset) {

  // fill 0000
  printf("%04d", offset);
  if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
    printf("   | ");
  } else {
    printf("%4d", chunk->lines[offset]);
  }

  uint8_t instruction = chunk->code[offset];

  switch (instruction) {
  case OP_RETURN:
    return simpleInstruction("OP_RETURN", offset);
  case OP_NEGATE:
    return simpleInstruction("OP_NEGATE", offset);
  case OP_CONSTANT:
    return constantInstruction("OP_CONSTANT", chunk, offset);
  default:
    printf("Unknown opcode %d\n", instruction);
    return offset + 1;
  }
}

const char *tokenTypeName(TokenType type) {
  switch (type) {
  case TOKEN_LEFT_PAREN:
    return "LEFT_PAREN";
  case TOKEN_RIGHT_PAREN:
    return "RIGHT_PAREN";
  case TOKEN_LEFT_BRACE:
    return "LEFT_BRACE";
  case TOKEN_RIGHT_BRACE:
    return "RIGHT_BRACE";
  case TOKEN_COMMA:
    return "COMMA";
  case TOKEN_DOT:
    return "DOT";
  case TOKEN_MINUS:
    return "MINUS";
  case TOKEN_PLUS:
    return "PLUS";
  case TOKEN_SEMICOLON:
    return "SEMICOLON";
  case TOKEN_COLON:
    return "COLON";
  case TOKEN_SLASH:
    return "SLASH";
  case TOKEN_STAR:
    return "STAR";
  case TOKEN_BANG:
    return "BANG";
  case TOKEN_BANG_EQUAL:
    return "BANG_EQUAL";
  case TOKEN_EQUAL:
    return "EQUAL";
  case TOKEN_EQUAL_EQUAL:
    return "EQUAL_EQUAL";
  case TOKEN_GREATER:
    return "GREATER";
  case TOKEN_GREATER_EQUAL:
    return "GREATER_EQUAL";
  case TOKEN_LESS:
    return "LESS";
  case TOKEN_LESS_EQUAL:
    return "LESS_EQUAL";
  case TOKEN_IDENTIFIER:
    return "IDENTIFIER";
  case TOKEN_STRING:
    return "STRING";
  case TOKEN_NUMBER:
    return "NUMBER";
  case TOKEN_AND:
    return "AND";
  case TOKEN_CLASS:
    return "CLASS";
  case TOKEN_ELSE:
    return "ELSE";
  case TOKEN_FALSE:
    return "FALSE";
  case TOKEN_FOR:
    return "FOR";
  case TOKEN_FUN:
    return "FUN";
  case TOKEN_IF:
    return "IF";
  case TOKEN_NIL:
    return "NIL";
  case TOKEN_OR:
    return "OR";
  case TOKEN_PRINT:
    return "PRINT";
  case TOKEN_RETURN:
    return "RETURN";
  case TOKEN_SUPER:
    return "SUPER";
  case TOKEN_THIS:
    return "THIS";
  case TOKEN_TRUE:
    return "TRUE";
  case TOKEN_VAR:
    return "VAR";
  case TOKEN_WHILE:
    return "WHILE";
  case TOKEN_ERROR:
    return "ERROR";
  case TOKEN_EOF:
    return "EOF";
  case TOKEN_ASK:
    return "ASK";
  case TOKEN_AGENT:
    return "AGENT";
  case TOKEN_MODEL:
    return "MODEL";
  case TOKEN_SYSTEM:
    return "SYSTEM";
  case TOKEN_TOOL:
    return "TOOL";
  case TOKEN_GRAMMAR:
    return "GRAMMAR";
  default:
    return "<unknown>";
  }
}

void printToken(Token token) {
  printf("%4d %-14s", token.line, tokenTypeName(token.type));
  switch (token.type) {
  case TOKEN_IDENTIFIER:
  case TOKEN_STRING:
  case TOKEN_NUMBER:
  case TOKEN_ERROR:
    printf(" %.*s", token.length, token.start);
    break;
  default:
    break;
  }
  printf("\n");
}

void debugScanTokens(const char *source) {
  initScanner(source);
  for (;;) {
    Token token = scanToken();
    printToken(token);
    if (token.type == TOKEN_EOF || token.type == TOKEN_ERROR)
      break;
  }
}
