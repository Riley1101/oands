#ifndef clox_vm_h
#define clox_vm_h

#define STACK_MAX 256

#include "chunk.h"
#include "value.h"
#include <stdint.h>

typedef struct {
  Chunk *chunk;
  // In CS it's called instruction pointer/paging counter
  // this is inprogress location where VM is executing,
  // We don't store this as local variable because this will be reused by
  // various different instructions
  uint8_t *ip;

  Value stack[STACK_MAX];
  Value *stackTop;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR,
} InterprectResult;

static void resetStack();
void initVM();
void freeVM();

InterprectResult interpret(Chunk *chunk);
void push(Value value);
Value pop();

#endif // !clox_vm_h
