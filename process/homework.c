#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Write a program that calls fork(). Before calling fork(), have the
 * main process access a variable (e.g., x) and set its value to some-
 * thing (e.g., 100). What value is the variable in the child process?
 * What happens to the variable when both the child and parent change
 * the value of x?
 */
void q1() {
  int num;
  num = 100;
  printf("Num before fork %d\n", num);
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "Fork failed");
  } else if (rc == 0) {
    printf("Children initial value of num %d\n", num);
    num = 10;
    printf("Children after settting value of num %d\n", num);
  } else {
    printf("Inside parent \n");
    wait(NULL);
    printf("Inside the parent process %d\n", num);
  }
}

/**
 * Write a program that opens a file (with the open() system call)
 * and then calls fork() to create a new process. Can both the child
 * and parent access the file descriptor returned by open()? What
 * happens when they are writing to the file concurrently, i.e., at the
 * same time?
 */
void q2() {

  FILE *fd = fopen("file.txt", "r+");
  char character;

  if (fd == NULL) {
    fprintf(stderr, "Failed to open file\n");
    exit(1);
  }

  printf("In parent process, \n");
  while ((character = fgetc(fd)) != EOF) {
    printf("%c \n", character);
  }

  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "Fork failed \n");
  } else if (rc == 0) {
    printf("In child process\n");
    while ((character = fgetc(fd)) != EOF) {
      printf("%c \n", character);
    }
  } else {
    printf("Inside parent process \n");
    wait(NULL);
  }
  fclose(fd);
}

/**
 * Write another program using fork(). The child process should
 * print “hello”; the parent process should print “goodbye”. You should
 * try to ensure that the child process always prints first; can you do
 * this without calling wait() in the parent?
 */
void q3() {
  int p[2];

  if (pipe(p) < 0) {
    fprintf(stderr, "Pipe failed \n");
  }

  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "Fork failed \n");
  } else if (rc == 0) {
    printf("Hello \n");
    write(p[1], "x", 1);
    close(p[1]);
  } else {
    char buffer[1];
    read(p[0], buffer, 1);
    printf("Goodbye! \n");
    close(p[0]);
  }
}

#define READ_END 0
#define WRITE_END 1
#define BUFFER_SIZE 4096

/**
 * Write a program that calls fork() and then calls some form of
 * exec() to run the program /bin/ls. See if you can try all of the
 * variants of exec(), including (on Linux) execl(), execle(),
 * execlp(), execv(), execvp(), and execvpe(). Why do
 * you think there are so many variants of the same basic call?
 */
void q4(void) {
  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "Fail to create fork. \n");
  } else if (rc == 0) {
    printf("Child process with pid: %d\n", (int)getpid());
    char *binaryPath = "/bin/ls";
    char *args[] = {"ls", "-l", "-h", NULL};
    char *env[] = {"MY_VAR=hello", NULL};

    execle(binaryPath, "ls", "-l", "-h", NULL, env);

    printf("This should not be here.\n");

  } else {
    printf("Parent process with pid: %d\n", (int)getpid());
    wait(NULL);
  }
}

/*
 * Now write a program that uses wait() to wait for the child process
 * to finish in the parent. What does wait() return? What happens if
 * you use wait()  or waitpid() in the child?
 */
void q5(void) {
  int child_pid;
  int stat;
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "Error creating fork \n");
  } else if (rc == 0) {
    int i = 10;
    child_pid = getpid();
    printf("child_pid: %d\n", child_pid);
    while (i > 0) {
      printf("I is %d\n", i);
      i--;
    }
  } else {
    int pid = waitpid(child_pid, &stat, 0);
    printf("Process id %d\n", pid);
  }
}

/**
 * Write a program that creates a child process, and then in the child
 * closes standard output (STDOUT FILENO). What happens if the child
 * calls printf() to print some output after closing the descriptor?
 */
void q7(void) {
  int rc = fork();
  if (rc == 0) {
    const char *message = "Before close. \n";
    write(STDOUT_FILENO, message, strlen(message));
    close(STDOUT_FILENO);
    printf("After close. \n");
  } else {
    wait(NULL);
  }
}

/*
 * Write a program that creates two children, and connects the stan-
 * dard output of one to the standard input of the other, using the
 * pipe() system call.
 */
void q8(void) {
  int pd[2];
  int pd_s = pipe(pd);
  if (pd_s < 0) {
    fprintf(stderr, "Error creating pipe. \n");
  }
  int rc1 = fork();
  if (rc1 == 0) {
    dup2(pd[1], STDOUT_FILENO);
    close(pd[0]);
    close(pd[1]);

    char *args[] = {"ls", "-l", NULL};
    execvp(args[0], args);
    perror("Error exec ls");
  }

  int rc2 = fork();
  if (rc2 == 0) {
    dup2(pd[0], STDIN_FILENO);
    close(pd[0]);
    close(pd[1]);

    char *args[] = {"wc", "-l", NULL};
    execvp(args[0], args);
    perror("Error exec wc");
  }

  close(pd[0]);
  close(pd[1]);

  waitpid(rc1, NULL, 0);
  waitpid(rc2, NULL, 0);
}

int main(int argc, char *argv[]) { q8(); }
