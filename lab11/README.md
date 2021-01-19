# OS Lab 11 - Semaphores, Mutex, Condition Variable - June 9th 2020
Laboratory 11 of the Operating Systems course of the master degree in Embedded System (Electronic Engineering) of Politecnico di Torino, academic year 2019/2020.<br/>

## Exercise 1
Create a multi-thread program that writes information in a shared file.
The main program creates an empty file whose name is provided by the user.
Then, it creates N threads (with N still specified by the user).

Each thread performs 100 times the following operations:
1. Open the file.
2. Read the last line of the file (each line contains a number).
3. Add 3 to the number.
4. Append the new number at the end of the file.
5. Close the file.

Make sure that steps from 1 to 5 are executed in an atomic way by the different processes.

Hint: fopen, fprintf and fscanf are the functions you are required to know in order to properly manage the file access.
Also remember that files accept three basic way of opening: reading, writing and append.
Choose accordingly.

## Exercise 2
Create a multi-thread program composed of 2 threads.
Each thread must simply print on the screen a message reporting its thread id.
The threads must be synchronized in such a way that messages are alternated on the screen, i.e., message from thread 1 always followed by message from thread 2.

## Exercise 3
Similarly to previous labs, write a multi-thread program that evaluates the following math series:

<p align="center">
<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Csum_%7Bi%3D0%7D%5E%7BN%7D+%5Cfrac%7B1%7D%7B2%5Ei%7D%0A" 
alt="\sum_{i=0}^{N} \frac{1}{2^i}
">

The main program receives the N value as input and creates the set of necessary threads.
Each thread evaluates a single 1/2<sup>i</sup> instance, where i is the index of creation (e.g., the thread 1 evaluates 1/2<sup>0</sup> , the thread 2 evaluates 1/2<sup>1</sup> and so on) and adds it directly to the final results.
Once all the threads complete their job, the main program displays the final result.
Use a mutex to protect shared memory locations: is there any critical section issue?

## Exercise 4
Write a multi-thread program that performs the following multiplication:

<p align="center">
<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Cprod_%7Bi%3D0%7D%5E%7BN%7D+x%5Ei%0A" 
alt="\prod_{i=0}^{N} x^i
">

The main program receives N and x values and let N+1 threads dealing with the power operation.
Force the threads to update the content of the multiplication.

Once all threads are done, display the final result.
Use a mutex to protect shared memory locations: is there any critical section issue?

## Exercise 5
Write the multi-thread program to search if a number N is a prime number
by checking if it is divisible by any number in the range [2, N/2].
The program receives the number N and the number P of threads to use as input.

The program must create P threads and assign to each of them a subset of possible divisors to test.
Each thread, then verifies if N is divisible by any of the assigned divisors.
The main program continuously checks the result of the generated threads.

Resorting to a proper usage of Conditional variables let the main program detect when the number is not prime as soon as possible; if so, it has to end all threads immediately.

Again, when compared with the previous implementation, is it the correct usage of a condition variable?

## Exercise 6
Write a program that creates 3 threads, displays their ID and prompt the user to choose which thread has to end.
Once the selected thread ends (and only at that time!), the list of remaining open threads ID has to be re-printed and the user has to choose a new one to end.

The main program communicates the end to threads using one or more Condition Variables. It ends when all threads terminate.

When compared with the previous implementation, is it the correct usage of a condition variable?

[//]: # (https://tex-image-link-generator.herokuapp.com/)
