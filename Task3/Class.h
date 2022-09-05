#pragma once
#include <iostream>
#include <string>
#include <limits.h>

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
	const double** GetMatrix() const;
	void SetMatrixElem(const double Elem, const int LinesPosition, const int ColumnsPosition);
	void SetMatrix(double** Matr);
	const int GetLines() const;
	void SetLines(const int Number);
	const int GetColumns() const;
	void SetColumns(const int Number);

	friend const Matrix operator+ (const Matrix& Left, const Matrix& Right);
	friend const Matrix operator+ (const Matrix& Left, const int Number);
	friend const Matrix operator+ (const Matrix& Left, const char* Str);
	friend const Matrix operator- (const Matrix& Left, const Matrix& Right);
	friend const Matrix operator- (const Matrix& Left, const int Number);
	friend const Matrix operator- (const Matrix& Left, const char* Str);
	friend const Matrix operator* (const Matrix& Left, const Matrix& Right); 
	friend const Matrix operator* (const Matrix& Left, const int Number);
	friend const Matrix operator* (const Matrix& Left, const char* Str);
	friend const Matrix operator/ (const Matrix& Left, const Matrix& Right);
	friend const Matrix operator/ (const Matrix& Left, const int Number);
	friend const Matrix operator/ (const Matrix& Left, const char* Str);

	const Matrix& operator+=(const Matrix& AnotherMatrix);
	const Matrix& operator+=(const int Number);
	const Matrix& operator-=(const Matrix& AnotherMatrix);
	const Matrix& operator-=(const int Number);
	const Matrix& operator*=(const Matrix& AnotherMatrix);
	const Matrix& operator*=(const int Number);
	const Matrix& operator/=(const Matrix& AnotherMatrix);
	const Matrix& operator/=(const int Number);

	friend const bool operator<(const Matrix& Left, const Matrix& Right);
	friend const bool operator>(const Matrix& Left, const Matrix& Right);
	friend const bool operator>=(const Matrix& Left, const Matrix& Right);
	friend const bool operator<=(const Matrix& Left, const Matrix& Right);
	friend const bool operator==(const Matrix& Left, const Matrix& Right);
	friend const bool operator!=(const Matrix& Left, const Matrix& Right);

	void MatrixTransponation();
};

const Matrix& CreateMatrix(const double** AnotherMatrix, const int AnotherMatrixLines, const int AnotherMatrixColumns);
const double FindDeterminant(const Matrix& M);