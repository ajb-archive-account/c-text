#include <stdlib.h>
#include <termios.h>
// Terminal I/O interface
#include <unistd.h>
// Access to POSIX system

struct termios orig_termios;

void disableRawMode() {
  /* Save a copy of teh termios original state in `&orig_termios` and use
   * `tcsetattr()` to reapply it on close.
   * `TCSAFLUSH` will clear leftover input from the shell on exit. */

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
  /* Set terminal attributes, modify, pass new attributes back out to terminal.
   * TCSAFLUSH specifies when to apply changes */

  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);

  struct termios raw = orig_termios;

  tcgetattr(STDIN_FILENO, &raw);

  raw.c_lflag &= ~(ECHO);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
  /* Read 1 byte from standard input into variable `c` (and keep reading until
   * there are no bytes left to read).
   * `&& c !='q'` tell the terminal to kill the while loop when it 'hears' a 'q'
   * keypress.
   * `read()` returns the number of bytes it has read and will return 0 when
   * complete. */

  enableRawMode();

  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q')
    ;
  return 0;
}
