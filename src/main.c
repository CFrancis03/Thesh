// This is (The sh)ell a simple unix shell written in c
// By Colton Francis



// This project is based off the article https://brennan.io/2015/01/16/write-a-shell-in-c/
// I hope to improve upon this starter code and make something of my own




#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Declarations of builtin functions
int thesh_cd(char **args);
int thesh_help(char **args);
int thesh_exit(char **args);


// The strings that call the builtin functions
char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

// Mapping the strings to their particular function
int (*builtin_func[]) (char **) = {
  &thesh_cd,
  &thesh_help,
  &thesh_exit
};

// Returns the number of builtins for later printing
int thesh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}


//Implementation of our builtin functions



// Implementing cd (changes the current working directory)
int thesh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "thesh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("thesh");
    }
  }
  return 1;
}



// Implementing help(explains how to use our shell)
int thesh_help(char **args)
{
  int i;
  printf("(The sh)ell - by Colton Francis\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < thesh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

// Implementing the exit command()
int thesh_exit(char **args)
{
  return 0;
}


// Launch a program and wait for it to return
int thesh_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("thesh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("thesh");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

// Executes the command entered
int thesh_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < thesh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return thesh_launch(args);
}

#define THESH_RL_BUFSIZE 1024


// Reads commands form stdin
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
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
	bufsize += THESH_RL_BUFSIZE;
        fprintf(stderr, "thesh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
}

#define THESH_TOK_BUFSIZE 64
#define THESH_TOK_DELIM " \t\r\n\a" //tokenizes each line read from stdin 
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
    tokens[position] = token;
    position++;

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

// Loops while status getting args from stdin
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

int main(int argc, char **argv)
{
  // Load config files, if any.

  // Run command loop.
  thesh_loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}
