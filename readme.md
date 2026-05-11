*This project has been created as part of the 42 curriculum by ttiprez, afournie*

# Minishell

![result](./correction.png)

## Description

Minishell is a minimal command-line interpreter (shell) developed in C, inspired by the behavior of **bash**. The goal of this project is to gain a deep understanding of the internal workings of a Unix shell: reading user input, lexical and syntactic analysis of commands, process management, redirections and pipes, and the implementation of built-in commands (builtins).

The shell supports:

- An **interactive prompt** with history management (via `readline`)
- **Tokenization** and **parsing** of command lines
- **Expansion** of environment variables (`$VAR`, `$?`) and the tilde (`~`)
- **Redirections**: `<`, `>`, `>>`, `<<` (heredoc)
- **Pipes** (`|`) for chaining multiple commands
- **Single and double quotes** with correct quote state handling
- **Signal handling** (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- A set of **built-in commands**: `cd`, `echo`, `pwd`, `env`, `export`, `unset`, `exit`

---

## Instructions

### Prerequisites

- A **Linux** system
- `cc` or `clang`
- The **readline** library (`libreadline-dev` on Debian/Ubuntu)
- **libft** (included in the project)

### Compilation

```bash
make
```

The `Makefile` compiles all source files and generates the `minishell` executable.

```bash
# Remove object files
make clean

# Remove object files and the executable
make fclean

# Recompile from scratch
make re
```

### Running

```bash
./minishell
```

The shell starts and displays an interactive prompt. It inherits environment variables from the parent process.

### Usage Examples

```bash
# Basic commands
minishell$ echo "Hello, World!"
minishell$ pwd
minishell$ ls -la | grep ".c" > c_files.txt

# Redirections
minishell$ cat < input.txt >> output.txt
minishell$ cat << EOF
> heredoc text
> EOF

# Environment variables
minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
minishell$ unset MY_VAR

# Navigation
minishell$ cd ~/projects
minishell$ cd -

# Exit
minishell$ exit
```

---

## Project Architecture

The project is structured around several modules:

| Module | Role |
|--------|------|
| **Lexer** | Tokenizes the command line into typed tokens (WORD, PIPE, INPUT, OUTPUT, HEREDOC, APPEND) |
| **Parser** | Builds the linked list of `t_cmd` from tokens, with syntax checking |
| **Expander** | Expands environment variables, `$?`, and the tilde `~` |
| **Executor (pipex)** | Manages pipes, forks, redirections, and command execution via `execve` |
| **Builtins** | Implements `cd`, `echo`, `pwd`, `env`, `export`, `unset`, `exit` |
| **Signals** | Handles `SIGINT`, `SIGQUIT` depending on context (prompt, execution, heredoc) |
| **Heredoc** | Pre-processes heredocs into temporary files before execution |

---

## Resources

### Official Documentation & References

- [Bash Manual (GNU)](https://www.gnu.org/software/bash/manual/bash.html) — primary reference for expected shell behavior
- [Readline Manual](https://tiswww.case.edu/php/chet/readline/rltop.html) — readline library documentation
- [Linux man pages: `fork(2)`, `execve(2)`, `pipe(2)`, `waitpid(2)`, `dup2(2)`, `signal(2)`](https://man7.org/linux/man-pages/) — system calls used in the project
- [Write a Shell in C — Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/) — introductory tutorial on writing a shell in C

### Use of AI

AI was used in this project for the following tasks:

- **Debugging**: help identifying memory leaks, segmentation faults, and unexpected behavior during test runs
- **Understanding system calls**: clarification of the behavior of `dup2`, `waitpid` (options `WIFEXITED`, `WIFSIGNALED`), and signal handling in a multi-process context

> AI was not used to generate source code submitted directly in the project.
