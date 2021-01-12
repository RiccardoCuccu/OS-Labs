# OS Lab 04 - `system()` and `exec()` - April 14th 2020
Laboratory 04 of the Operating Systems course of the master degree in Embedded System (Electronic Engineering) of Politecnico di Torino, academic year 2019/2020.<br/>

## Exercise 1
Create a Linux shell. It must have the following characteristic:
- It receives commands on the command line like the standard Linux shell (the command cannot be split on different lines).
- Every command is executed in background in a dedicated child process
- The output of the command is not written on the screen but is saved in a file named \<PID\>.log where \<PID\> is the process identifier of the child process executing the command.
- The shell terminates when the user enters the exit command.

## Exercise 2
Write a C program that launches the find command with specified user path as input argument.

## Exercise 3
Write a C program that performs the following operations:
- Creates a child process that generates a file called random.txt containing 100 random numbers that are separated by the space character.
- When the file is created the program must instantiate three sub processes:
  - The first process must execute the Linux command `wc –m` to print on the screen the number of bytes of the file.
  - The second process must execute the Linux command `wc –w` to count the number of words in the file
  - The third process must execute a custom program (to be programmed by your own) designed to compute the average of all generated number.
- The main process terminates when all three children terminate.
