## Shell Concepts

**Fundamentals concepts in shell development**

### Child and Parent Processes

**PID & PPID**

---

#### PID

 A `process` is an instance of an executing program, that has a **unique process ID**. This process ID is used by many functions and system calls to interact with and manipulate processes. In order to retrieve the current process’ ID, you can use the system call `getpid`. (`man 2 getpid`).

- [x] [0-get_pid.c](pid.c) - gets a child process ID using the `getpid` system call. Everytime the progrma is executed a new instance is created with a different  ID.

---

#### PPID

Each process has a `parent`: the process that created it. It is possible to get the PID of a parent process by using the `getppid` system call (`man 2 getppid`), from within the child process.

- [x] [1-get_ppid.c](ppid.c) - gets the parent process id from within the child process using the `getppid` system call.


---

### commandline arguments

