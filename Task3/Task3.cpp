#include <iostream>
#include "Class.h"

int main()
{
	double** MatrixElements = new double* [3];
	for (int i = 0; i < 3; ++i)
	{
		MatrixElements[i] = new double[3];
	}
	MatrixElements[0][0] = 2;
	MatrixElements[0][1] = 4;
	MatrixElements[0][2] = 3;
	MatrixElements[1][0] = 5;
	MatrixElements[1][1] = 7;
	MatrixElements[1][2] = 8;
	MatrixElements[2][0] = 6;
	MatrixElements[2][1] = 9;
	MatrixElements[2][2] = 1;
	Matrix M((const double**)MatrixElements, 3, 3);
	return 0;
}