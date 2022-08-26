## Shell Concepts

**Fundamentals concepts in shell development**

### Child and Parent Processes

**PID & PPID**

---
 A `process` is an instance of an executing program, that has a **unique process ID**. This process ID is used by many functions and system calls to interact with and manipulate processes. In order to retrieve the current process’ ID, you can use the system call `getpid`. (`man 2 getpid`).

- [x] [Example.c](pid.c) - gets a child process ID using the `getpid` system call.
