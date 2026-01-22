#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

/**
 * In array of chunk, this will walk through each
 * chunk instruction and determine/ debug user what instruction are in the code
 */
void disassembleChunk(Chunk *chunk, const char *name);

/**
 * Print each instruction offset
 */
int disassembleInstruction(Chunk *chunk, int offset);

#endif /* ifndef clox_debug_h */
