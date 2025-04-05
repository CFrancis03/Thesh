#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "thesh.h"

extern char *builtin_str[];
extern int (*builtin_func[]) (char **);

int thesh_launch(char **args) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("thesh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Fork failed
        perror("thesh");
    } else {
        // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int thesh_execute(char **args) {
    if (args[0] == NULL) return 1;

    for (int i = 0; i < thesh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return thesh_launch(args);
}
