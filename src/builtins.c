#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "thesh.h"

char *builtin_str[] = {
  "cd",
  "help",
  "exit",
  "echo"
};

int (*builtin_func[]) (char **) = {
  &thesh_cd,
  &thesh_help,
  &thesh_exit,
  &thesh_echo
};

int thesh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

int thesh_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "thesh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("thesh");
    }
  }
  return 1;
}

int thesh_help(char **args) {
  printf("(The sh)ell - by Colton Francis\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");
  for (int i = 0; i < thesh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }
  printf("Use the man command for information on other programs.\n");
  return 1;
}

int thesh_exit(char **args) {
  return 0;
}



int thesh_echo(char **args) {
    for (int i = 1; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
    return 1;
}


