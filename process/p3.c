#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Spawing as a seperate process
 */
int main(int argc, char *argv[]) {
  printf("Hello world (pid: %d)\n", (int)getpid());
  int rc = fork();
  if (rc < 0) {
    printf("stderr, cannot create a fork\n");
  } else if (rc == 0) {

    printf("Hello I am a child process with (pid: %d)\n", (int)getpid());
    char *myargs[3];
    myargs[0] = strdup("wc");
    myargs[1] = strdup("p3.c");
    myargs[2] = NULL;
    execvp(myargs[0], myargs);
    printf("This should not happen.\n");
  } else {
    int rc_wait = wait(NULL);
    printf("Hello, I am a parent of %d (rc_wait: %d) (pid: %d)\n", rc,
           (int)rc_wait, (int)getpid());
  }
  return EXIT_SUCCESS;
}
