#include <stdio.h>
#include <stdlib.h>

void forget_free() {
  printf("In forget free.\n");

  int *arr = malloc(sizeof(int) * 2);

  arr[0] = 1;

  arr[1] = 2;

  for (int i = 0; i < 2; i++) {
    printf("i : %d\n", arr[i]);
  }
  free(arr);
}

void one_hundred() {
  int size = 100;
  int *arr = malloc(sizeof(int) * size);

  arr[size - 1] = 0;

  free(arr);

}

int main(int argc, char *argv[]) {
  //
  // int *ptr = malloc(sizeof(int));
  //
  // *ptr = 12;
  //
  // printf("Value of ptr  is %d\n", *ptr);
  //
  // free(ptr);
  //
  // ptr = NULL;
  //
  // forget_free();

  one_hundred();

  return EXIT_SUCCESS;
}
