//Author: Ömer Alperen Kati
//Date: 05/04/2020

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

void countNumOfElements(ifstream* take, int* matrixDimension, double* mult) {
/*
This function counts the number of elements in Matrix A. It takes elements from the file one by one, and
each time increments "*matrixDimension" by 1. If this operation fails, it doesn't increment and breaks
the do-while loop. Finally, it closes the file.
*/	
	do {
		*take >> *mult; // Every time, as a formality, stores the element in "*mult"
		if(!take->fail()) { // Tests if the operation fails. If it fails, take->fail() returns 1.
			(*matrixDimension)++; // If it doesn't fail, "*matrixDimension" is incremented.			
		}
	} while(!take->fail());
	take->close(); // we close the file for now.	
}

int openFileAndCount(void (*countNumOfElements) (ifstream*, int*, double*),char* &fileName, int* matrixDimension, double * mult) {
	/*
	This function opens the file whose name is entered by user, and counts the number of elements in it.
	*/	
	ifstream take(fileName); // , and open it.
	if (!take.is_open()) { // If it can't opened
		system("pause"); // we pause the code, and
		cout << "file not found..."; // inform the user.
		return 0; // For this case, it returns 0 to function.
	} else { // if it is opened,
		countNumOfElements(&take, matrixDimension, mult); // we count the number of elements in this file to find the dimension of Matrix A.
		return 1; // And in order to inform that file is successfully opened, it returns 1.
	}
}

void makeMatrixA_2D(double** matrixA, int* matrixDimension, int* i) {
	/*
	This function is specialized to convert an array one dimensional to 2D before storing Matrix A in it.
	*/
	for(*i = 0; *i < *matrixDimension ; (*i)++) {
    	matrixA[*i] = new double[*matrixDimension];
	}		
}

void readMatrixA(char* fileName, int* i, int* j, int* matrixDimension, double** matrixA) {
	ifstream take1(fileName); // opening the file
	for(*i = 0 ; *i < *matrixDimension ; (*i)++) { // nested 2 for loops for locating each element of Matrix A to correct locations.
		for(*j = 0 ; *j < *matrixDimension ; (*j)++) {
			take1 >> matrixA[*i][*j];
		}
	}
	take1.close();	// closing the file again.
}

int printConditionNumbers(int* matrixDimension, double** matrixA) {
	/*
	This function prints the condition numbers at 1 and infinity of a 2x2 matrix by comparing the row and column sums.
	*/

	if(*matrixDimension == 2) {
		if((abs(matrixA[0][0])*abs(matrixA[1][1])-abs(matrixA[0][1])*abs(matrixA[1][0])) == 0) {
			return 0;
		}
		if(abs(matrixA[0][0]) + abs(matrixA[1][0]) >= abs(matrixA[0][1]) + abs(matrixA[1][1])) {
			if(abs(matrixA[0][0]) + abs(matrixA[0][1]) >= abs(matrixA[1][0]) + abs(matrixA[1][1])) {
				cout << "Condition number is " << (((abs(matrixA[0][0]) + abs(matrixA[1][0]))*(abs(matrixA[0][0]) + abs(matrixA[0][1])))/(abs(matrixA[0][0])*abs(matrixA[1][1])-abs(matrixA[0][1])*abs(matrixA[1][0]))) << endl;
			} else {
				cout << "Condition number is " << (((abs(matrixA[0][0]) + abs(matrixA[1][0]))*(abs(matrixA[1][0]) + abs(matrixA[1][1])))/(abs(matrixA[0][0])*abs(matrixA[1][1])-abs(matrixA[0][1])*abs(matrixA[1][0]))) << endl;
			}			
		} else {
			if(abs(matrixA[0][0]) + abs(matrixA[0][1]) >= abs(matrixA[1][0]) + abs(matrixA[1][1])) {
				cout << "Condition number is " << (((abs(matrixA[0][1]) + abs(matrixA[1][1]))*(abs(matrixA[0][0]) + abs(matrixA[0][1])))/(abs(matrixA[0][0])*abs(matrixA[1][1])-abs(matrixA[0][1])*abs(matrixA[1][0]))) << endl;
			} else {
				cout << "Condition number is " << (((abs(matrixA[0][1]) + abs(matrixA[1][1]))*(abs(matrixA[1][0]) + abs(matrixA[1][1])))/(abs(matrixA[0][0])*abs(matrixA[1][1])-abs(matrixA[0][1])*abs(matrixA[1][0]))) << endl;
			}
		}
	}
	return 0;	
}

void openAndReadvectorB(char* fileName, int* i, int* matrixDimension, double* vectorB) {
	/*
	This function opens the file, and allocates the elements in predeclared Matrix B.
	*/
	ifstream take2(fileName); // opens the file
	for(*i = 0 ; *i < *matrixDimension ; (*i)++) { // constructs vector B.
		take2 >> vectorB[*i];
	}
	take2.close(); //closes the file.
}

void convertToUpperTriangular(double* mult,int* i, int* j, int* m, int* matrixDimension, double** matrixA, double* vectorB) {
	/*
	This functions basicaly converts the primary matrix to upper triangular by doing row operations, and
	also applies the same row operations by using the corresponding pivot to the element ratios.
	*/
	for(*i = 0 ; *i < *matrixDimension ; (*i)++) {
		for(*j = (*matrixDimension)-1 ; *j > *i ; (*j)--) {
			*mult = matrixA[*j][*i] / matrixA[*i][*i]; // for each pair, we find the ratio of each pivot to the elements in the same columns.
				for(*m = 0 ; *m < *matrixDimension ; (*m)++) {
					matrixA[*j][*m] -= matrixA[*i][*m]*(*mult); // by using this ratio, we do row operation
				}
				vectorB[*j] -= vectorB[*i]*(*mult); // apply the same operation using the same ratio
		}
	}	
}

int checkSingularity(int* i, int* matrixDimension, double** matrixA) {
	/*
	This function checks the singularity of a *matrixDimension x *matrixDimension MatrixA
	*/
	for(*i = 0 ; *i < *matrixDimension ; (*i)++) {
		if( matrixA[*i][*i] == 0) { //With the help of for loop, this statement checks each pivot to decide whether Matrix A is singular or not.
			cout << "The matrix is singular."; // If singular, prints error message, and...
			return 1; // returns 1. We will use this one in the main function to terminate the program.
		}
	}
	return 0;// If it doesn't enter to if statement for every pivot element, it returns 1, so matrix is not singular.
}

void upperTriangularToDiagonal(int* i, int* j, int* matrixDimension, double* mult, double** matrixA, double* vectorB) {
	/*
	This function converts upper triangular matrix to diagonal matrix.
	*/
	for(*i = (*matrixDimension)-1 ; *i >= 0 ; (*i)--) { // By starting from the last pivot, and
		for(*j = (*i)-1 ; *j >= 0 ; (*j)--) { // for the each element in the same column,
			*mult = matrixA[*j][*i]/matrixA[*i][*i]; // we find the ratio of pivot to the elements,
			vectorB[*j] -= vectorB[*i]*(*mult); // and by using this ratio, we do back subtitution.			
			matrixA[*j][*i] = 0; // Finally, initialize the elements where back subtitution is just done to 0.
		}	
	}
}

void diagonalToIdentity(int* i, int* matrixDimension, double** matrixA, double* vectorB) {
	/*
	This function gets the solution for Ax = b by dividing each element of the matrix b 
	by corresponding values of the pivots.
	*/
	for( *i = 0 ; *i < *matrixDimension ; (*i)++) {
		vectorB[*i] /= matrixA[*i][*i];
		matrixA[*i][*i] = 1;
	}	
}

void printAndSaveTheSolution(int* i, int* matrixDimension, double* vectorB) {
	ofstream outputFile("x.txt");
	for(*i = 0 ; *i < *matrixDimension ; (*i)++) {
		cout << vectorB[*i] << endl;
		outputFile << vectorB[*i] << endl;
	}
	outputFile.close();	
}

int main(int argc, char* argv[]) {
	int* matrixDimension = new int; // declaration of the variable which will store the dimension of Matrix A.
	cout << argv[0];
//declaration of variables which will be used in for loops.
	int* i = new int;
	int* j = new int;
	int* m = new int;
//declaration of variables which will be used in for loops.	
	
	*matrixDimension = 0; // it is initialized to zero before the operation of counting # of elements in Matrix A.
	double* mult = new double; // this will be used as a multiplier while row operations and reductions are being done.
	char* fileName = new char[1]; // this is to store the names of the files going to be read.
	
	*i = openFileAndCount(countNumOfElements,argv[1], matrixDimension, mult); // we open the file of Matrix A, and count the number of elements in it.
	if(*i == 0) { //By the way, we return a value to notice whether opening is successful.
		return 0; // If it is not, program is terminated.
	}	
	
	*matrixDimension = sqrt(*matrixDimension); // finding the size of Matrix A by taking square root.
	double **matrixA = new double*[*matrixDimension]; // by using the size, we declare an array, and
	makeMatrixA_2D(matrixA, matrixDimension, i); // we convert this one dimensional array to a 2D one.

	readMatrixA(argv[1], i, j, matrixDimension, matrixA); // operation of reading and storing Matrix A.
	
	double* vectorB = new double[*matrixDimension]; // by using the same dimension, declaration of Matrix b.
	
	printConditionNumbers(matrixDimension, matrixA); // in case of having a 2x2 matrix, printing condition numbers.
	
	openAndReadvectorB(argv[2], i, matrixDimension, vectorB); // for Matrix b, opens the file, and reads and allocates the elements.

	convertToUpperTriangular(mult, i, j, m, matrixDimension, matrixA, vectorB); // by making row operations, getting an upper triangular matrix.

	if(checkSingularity(i, matrixDimension, matrixA) == 1) { // this if statement checks singularity, if so, terminates the program.
		return 0;
	}

	upperTriangularToDiagonal(i, j, matrixDimension, mult, matrixA, vectorB); // converts upper triangular matrixA to diagonal one, and applies the same row operations to vectorB.
	
	diagonalToIdentity(i, matrixDimension, matrixA, vectorB); // converts diagonal to identity matrix, and gets the final form of matrix b.

	printAndSaveTheSolution(i, matrixDimension, vectorB); // prints the elements of the solution in order, and at the same time saves it as a .txt file named "x.txt"
	
	for(*i = 0 ; *i < *matrixDimension ; (*i)++) {
		delete [] matrixA[*i];
 	}
 	delete [] vectorB;
	delete fileName, i, j, m, matrixDimension, mult;
	return 0;
}

//Author: Ömer Alperen Kati
//Date: 05/04/2020
