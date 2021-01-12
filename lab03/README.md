# OS Lab 03 - `wait()`, `waitpid()`, `exit()` - April 7th 2020
Laboratory 03 of the Operating Systems course of the master degree in Embedded System (Electronic Engineering) of Politecnico di Torino, academic year 2019/2020.<br/>

## Exercise 1
Write a C program that creates 2 child processes with the following characteristics:
- the child processes wait for 5 seconds and terminate
- the parent process terminates when the second created child terminates.

## Exercise 2
Write a C program that creates 6 child processes with the following characteristics:
- all 6 child processes are always running
- first 3 processes continuously generate a random number and print it on the standard output
- second 3 processes generate 50 random numbers and print it and its square on the standard output
- every time a child process terminates it should be replaced by a new child of the same type.

## Exercise 3
Write a multi-process program that evaluates the following math series:

<p align="center">
<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+%5Csum_%7Bi%3D0%7D%5E%7Bn%7D+2%5Ei%0A" 
alt="\sum_{i=0}^{n} 2^i">
</p>

The main process receives the n value as input (set max value for n to 5) and performs the final sum. Each 2<sup>i</sup> is evaluated by the i-th process and sent to the father for the final sum.

Hint: remember that you cannot share variables among processes right now but you can always send back some value by the exit status.

[//]: # (https://tex-image-link-generator.herokuapp.com/)
