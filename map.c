#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 128
#define CMDSIZE 128
#define FUNCTION 1
#define FIRST_ARG 2

int exec_function(char *, char *);

int main(int argc, char *argv[]) {
  int return_code = 0;

  for (int i = 0; i < argc - FIRST_ARG; i++) {
    return_code = exec_function(argv[FUNCTION], argv[i + FIRST_ARG]);
    if (return_code != 0) {
      return return_code;
    }
  };

  return 0;
}

int exec_function(char *func_name, char *arg) {
  char buf[BUFSIZE];
  FILE *fp;
  char *cmd;

  int i = 0;

  i = strlen(func_name) + 1 + // leave memory for a space between
      strlen(arg);

  // add memory for the null terminator
  cmd = (char *)malloc(i + 1);
  strcat(strcat(cmd, func_name), " ");
  strcat(cmd, arg);

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
