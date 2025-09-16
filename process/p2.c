#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Waiting for child process 
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
    int rc_wait = wait(NULL);
    printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait,
           (int)getpid());
  }
  return EXIT_SUCCESS;
}
