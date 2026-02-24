#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

//  Picking 8 is very arbitarity but in real world should pick constant based on
//  waht make sense the most
#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount)                          \
  (type *)reallocate(pointer, sizeof(type) * (oldCount),                       \
                     sizeof(type) * (newCount));
#define FREE_ARRAY(type, pointer, oldCount)                                    \
  reallocate(pointer, sizeof(type) * (oldCount), 0)

/**
 * Reallocate based on pointer and new size.
 * @param pointer 
 * @param (int) oldSize in size_t
 * @param newSize in size_t
 */
void *reallocate(void *pointer, size_t oldSize, size_t newSize);

#endif // !clox_memory_h
