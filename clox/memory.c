#include "memory.h"
#include "value.h"
#include "vm.h"
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

void freeObjects() {
  Obj *object = vm.objects;
  while (object != NULL) {
    Obj *next = object->next;
    freeObjects(object);
    object = next;
  }
}
