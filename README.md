# BasicShell

A small POSIX-style shell loop for Unix-like systems: read a line, turn it into tokens, parse a simple pipeline structure, then run built-ins or `execvp` for everything else.

## What you need

- CMake 3.16 or newer
- A C++20 compiler (`g++`, `clang++`, MSVC with matching support)

The project assumes a typical Linux or WSL environment with standard headers (`unistd`, `sys/wait`).

## Build

From the repository root:

```bash
cmake -S . -B build
cmake --build build
```

The binary is `build/myshell`.

There is also `run-myshell.sh`, which deletes `build/`, re-runs CMake, builds, then starts the shell.

## Behaviour

Each input line is processed in order: lexer (`Lexer`), parser (`Parser` → `ParsedPipeline`), executor (`Executor`). The shell runs the first parsed stage through the built-in table or forks and execs.

Built-ins shipped in-tree: `cd`, `pwd`, `echo`, `ls` (minimal directory listing via `std::filesystem`), `help`, `exit`. Anything else goes through `$PATH` with `execvp`.

`|` is recognised in the grammar, but chaining commands with pipes is not implemented yet—the executor stops with an error if more than one stage is present. Redirections (`>`, `>>`) are not handled either.

## Exit status

`main` returns the shell’s last status, except when `exit [n]` is used, which uses the supplied code after range checks.

## Layout

Headers live under `include/`, sources under `src/`. Rough map: lexer and token types (`lexer.hpp`), parse output (`pipeline.hpp`), parser, executor, shell and fork/exec plumbing, builtins in `builtins.cpp`.
