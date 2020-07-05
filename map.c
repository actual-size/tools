#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 128
#define CMDSIZE 128
#define FUNCTION 1
#define ARG_START FUNCTION + 1

int main(int argc, char *argv[]) {
  char buf[BUFSIZE];
  FILE *fp;
  char *cmd;

  int i = 0;

  i = strlen(argv[FUNCTION]) + 1 + // room for a space between
      strlen(argv[ARG_START]);

  // add space for the null terminator
  cmd = (char *)malloc(i + 1);
  strcat(strcat(cmd, argv[FUNCTION]), " ");
  strcat(cmd, argv[ARG_START]);

  fp = popen(cmd, "r");

  if (fp == NULL) {
    printf("Error opening pipe!\n");
    return -1;
  }

  while (fgets(buf, BUFSIZE, fp) != NULL) {
    // Do whatever you want here...
    printf("%s", buf);
  }

  if (pclose(fp)) {
    printf("Command not found or exited with error status\n");
    return -1;
  }

  return 0;
}
