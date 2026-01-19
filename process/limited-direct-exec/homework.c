#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

  time_t current_time_seconds = time(NULL);

  struct tm *local_time_struct = localtime(&current_time_seconds);

  printf("Current time: %02d:%02d:%02d\n", local_time_struct->tm_hour,
         local_time_struct->tm_min, local_time_struct->tm_sec);

  return EXIT_SUCCESS;
}
