
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  int *x = malloc(sizeof(*x));

  double *d = malloc(sizeof(double));

  int *ten_d = malloc(10 * sizeof(int));

  if (x == NULL || d == NULL || ten_d == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return EXIT_FAILURE;
  }

  *x = 12;

  printf("Size of x: %ld\n", sizeof(*x));
  printf("Size of d: %ld\n", sizeof(*d));
  printf("Size of ten_d: %ld\n", sizeof(*ten_d));

  free(x);
  free(d);
  free(ten_d);

  /***
   * New Block
   **/

  char *src = "Hello";
  char *dst = (char *)malloc(strlen(src) + 1);

  strcpy(dst, src);

  printf("%s\n", dst);

  /* Dangling pointer */

  int *ptr = malloc(sizeof(int));
  *ptr = 100;

  printf("Pointer value is %d\n", *ptr);

  free(ptr);

  printf("Dangling here if not set to NULL %d\n", *ptr);

  *ptr = 200; // Undefined behavior

  return EXIT_SUCCESS;
}
