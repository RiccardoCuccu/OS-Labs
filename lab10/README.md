# OS Lab 10 - Pipe, Signal - May 26th 2020
Laboratory 10 of the Operating Systems course of the master degree in Embedded System (Electronic Engineering) of Politecnico di Torino, academic year 2019/2020.<br/>

## Exercise 1
Use the previous program skeleton to evaluate the following Taylor expansion:

<p align="center">
<img src=
"https://render.githubusercontent.com/render/math?math=%5Cdisplaystyle+e%5Ex%3D1%2B%5Cfrac%7Bx%7D%7B1%21%7D%2B%5Cfrac%7Bx%5E2%7D%7B2%21%7D%2B%5Cfrac%7Bx%5E3%7D%7B3%21%7D%2B%5Ccdots%2B%5Cfrac%7Bx%5EN%7D%7BN%21%7D+%5Cqquad+-%5Cinfty+%3C+x+%3C+%2B%5Cinfty%0A" 
alt="e^x=1+\frac{x}{1!}+\frac{x^2}{2!}+\frac{x^3}{3!}+\cdots+\frac{x^N}{N!} \qquad -\infty < x < +\infty
">

The main process gets the x and the N values as input (x is a floating variable and N must be greater than 0) and performs the final sum.
Each fractional term (x<sup>i</sup>/i!) is evaluated by the i-th process and sent to the father for the final sum, using a pipe.

Advanced programming skills: try to improve the solution by not setting boundaries to N value, resorting to the malloc function for dynamic memory allocation and the free function to properly release the allocated memory at the end of the main process computation.

## Exercise 2
Write a program where the main process generates one child process.
The child picks a random number between 1 and 30 every 1 second, and writes it back into a pipe.
The father continuously reads the pipe and displays each read number.

Every 10 seconds let the child handle the SIGALARM in order to send a SIGUSR1 signal to the father.
Once received the signal, the father must generate a random number.
This number will be used in the time window between two consecutive SIGUSR1 signals as end number: if it is equal to one of the numbers read from the pipe, the father has to kill the child process and has to wait its end notification.

[//]: # (https://tex-image-link-generator.herokuapp.com/)
