#include <stdio.h>
#include <stdlib.h>

struct node {
  struct node *next;
  int val;
};

int main(int argc, char *argv[]) {

  int size = 3;
  struct node *ptr = malloc(sizeof(struct node) * size);

  ptr[0].val = 0;
  ptr[0].next = &ptr[1];

  ptr[1].val = 1;
  ptr[1].next = &ptr[2];

  ptr[2].val = 2;
  ptr[2].next = NULL;

  for (int i = 0; i < size; i++) {
    printf("Current Node: %d\n", ptr[i].val);
  }

  free(ptr);

  return EXIT_SUCCESS;
}
