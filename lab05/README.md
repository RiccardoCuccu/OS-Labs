# OS Lab 05 - Threads - April 21th 2020
Laboratory 05 of the Operating Systems course of the master degree in Embedded System (Electronic Engineering) of Politecnico di Torino, academic year 2019/2020.<br/>

## Exercise 1
Write a multi-thread program that creates two threads.
When a thread is created the program prints the message "first/second thread created".
When the thread execution starts the thread prints the message "first/second thread processing", then the thread waits for 5 seconds and finally it prints the message "first/second thread terminates".

## Exercise 2
Write a multi-thread program that defines a string of 20 characters, instantiates a thread and then starts a loop in which the user is required to enter a string.
The thread scans every second the content of the string. Whenever the string is equal to "house" or "casa" the thread prints the message "house detected".
If the string contains the string "exit" the program must terminate.
