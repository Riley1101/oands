#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"
#include "scanner.h"

/**
 * In array of chunk, this will walk through each
 * chunk instruction and determine/ debug user what instruction are in the code
 */
void disassembleChunk(Chunk *chunk, const char *name);

/**
 * Print each instruction offset
 */
int disassembleInstruction(Chunk *chunk, int offset);

/** Return human-readable name for a token type (for debugging). */
const char *tokenTypeName(TokenType type);

/** Print a single token: line, type name, and lexeme for literals/identifiers. */
void printToken(Token token);

/** Scan source and print every token until EOF (for scanner debugging). */
void debugScanTokens(const char *source);

#endif /* ifndef clox_debug_h */
