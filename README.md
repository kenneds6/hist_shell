# hist_shell
Unix-like Shell with built in command that lists history of commands


This is a project from the textbook Operating Systems Concepts (9th edition) by ABRAHAM SILBERSCHATZ PETER BAER GALVIN GREG GAGNE

This project was assigned as part of a final project for my Operating Systems course (EECE 6029) taught at the University of Cincinnati
Fall 2016

The specifications for the project are as follows:

"Project 1—UNIX Shell and History Feature
This project consists of designing a C program to serve as a shell interface
that accepts user commands and then executes each command in a separate
process. This project can be completed on any Linux, UNIX, or Mac OS X system.
A shell interface gives the user a prompt, after which the next command
is entered. The example below illustrates the prompt osh> and the user’s
next command: cat prog.c. (This command displays the file prog.c on the
terminal using the UNIX cat command.)
osh> cat prog.c
One technique for implementing a shell interface is to have the parent process
first read what the user enters on the command line (in this case, cat
prog.c), and then create a separate child process that performs the command.
Unless otherwise specified, the parent process waits for the child to exit
before continuing. This is similar in functionality to the new process creation
illustrated in Figure 3.10. However, UNIX shells typically also allow the child
process to run in the background, or concurrently. To accomplish this, we add
an ampersand (&) at the end of the command. Thus, if we rewrite the above
command as
osh> cat prog.c &
the parent and child processes will run concurrently.
The separate child process is created using the fork() system call, and the
user’s command is executed using one of the system calls in the exec() family
(as described in Section 3.3.1).
A C program that provides the general operations of a command-line shell
is supplied in Figure 3.36. The main() function presents the prompt osh->
and outlines the steps to be taken after input from the user has been read. The
main() function continually loops as long as should run equals 1; when the
user enters exit at the prompt, your program will set should run to 0 and
terminate.
This project is organized into two parts: (1) creating the child process and
executing the command in the child, and (2) modifying the shell to allow a
history feature." (Gagne 157)
