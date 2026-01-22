#ifndef clox_value_h
#define clox_value_h

#include "common.h"

// This is how Lox represent actual values in the lox vm
typedef double Value;

// We keep track of a constant pool for our program to distinguish
// again. dynamic array
typedef struct {
  int capacity;
  int count;
  Value *values;
} ValueArray;

void initValueArray(ValueArray *array);
void writeValueArray(ValueArray *array, Value value);
void freeValueArray(ValueArray *array);
void printValue(Value value);

#endif // !clox_value_h
