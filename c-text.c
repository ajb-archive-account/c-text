#include <termios.h>
// Terminal I/O interface
#include <unistd.h>
// Access to POSIX system

int main() {
  /* `main`, the default entry point for all c programs. When you `return` from
   * main(), the program exits and returns an int to the operating system. (A
   * return value of 0 indicates success). */
  /* Read 1 byte from standard input into variable `c` (and keep reading until
   * there are no bytes left to read). */
  /* `&& c !='q'` tell the terminal to kill the while loop when it 'hears' a 'q'
   * keypress. */
  /* `read()` returns the number of bytes it has read and will return 0 when
   * complete. */
  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q')
    ;
  return 0;
}
