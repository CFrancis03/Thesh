#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "thesh.h"

#define THESH_RL_BUFSIZE 1024
char *thesh_read_line(void)
{
  int bufsize = THESH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "thesh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    c = getchar();

    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    if (position >= bufsize) {
      bufsize += THESH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "thesh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

#define THESH_TOK_BUFSIZE 64
#define THESH_TOK_DELIM " \t\r\n\a"
char **thesh_split_line(char *line)
{
  int bufsize = THESH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "thesh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, THESH_TOK_DELIM);
  while (token != NULL) {
    tokens[position++] = token;

    if (position >= bufsize) {
      bufsize += THESH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "thesh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, THESH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

void thesh_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = thesh_read_line();
    args = thesh_split_line(line);
    status = thesh_execute(args);

    free(line);
    free(args);
  } while (status);
}

