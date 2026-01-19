#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <memory_in_mb> [diration in seconds] \n",
            argv[0]);

    return 1;
  }

  long long megabytes = atol(argv[1]);
  long long bytes = megabytes * 1024 * 1024;

  long long duration = (argc == 3) ? atol(argv[2]) : -1;

  printf("Allocating memory %lld\n", megabytes);

  char *memory = malloc(bytes);

  if (memory == NULL) {
    perror("malloc");
    return EXIT_FAILURE;
  }

  printf("Starting memory stream, Press Ctrl-C to stop.\n");

  time_t start_time = time(NULL);

  while (duration == -1 || (time(NULL) - start_time) < duration) {
    for (long long i = 0; i < bytes; i++) {
      printf("Allocated for %lld\n ", i);
      memory[i] = 0;
    }
  }

  printf("Time elapsed. Freeing memory.\n");

  free(memory);

  return EXIT_SUCCESS;
}
