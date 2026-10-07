# ShellForge

ShellForge is a Unix-like shell developed as part of the Operating Systems and Systems Programming Project-Based Learning course.

## Week 10 – Threads and Concurrency using POSIX Threads

### Features

- POSIX thread support using pthread.h
- Background monitoring thread
- Thread creation using pthread_create()
- Thread synchronization using pthread_join()
- Mutex synchronization using pthread_mutex_t
- Critical section protection
- Shared resource synchronization demonstration
- Thread synchronization test using the threadtest built-in command

### Thread Synchronization

ShellForge includes a background monitoring thread that periodically displays:

[Monitor] ShellForge Running...

A separate thread demonstration creates two worker threads that safely update a shared counter using a mutex.

Running:

threadtest

produces:

Running thread synchronization test...
[Thread Demo] Final counter: 2000

This demonstrates thread creation, mutex synchronization, critical-section protection, and pthread_join().

## Existing Shell Features

- Dynamic command input
- Built-in commands
- External command execution
- Process creation using fork()
- Command execution using execvp()
- Process synchronization using waitpid()
- Input/output redirection
- Pipes
- Signal handling
- DevOps automation commands
- Git status integration
- POSIX thread support

## Built-in Commands

cd <directory>   Change directory
pwd              Show current directory
help             Show help
clear            Clear terminal
build            Build ShellForge
run              Run ShellForge
clean            Clean build files
gitstatus        Show Git status
threadtest       Test thread synchronization
exit             Exit ShellForge

## Project Structure

DevOps-Mini-Shell/
├── src/
│   ├── main.c
│   ├── input.c
│   ├── parser.c
│   ├── process.c
│   ├── builtin.c
│   ├── signals.c
│   └── thread.c
├── include/
│   ├── input.h
│   ├── parser.h
│   ├── process.h
│   ├── builtin.h
│   ├── signals.h
│   └── thread.h
├── docs/
├── tests/
├── screenshots/
├── bin/
├── Makefile
├── .gitignore
└── README.md

## Build and Run

make clean
make
make run

## Thread Synchronization Test

Inside ShellForge:

threadtest

Expected output:

Running thread synchronization test...
[Thread Demo] Final counter: 2000
