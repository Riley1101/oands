#include "memory.h"
#include <stdlib.h>

void *reallocate(void *pointer, size_t oldSize, size_t newSize) {

  // temporary ignore for now
  (void)oldSize;

  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  void *result = realloc(pointer, newSize);

  if (result == NULL) {
    exit(EXIT_FAILURE);
  }

  return result;
}
