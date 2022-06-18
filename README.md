# Linear-Equation-Solver
//Author: Ömer Alperen Katı
//Date: 05/04/2020

LINEAR EQUATION SOLVER

-This program implements the Gaussian elimination algorithm with partial pivoting together 
with backward substitution to solve Ax = b, where A is an n⇥n square matrix.

-It reads the names of the input files for matrix A and vector b consecutively, and output
the solution x in the correct order as a .txt file called "x.txt".

-This program was written considering that given matrix always will be a square matrix, and size
of it always matches with that of vector b, so make sure that matrix A and vector b are in an
appropriate form to be solved.

-At the first version of the program, matrices were stored in arrays of type float. But then,
it was noticed that in the cases of equations having ranks over than 10000, error is very big.
As a result of that, it was decided to use double instead of float as the type of arrays.

HOW TO RUN THE PROGRAM USING CMD

-Firstly, open cmd. Then adjust the directory of cmd as where all your input files and main.cpp
file are.

-Secondly, if you are in the correct directory, write "g++ source.cpp -o source.exe" to generate
.exe file, and press enter.
Example: C:\Users\(!!username here!!)\Desktop\EE242_Project1>g++ source.cpp -o source.exe

-After that, write "source.exe (Insert name of the matrix A here) (Insert name of the vector b here)",
and press enter to run the program.
Example: C:\Users\(!!username here!!)\Desktop\EE242_Project1>source.exe A.txt b.txt


EXAMPLE FOR COMMENTING ON CONDITION NUMBERS
-When we use following vector b samples solving for x by taking matrix A constant like below.
We get the following condition number and solutions.

A:		Condition #: 4004
1.000 1.000
1.000 1.001

b1:		b2:
2.000		2.000
2.000		2.001

x1:		x2:
2		1
0		1

It can be said that when the condition # of a matrix is very big, a small change in vector b
can cause comparatively large changes in solution x. In this case, even if the change is 1 of
1000, the change in output is hundred percent.

//Author: Ömer Alperen Katı
//Date: 05/04/2020
