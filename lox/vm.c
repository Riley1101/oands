#include "vm.h"
#include "chunk.h"
#include "compiler.h"
#include "debug.h"
#include "value.h"
#include <stdio.h>
#include <sys/types.h>

VM vm;

static void resetStack() { vm.stackTop = vm.stack; }

void initVM() {
  vm.chunk = NULL;
  vm.ip = NULL;
  resetStack();
}

void freeVM() {
  if (vm.chunk != NULL) {
    freeChunk(vm.chunk);
    vm.chunk = NULL;
  }
}

void push(Value value) {
  *vm.stackTop = value;
  vm.stackTop++;
}

Value pop() {
  vm.stackTop--;
  // copy of value at the top
  return *vm.stackTop;
}

static InterprectResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op)                                                          \
  do {                                                                         \
    double b = pop();                                                          \
    double a = pop();                                                          \
    push(a op b);                                                              \
  } while (false)
  for (;;) {
#ifdef DEBUG_TRACING_EXTENSION
    printf("        \n");
    for (Value *slot = vm.stack; slot < vm.stackTop; slot++) {
      printf("[  ");
      printValue(*slot);
      printf("  ]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif /* ifndef DEBUG_TRACING_EXTENSION */

    uint8_t instruction;

    switch (instruction = READ_BYTE()) {

    case OP_CONSTANT: {
      Value constant = READ_CONSTANT();
      printValue(constant);
      printf("\n");
      push(constant);
      break;
    }
    case OP_ADD:
      BINARY_OP(+);
      break;
    case OP_SUBTRACT:
      BINARY_OP(-);
      break;
    case OP_MULTIPLY:
      BINARY_OP(*);
      break;
    case OP_DIVIDE:
      BINARY_OP(/);
      break;
    case OP_NEGATE: {
      push(-pop());
      break;
    }
    case OP_RETURN: {
      printValue(pop());
      printf("\n");
      return INTERPRET_OK;
    }
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

InterprectResult interpret(const char *source) {
  Chunk chunk;
  initChunk(&chunk);

  if (!compile(source, &chunk)) {
    freeChunk(&chunk);
    return INTERPRET_COMPILE_ERROR;
  }
  vm.chunk = &chunk;
  vm.ip = vm.chunk->code;
  InterprectResult result = run();
  freeChunk(&chunk);
  return result;
}
