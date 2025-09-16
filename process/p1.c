#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Illustration of non-determinism in fork()
 */
int main(int argc, char *argv[]) {

  printf("hello world (pid:%d)\n", (int)getpid());
  int rc = fork();

  if (rc < 0) {
    printf("Fork failed\n");
    exit(1);
  } else if (rc == 0) {
    printf("Hello I am a child with  (pid:%d)\n", (int)getpid());
  } else {
    printf("hello, I am parent of %d (pid:%d)\n", rc, (int)getpid());
  }
  return EXIT_SUCCESS;
}
