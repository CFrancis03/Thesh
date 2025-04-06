#ifndef THESH_H
#define THESH_H

// Builtin functions
int thesh_cd(char **args);
int thesh_help(char **args);
int thesh_exit(char **args);
int thesh_echo(char **args);
int thesh_date(char **args);
int thesh_num_builtins(void);

// Execution functions
int thesh_launch(char **args);
int thesh_execute(char **args);

// Input functions
char *thesh_read_line(void);
char **thesh_split_line(char *line);

// Main loop
void thesh_loop(void);

#endif
