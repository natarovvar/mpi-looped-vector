# Looped vector
The task implements parallel calculations on different processors

## Problem statement
Pass a vector of 100 elements along the ring, let each process iterate through the elements in the array with a number multiple of its number and calculate the number of even ones. The resulting result is pressed on the process with the number 0, the process with the number 0 forms an array from the received values (the element number corresponds to the process number)

## Scheme

 <img src="https://i.imgur.com/4uRqYBV.jpg" width="750" />

 
## Technology Stack
* C++20
* MPI 4.0


