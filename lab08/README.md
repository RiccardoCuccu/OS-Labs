# OS Lab 08 - Shared Memory POSIX, Message Queue - May 12th 2020
Laboratory 08 of the Operating Systems course of the master degree in Embedded System (Electronic Engineering) of Politecnico di Torino, academic year 2019/2020.<br/>

## Exercise 1
A program partitions the computation between 2 processes (a parent and a child):
- The parent reads from a file (called "number.dat") a list of integer numbers bigger than 0 separated by space and sends to the child.
- The child prints the received numbers.
- There are no repeated numbers.
- The "number.dat" ends with 0.

Use the shared memory in POSIX.

## Exercise 2
Write a modified Linux shell based on a client/server architecture.
The new shell must have the following characteristics:
- The client receives commands on the command line.
- Every command is sent to the server and executed in background.
- The shell terminates when the user enters the exit command.

Try to implement the client/server communication using Message Queues.
