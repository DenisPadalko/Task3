#pragma once
#include <iostream>
#include <string>

using namespace std;
class Matrix
{
private:
	double** MatrixElements;
	int Columns;
	int Lines;
public:
	Matrix();
	Matrix(const double** AnotherMatrix, const int AnotherMatrixLines, const int AnotherMatrixColumns);
	Matrix(const Matrix& AnotherMatrix);
	Matrix(Matrix&& AnotherMatrix);
	Matrix(const int Number);
	Matrix(const char* AnotherMatrix);
	~Matrix();
	Matrix& operator=(const Matrix& AnotherMatrix);
	Matrix& operator=(Matrix&& AnotherMatrix);
	void ShowMatrix() const;
	void ConvertMatrixToString(string& Str) const;
};

const Matrix& CreateMatrix(const double** AnotherMatrix, const int AnotherMatrixLines, const int AnotherMatrixColumns);