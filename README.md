# thesh — A Simple Custom Shell

Welcome to **thesh**, a lightweight custom shell written in C. This project is a minimalist command-line interpreter designed for educational purposes. It demonstrates how to build basic shell functionality, including built-in commands, user input parsing, and system command execution.

## Features

- Built-in commands:
  - `cd` – Change the current working directory
  - `help` – Display information about the shell
  - `exit` – Exit the shell
  - `echo` – Print arguments to the terminal
- Executes external system commands (e.g., `ls`, `pwd`, etc.)
- Basic error handling
- Clean and readable codebase

## Getting Started

### Prerequisites

- GCC or any C compiler
- Unix-like environment (Linux, macOS, or WSL)

### Compilation

To compile the shell:

```bash
gcc -o thesh main.c builtins.c -Wall

