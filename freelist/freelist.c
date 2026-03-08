
/**
 * A free list of size 4096 bytes
 */
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>

typedef struct __node_t {
  int size;
  struct __node_t *next;
} node_t;

int main(int argc, char *argv[]) {

  // NULL here tells to allocate the virtual space at the page-aligned address 
  // Check linux manual
  node_t *head =
      mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

  head->size = 4096 - sizeof(node_t);
  head->next = NULL;

  return EXIT_SUCCESS;
}
