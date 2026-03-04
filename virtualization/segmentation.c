#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

typedef struct __node_t {
  int size;
  struct __node_t *next;
} node_t;

int main(int argc, char *argv[]) {
  node_t *head = mmap(NULL, sizeof(node_t), PROT_READ | PROT_WRITE,
                      MAP_ANON | MAP_PRIVATE, -1, 0);

  if (head == MAP_FAILED) {
    perror("mmap");
    return EXIT_FAILURE;
  }

  head->size = 4096 - sizeof(node_t);
  head->next = NULL;
  return EXIT_SUCCESS;
}
