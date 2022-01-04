#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 4096   /*max text line length*/

int main(void)
{
  fd_set rfds;
  struct timeval tv;
  int retval;
  int n;
  char buf[MAXLINE];

  /* Watch stdin (fd 0) to see when it has input. */
  FD_ZERO(&rfds);
  FD_SET(0, &rfds);

  /* Wait up to five seconds. */
  tv.tv_sec = 5;
  tv.tv_usec = 0;

  retval = select(1, &rfds, NULL, NULL, NULL);
  /* Don't rely on the value of tv now! */

  if (retval == -1)
    perror("select()");
  else if (retval) {
    while ((n = read(0, buf, MAXLINE)) > 0)
    {
      printf("Data is available now: ");
      puts(buf);
      memset(buf, '\0', sizeof(buf));
    }
  }
  /* FD_ISSET(0, &rfds) will be true. */
  else
    printf("No data within five seconds.\n");

  exit(EXIT_SUCCESS);
}