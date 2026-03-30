
#include <kernel/tty.h>

void kernel_main(void) {
  terminal_initialize();

  for (char c = 'A'; c <= 'Z'; c++) {
    char *ca = &c;
    terminal_writestring(ca);
    terminal_writestring("\n");
  }
}
