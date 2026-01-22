#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"
#include <stdint.h>

typedef enum {
  OP_CONSTANT,
  OP_RETURN,
} OpCode;

/**
 * This is going to be like a dynamic list to allocate chunk of code
 */
typedef struct {
  int count;
  int capacity;
  int *lines;
  uint8_t *code;
  ValueArray constants;
} Chunk;

void initChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
void freeChunk(Chunk *chunk);

/**
 * Add a constant to chunk, and returns its index.
 */
int addConstant(Chunk *chunk, Value value);

#endif // !clox_chunk_h
