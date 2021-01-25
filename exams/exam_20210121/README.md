# Exam of 21.01.2021
Exam of the Operating Systems course of the master degree in Embedded System (Electronic Engineering) of Politecnico di Torino.

## Exam Text
Write a multi-thread program designed to compute the **compatibility** of a DNA sequence with a pattern of bases.

The DNA is a string composed of a sequence of a maximum of 50,000 characters in the following set: {A, C, G, T}. Each character indicates one of the four bases composing a DNA strand: adenine (A), cytosine (C), guanine (G), or thymine (T).
The string is saved in a file whose name is provided to the program using the command line.

The program also receives on the command line a pattern which is a second string of a maximum of 30 characters indicating a sequence o bases also coded with the same four letters used for the DNA {A, C, G, T}.

Computing the DNA compatibility means counting how many times the pattern is "approximatively" contained in the DNA by matching the pattern in all possible positions of the DNA. Approximatively means that not all letters of the pattern must match. N mismatches are tolerated, where N is an integer parameter provided on the command line.

As an example let's consider the following DNA string: "AACTGTTTACATAGACTAA".

If the program receives "ACT" as pattern and N is equal to 1, the DNA compatibility is equal to 3 with the three matches in bold in the following string "A**ACT**GTTT**ACA**TAG**ACT**AA".

Write a multi-thread implementation of the above mentioned program where the matching and counting tasks are parallelized.
The program receives on the command line as 4th parameter the number X of matching threads that can be executed.
Each thread has the task of matching the pattern with a single position of the DNA.
In case of approximate matching, the thread must update a shared counter of the number of matches.

The main thread distributes the work among the X matching threads and prints the final compatibility when all DNA positions have been analyzed.
