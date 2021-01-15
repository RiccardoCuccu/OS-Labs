# OS Lab 07 - Shared memory - May 5th 2020
Laboratory 07 of the Operating Systems course of the master degree in Embedded System (Electronic Engineering) of Politecnico di Torino, academic year 2019/2020.<br/>

## Exercise 1
Write a multi-process program that evaluates the following math series:

<p align="center">
<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Csum_%7Bi%3D0%7D%5E%7Bn%7D+2%5Ei%0A" 
alt="\sum_{i=0}^{n} x^i">
</p>

The main program receives the x and n values as input (set max value for n to 5) and creates the set of necessary processes.
Each process evaluates a single x<sup>i</sup> instance, referring to its index of creation (e.g., process 1 evaluates x<sup>0</sup>, process 2 evaluates x<sup>1</sup>, and so on).
Impose x being a floating-point value and let only the father compute the final results.
Once all the processes complete their job, the main program displays the final result.
Use the shared memory facilities to exchange each child process result with the father.

## Exercise 2
Write a modified Linux shell based on a client/server architecture.
The new shell must have the following characteristics:
- The client receives commands on the command line.
- Every command is sent to the server and executed in background.
- The shell terminates when the user enters the `exit` command.

Try to implement the client/server communication using shared memory.

[//]: # (https://tex-image-link-generator.herokuapp.com/)
