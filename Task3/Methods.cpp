#include "Class.h"

Matrix::Matrix()
{
	Lines = 3;
	Columns = 3;
	MatrixElements = new double* [Lines];
	for (int i = 0; i < Lines; ++i) {
		MatrixElements[i] = new double[Columns];
	}
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] = j + 1;
		}
	}
};

Matrix::Matrix(const double** AnotherMatrix, const int AnotherMatrixLines, const int AnotherMatrixColumns)
{
	Lines = AnotherMatrixLines;
	Columns = AnotherMatrixColumns;
	MatrixElements = new double* [Lines];
	for (int i = 0; i < Lines; ++i)
	{
		MatrixElements[i] = new double[Columns];
	}
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] = AnotherMatrix[i][j];
		}
	}
};

Matrix::Matrix(const Matrix& AnotherMatrix)
{
	Lines = AnotherMatrix.Lines;
	Columns = AnotherMatrix.Lines;
	MatrixElements = new double* [Lines];
	for (int i = 0; i < Lines; ++i)
	{
		MatrixElements[i] = new double[Columns];
	}
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] = AnotherMatrix.MatrixElements[i][j];
		}
	}
};

Matrix::Matrix(Matrix&& AnotherMatrix)
{
	Lines = AnotherMatrix.Lines;
	Columns = AnotherMatrix.Columns;
	MatrixElements = AnotherMatrix.MatrixElements;

	for (int i = 0; i < AnotherMatrix.Lines; ++i)
	{
		AnotherMatrix.MatrixElements[i] = nullptr;
		delete[] AnotherMatrix.MatrixElements[i];
	}
	AnotherMatrix.MatrixElements = nullptr;
	delete[] AnotherMatrix.MatrixElements;
};

Matrix::Matrix(const int Number)
{
	Lines = 1;
	Columns = 1;
	MatrixElements = new double* [1];
	MatrixElements[0] = new double[1];
	MatrixElements[0][0] = Number;
};

Matrix::Matrix(const char* AnotherMatrix)
{
	int i = 0, j = 0;
	Lines = 0;
	Columns = 1;
	int Col = 1;
	while (AnotherMatrix[i] != '\0')
	{
		if (AnotherMatrix[i] == ',')
		{
			Col += 1;
		}
		else if (AnotherMatrix[i] == ';')
		{
			Lines += 1;
			Columns = Col;
			Col = 1;
		}
		i++;
	}
	MatrixElements = new double* [Lines];
	for (i = 0; i < Lines; ++i)
	{
		MatrixElements[i] = new double[Columns];
	}
	const char s[6] = "[];, ";
	char* Number;
	char* NextNumber;
	Number = strtok_s((char*)AnotherMatrix, s, &NextNumber);
	for (i = 0; i < Lines; ++i)
	{
		for (j = 0; j < Columns; j++)
		{
			MatrixElements[i][j] = strtod(Number, NULL);
			Number = strtok_s(NULL, s, &NextNumber);
		}
	}
};

Matrix::~Matrix()
{
	if (MatrixElements != nullptr)
	{
		for (int i = 0; i < Lines; ++i)
		{
			delete[] MatrixElements[i];
		}
		delete[] MatrixElements;
	}
};

Matrix& Matrix::operator=(const Matrix& AnotherMatrix)
{
	if (&AnotherMatrix == this) return *this;
	for (int i = 0; i < Lines; ++i)
	{
		delete[] MatrixElements[i];
	}
	delete[] MatrixElements;

	Columns = AnotherMatrix.Columns;
	Lines = AnotherMatrix.Lines;
	MatrixElements = new double* [Lines];
	for (int i = 0; i < Lines; i++)
	{
		MatrixElements[i] = new double[Columns];
	}
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] = AnotherMatrix.MatrixElements[i][j];
		}
	}

	return *this;
};

Matrix& Matrix::operator=(Matrix&& AnotherMatrix)
{
	if (&AnotherMatrix == this) return *this;

	for (int i = 0; i < Lines; ++i)
	{
		delete[] MatrixElements[i];
	}
	delete[] MatrixElements;

	Lines = AnotherMatrix.Lines;
	Columns = AnotherMatrix.Columns;
	MatrixElements = AnotherMatrix.MatrixElements;
	for (int i = 0; i < AnotherMatrix.Lines; ++i)
	{
		AnotherMatrix.MatrixElements[i] = nullptr;
		delete[] AnotherMatrix.MatrixElements[i];
	}
	AnotherMatrix.MatrixElements = nullptr;
	delete[] AnotherMatrix.MatrixElements;

	return *this;
};

void Matrix::ShowMatrix() const
{
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			cout << MatrixElements[i][j] << " ";
		}
		cout << endl;
	}
};

void Matrix::ConvertMatrixToString(string& Str) const
{
	Str += '[';
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			Str += to_string(MatrixElements[i][j]);
			if (j < (Columns - 1))
			{
				Str += ", ";
			}
		}
		Str += "; ";
	}
	Str += ']';
};

const double** Matrix::GetMatrix() const
{
	return (const double**)MatrixElements;
};

void Matrix::SetMatrixElem(const double Elem, const int LinesPosition, const int ColumnsPosition)
{
	MatrixElements[LinesPosition][ColumnsPosition] = Elem;
};

void Matrix::SetMatrix(double** Matr) 
{
	for (int i = 0; i < Lines; ++i)
	{
		delete[] MatrixElements[i];
	}
	delete[] MatrixElements;
	MatrixElements = Matr;
};

const int Matrix::GetLines() const
{
	return Lines;
};

void Matrix::SetLines(const int Number)
{
	Lines = Number;
};

const int Matrix::GetColumns() const
{
	return Columns;
};

void Matrix::SetColumns(const int Number) 
{
	Columns = Number;
};

const Matrix& CreateMatrix(const double** AnotherMatrix, const int AnotherMatrixLines, const int AnotherMatrixColumns)
{
	Matrix* Mat = new Matrix(AnotherMatrix, AnotherMatrixLines, AnotherMatrixColumns);
	return *Mat;
};

const Matrix operator+ (const Matrix& Left, const Matrix& Right) 
{
	if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
	{
		cout << "Failed to add matrices" << endl;
		return 0;
	}
	int Lines = Left.Lines;
	int Columns = Left.Columns;
	double** MatrixElements = new double* [Lines];
	for (int i = 0; i < Lines; ++i)
	{
		MatrixElements[i] = new double[Columns];
	}
	for (int i = 0; i < Lines; ++i) 
	{
		for (int j = 0; j < Columns; ++j)
		{
			if (((Right.MatrixElements[i][j] > 0) && (Left.MatrixElements[i][j] > (DBL_MAX - Right.MatrixElements[i][j]))) ||
				((Right.MatrixElements[i][j] < 0) && (Left.MatrixElements[i][j] < (DBL_MIN - Right.MatrixElements[i][j]))))
			{
				cout << "An overflow occurred while adding matrices" << endl;
				MatrixElements[i][j] = 0;
			}
			else
			{
				MatrixElements[i][j] = Left.MatrixElements[i][j] + Right.MatrixElements[i][j];
			};
		}
	}
	return Matrix((const double**)MatrixElements, Lines, Columns);
};

const Matrix operator+ (const Matrix& Left, const int Number)
{
	int Lines = Left.Lines;
	int Columns = Left.Columns;
	double** MatrixElements = new double* [Lines];
	for (int i = 0; i < Lines; ++i)
	{
		MatrixElements[i] = new double[Columns];
	}
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			if (i == j)
			{
				if (((Number > 0) && (Left.MatrixElements[i][j] > (DBL_MAX - Number))) ||
					((Number < 0) && (Left.MatrixElements[i][j] < (DBL_MIN - Number))))
				{
					cout << "An overflow occurred while adding matrices" << endl;
					MatrixElements[i][j] = 0;
				}
				else MatrixElements[i][j] = Left.MatrixElements[i][j] + Number;
			}
			else MatrixElements[i][j] = Left.MatrixElements[i][j];
		}
	}
	return Matrix((const double**)MatrixElements, Lines, Columns);
};

const Matrix operator+ (const Matrix& Left, const char* Str) 
{
	return Left + atoi(Str);
};

const Matrix operator- (const Matrix& Left, const Matrix& Right) 
{
	if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
	{
		cout << "Failed to subtract matrices" << endl;
		return 0;
	}
	int Lines = Left.Lines;
	int Columns = Left.Columns;
	double** MatrixElements = new double* [Lines];
	for (int i = 0; i < Lines; ++i)
	{
		MatrixElements[i] = new double[Columns];
	}
	for (int i = 0; i < Left.Lines; ++i)
	{
		for (int j = 0; j < Left.Columns; ++j)
		{
			if (((Right.MatrixElements[i][j] > 0) && (Left.MatrixElements[i][j] < (DBL_MIN + Right.MatrixElements[i][j]))) ||
				((Right.MatrixElements[i][j] < 0) && (Left.MatrixElements[i][j] > (DBL_MAX + Right.MatrixElements[i][j]))))
			{
				cout << "An overflow occurred while subtracting matrices" << endl;
				MatrixElements[i][j] = 0;
			}
			else
			{
				MatrixElements[i][j] = Left.MatrixElements[i][j] - Right.MatrixElements[i][j];
			};
		}
	}
	return Matrix((const double**)MatrixElements, Lines, Columns);
};

const Matrix operator- (const Matrix& Left, const int Number)
{
	int Lines = Left.Lines;
	int Columns = Left.Columns;
	double** MatrixElements = new double* [Lines];
	for (int i = 0; i < Lines; ++i)
	{
		MatrixElements[i] = new double[Columns];
	}
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			if (i == j)
			{
				if (((Number > 0) && (Left.MatrixElements[i][j] < (DBL_MIN + Number))) ||
					((Number < 0) && (Left.MatrixElements[i][j] > (DBL_MAX + Number))))
				{
					cout << "An overflow occurred while subtracting matrices" << endl;
					MatrixElements[i][j] = 0;
				}
				else MatrixElements[i][j] = Left.MatrixElements[i][j] - Number;
			}
			else MatrixElements[i][j] = Left.MatrixElements[i][j];
		}
	}
	return Matrix((const double**)MatrixElements, Lines, Columns);
};

const Matrix operator- (const Matrix& Left, const char* Str) 
{
	return Left - atoi(Str);
};

const Matrix operator* (const Matrix& Left, const Matrix& Right) 
{
	if (Left.Columns != Right.Lines)
	{
		cout << "Failed to multiply matrices" << endl;
		return 0;
	}
	int Lines = Left.Lines;
	int Columns = Right.Columns;
	double** MatrixElements = new double* [Lines];
	for (int i = 0; i < Lines; ++i)
	{
		MatrixElements[i] = new double[Columns];
		for (int j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] = 0;
			for (int k = 0; k < Columns; ++k)
			{
				MatrixElements[i][j] += Left.MatrixElements[i][k] * Right.MatrixElements[k][j];
			}
			if (MatrixElements[i][j] < 0.000000001) 
			{
				MatrixElements[i][j] = 0;
			}
		}
	}
	return Matrix((const double**)MatrixElements, Lines, Columns);
};

const Matrix operator* (const Matrix& Left, const int Number)
{
	int Lines = Left.Lines;
	int Columns = Left.Columns;
	double** MatrixElements = new double* [Lines];
	for (int i = 0; i < Lines; ++i)
	{
		MatrixElements[i] = new double[Columns];
	}
	for (int i = 0; i < Left.Lines; ++i)
	{
		for (int j = 0; j < Left.Columns; ++j)
		{
			MatrixElements[i][j] = Left.MatrixElements[i][j] * Number;
		}
	}
	return Matrix((const double**)MatrixElements, Lines, Columns);
};

const Matrix operator* (const Matrix& Left, const char* Str) 
{
	return Left * atoi(Str);
};

void GetMatr(const double** Mas, double** P, const int i, const int j, const int m) 
{
	int di, dj;
	di = 0;
	for (int ki = 0; ki < m - 1; ++ki) 
	{
		if (ki == i) di = 1;
		dj = 0;
		for (int kj = 0; kj < m - 1; ++kj) 
		{
			if (kj == j) dj = 1;
			P[ki][kj] = Mas[ki + di][kj + dj];
		}
	}
}

const double FindDeterminant(const Matrix& M) // ??????? ??????????? ?????????? ???????, ????????? ??? ??????? ???????
{
	double Determinant = 0;
	int k, n;
	double** P;
	P = new double* [M.GetLines()];
	for (int i = 0; i < M.GetLines(); ++i) P[i] = new double[M.GetLines()];
	k = 1; //(-1) ? ??????? i
	n = M.GetLines() - 1;
	if (M.GetLines() == 1) 
	{
		return M.GetMatrix()[0][0];
	}
	if (M.GetLines() == 2)
	{
		Determinant = M.GetMatrix()[0][0] * M.GetMatrix()[1][1] - (M.GetMatrix()[1][0] * M.GetMatrix()[0][1]);
		return Determinant;
	}
	if (M.GetLines() > 2) 
	{
		for (int i = 0; i < M.GetLines(); ++i)
		{
			GetMatr(M.GetMatrix(), P, i, 0, M.GetLines());
			Matrix TempMatrix((const double**)(P), n, n);
			Determinant = Determinant + k * M.GetMatrix()[i][0] * FindDeterminant(TempMatrix);
			k = -k;
		}
	}
	return Determinant;
}

int GetMinor(const double** A, double** B, int x, int y, int size)
{
	int XCount = 0, YCount = 0;
	for (int i = 0; i < size; ++i)
	{
		if (i != x)
		{
			YCount = 0;
			for (int j = 0; j < size; ++j)
			{
				if (j != y)
				{
					B[XCount][YCount] = A[i][j];
					YCount++;
				}
			}
			XCount++;
		}
	}
	return 0;
}

double FindArrayDeterminant(const double** A, const int Size)
{
	if (Size == 1)
	{
		return A[0][0];
	}
	else
	{
		int Det = 0;
		double** Minor = new double* [Size - 1];
		for (int i = 0; i < Size; ++i)
		{
			Minor[i] = new double[Size - 1];
		}
		for (int i = 0; i < Size; ++i)
		{
			GetMinor(A, Minor, 0, i, Size);
			Det += pow(-1, i) * A[0][i] * FindArrayDeterminant((const double**)Minor, Size - 1);
		}
		return Det;
	}
}

void FindAlgDop(const double** A, const int Size, double** B)
{
	int Det = FindArrayDeterminant(A, Size);
	if (Det > 0) Det = -1;
	else Det = 1;
	double** Minor = new double* [Size - 1];
	for (int i = 0; i < Size - 1; ++i)
	{
		Minor[i] = new double[Size - 1];
	}
	for (int j = 0; j < Size; ++j)
	{
		for (int i = 0; i < Size; ++i)
		{
			GetMinor(A, Minor, j, i, Size);
			if ((i + j) % 2 == 0)
				B[j][i] = -Det * FindArrayDeterminant((const double**)Minor, Size - 1);
			else
				B[j][i] = Det * FindArrayDeterminant((const double**)Minor, Size - 1);
		}
	}
	for (int i = 0; i < Size - 1; ++i)
	{
		delete[] Minor[i];
	}
	delete[] Minor;
}

void Matrix::MatrixTransponation()
{
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = i; j < Columns; ++j)
		{
			swap(MatrixElements[i][j], MatrixElements[j][i]);
		}
	}
}

const Matrix operator/ (const Matrix& Left, const Matrix& Right) 
{
	if (Left.Columns != Right.Lines)
	{
		cout << "Failed to divide matrices" << endl;
		return 0;
	}
	if (Right.Lines != Right.Columns)
	{
		cout << "Failed to divide matrices" << endl;
		return 0;
	}
	double Determinant = FindDeterminant(Right);
	if (Determinant == 0)
	{
		cout << "Determinant was equal to 0. Failed to divide matrices" << endl;
		return 0;
	}
	for (int i = 0; i < Right.Lines; ++i)
	{
		for (int j = 0; j < Right.Columns; ++j)
		{
			if (Right.MatrixElements[i][j] == 0)
			{
				cout << "Divisor was equal to 0. Failed to divide matrices" << endl;
				return 0;
			}
		}
	}
	double** Result = new double* [Right.Lines];
	for (int i = 0; i < Right.Lines; ++i)
	{
		Result[i] = new double[Right.Columns];
	}
	FindAlgDop((const double**)Right.MatrixElements, Right.Lines, Result);
	Matrix Copy((const double**)Result, Right.Lines, Right.Columns);
	Copy.MatrixTransponation();
	for (int i = 0; i < Copy.Lines; ++i)
	{
		for (int j = 0; j < Copy.Columns; ++j)
		{
			Copy.MatrixElements[i][j] /= Determinant;
		}
	}
	for (int i = 0; i < Right.Lines; ++i)
	{
		delete[] Result[i];
	}
	delete[] Result;
	return Left * Copy;
};

const Matrix operator/ (const Matrix& Left, const int Number)
{
	if (Number == 0)
	{
		cout << "The divisor was equal to 0" << endl;
		return 0;
	}
	int Lines = Left.Lines;
	int Columns = Left.Columns;
	double** MatrixElements = new double* [Lines];
	for (int i = 0; i < Lines; ++i)
	{
		MatrixElements[i] = new double[Columns];
		for (int j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] = Left.MatrixElements[i][j];
		}
	}
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] /= Number;
		}
	}
	return Matrix((const double**)MatrixElements, Lines, Columns);
};

const Matrix operator/ (const Matrix& Left, const char* Str) 
{
	return Left + atoi(Str);
};

const Matrix& Matrix::operator+=(const Matrix& AnotherMatrix)
{
	if ((Lines != AnotherMatrix.Lines) || (Columns != AnotherMatrix.Columns))
	{
		cout << "Failed to add matrices" << endl;
		return 0;
	}
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			if (((AnotherMatrix.MatrixElements[i][j] > 0) && (MatrixElements[i][j] > (DBL_MAX - AnotherMatrix.MatrixElements[i][j]))) ||
				((AnotherMatrix.MatrixElements[i][j] < 0) && (MatrixElements[i][j] < (DBL_MIN - AnotherMatrix.MatrixElements[i][j]))))
			{
				cout << "An overflow occurred while adding matrices" << endl;
				MatrixElements[i][j] = 0;
			}
			else MatrixElements[i][j] += AnotherMatrix.MatrixElements[i][j];
		}
	}
	return *this;
};

const Matrix& Matrix::operator+=(const int Number)
{
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			if (i == j)
			{
				if (((Number > 0) && (MatrixElements[i][j] > (DBL_MAX - Number))) ||
					((Number < 0) && (MatrixElements[i][j] < (DBL_MIN - Number))))
				{
					cout << "An overflow occurred while adding matrices" << endl;
					MatrixElements[i][j] = 0;
					continue;
				}
				else MatrixElements[i][j] += Number;
			}
		}
	}
	return *this;
};

const Matrix& Matrix::operator-=(const Matrix& AnotherMatrix) 
{
	if ((Lines != AnotherMatrix.Lines) || (Columns != AnotherMatrix.Columns))
	{
		cout << "Failed to subtract matrices" << endl;
		return 0;
	}
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			if (((AnotherMatrix.MatrixElements[i][j] > 0) && (MatrixElements[i][j] < (DBL_MIN + AnotherMatrix.MatrixElements[i][j]))) ||
				((AnotherMatrix.MatrixElements[i][j] < 0) && (MatrixElements[i][j] > (DBL_MAX + AnotherMatrix.MatrixElements[i][j]))))
			{
				cout << "An overflow occurred while subtracting matrices" << endl;
				MatrixElements[i][j] = 0;
			}
			else MatrixElements[i][j] -= AnotherMatrix.MatrixElements[i][j];
		}
	}
	return *this;
};

const Matrix& Matrix::operator-=(const int Number)
{
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			if (i == j) {
				if (((Number > 0) && (MatrixElements[i][j] < (DBL_MIN + Number))) ||
					((Number < 0) && (MatrixElements[i][j] > (DBL_MAX + Number))))
				{
					cout << "An overflow occurred while subtracting matrices" << endl;
					MatrixElements[i][j] = 0;
				}
				else MatrixElements[i][j] -= Number;
			}
		}
	}
	return *this;
};

const Matrix& Matrix::operator*=(const Matrix& AnotherMatrix) 
{
	if (Columns != AnotherMatrix.Lines)
	{
		cout << "Failed to multiply matrices" << endl;
		return 0;
	}

	double** Temp = new double* [Lines];
	for (int i = 0; i < Lines; ++i)
	{
		Temp[i] = new double[Columns];
	}
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			Temp[i][j] = MatrixElements[i][j];
		}
	}
	for (int i = 0; i < Lines; ++i)
	{
		delete[] MatrixElements[i];
	}
	delete[] MatrixElements;

	MatrixElements = new double* [Lines];
	Columns = AnotherMatrix.Columns;
	for (int i = 0; i < Lines; ++i)
	{
		MatrixElements[i] = new double[Columns];
	}
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < AnotherMatrix.Columns; ++j)
		{
			MatrixElements[i][j] = 0;
			for (int k = 0; k < AnotherMatrix.Columns; ++k)
			{
				MatrixElements[i][j] += Temp[i][k] * AnotherMatrix.MatrixElements[k][j];
			}
		}
	}

	for (int i = 0; i < Lines; ++i)
	{
		delete[] Temp[i];
	}
	delete[] Temp;
	return *this;
};

const Matrix& Matrix::operator*=(const int Number)
{
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] *= Number;
		}
	}
	return *this;
};

const Matrix& Matrix::operator/=(const Matrix& AnotherMatrix)
{
	if (Columns != AnotherMatrix.Lines)
	{
		cout << "Failed to divide matrices" << endl;
		return 0;
	}
	if (AnotherMatrix.Lines != AnotherMatrix.Columns)
	{
		cout << "Failed to divide matrices" << endl;
		return 0;
	}
	double Determinant = FindDeterminant(AnotherMatrix);
	if (Determinant == 0)
	{
		cout << "Determinant was equal to 0. Failed to divide matrices" << endl;
		return 0;
	}
	for (int i = 0; i < AnotherMatrix.Lines; ++i)
	{
		for (int j = 0; j < AnotherMatrix.Columns; ++j)
		{
			if (AnotherMatrix.MatrixElements[i][j] == 0)
			{
				cout << "Divisor was equal to 0. Failed to divide matrices" << endl;
				return 0;
			}
		}
	}
	double** Result = new double* [AnotherMatrix.Lines];
	for (int i = 0; i < AnotherMatrix.Lines; ++i)
	{
		Result[i] = new double[AnotherMatrix.Columns];
	}
	FindAlgDop((const double**)AnotherMatrix.MatrixElements, AnotherMatrix.Lines, Result);
	Matrix Copy((const double**)Result, AnotherMatrix.Lines, AnotherMatrix.Columns);
	Copy.MatrixTransponation();
	for (int i = 0; i < Copy.Lines; ++i)
	{
		for (int j = 0; j < Copy.Columns; ++j)
		{
			Copy.MatrixElements[i][j] /= Determinant;
		}
	}
	Matrix Res = *this * Copy;
	for (int i = 0; i < Lines; ++i)
	{
		delete[] MatrixElements[i];
	}
	for (int i = 0; i < Lines; ++i) 
	{
		MatrixElements[i] = new double[Columns];
		for (int j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] = Res.MatrixElements[i][j];
		}
	}
	for (int i = 0; i < AnotherMatrix.Lines; ++i)
	{
		delete[] Result[i];
	}
	delete[] Result;
	return *this;
};

const Matrix& Matrix::operator/=(const int Number)
{
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] /= Number;
		}
	}
	return *this;
};

const bool operator<(const Matrix& Left, const Matrix& Right) 
{
	if (&Left == &Right) return false;
	if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
	{
		cout << "Those matrices cannot be compared" << endl;
		return false;
	}
	bool Result = false;
	for (int i = 0; i < Left.Lines; ++i)
	{
		for (int j = 0; j < Left.Columns; ++j)
		{
			if (Left.MatrixElements[i][j] < Right.MatrixElements[i][j]) Result = true;
			else Result = false;
		}
	}
	return Result;
};

const bool operator>(const Matrix& Left, const Matrix& Right) 
{
	if (&Left == &Right) return false;
	if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
	{
		cout << "Those matrices cannot be compared" << endl;
		return false;
	}
	bool Result = false;
	for (int i = 0; i < Left.Lines; ++i)
	{
		for (int j = 0; j < Left.Columns; ++j)
		{
			if (Left.MatrixElements[i][j] > Right.MatrixElements[i][j]) Result = true;
			else Result = false;
		}
	}
	return Result;
};

const bool operator>=(const Matrix& Left, const Matrix& Right) 
{
	if (&Left == &Right) return true;
	if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
	{
		cout << "Those matrices cannot be compared" << endl;
		return false;
	}
	bool Result = false;
	for (int i = 0; i < Left.Lines; ++i)
	{
		for (int j = 0; j < Left.Columns; ++j)
		{
			if (Left.MatrixElements[i][j] >= Right.MatrixElements[i][j]) Result = true;
			else Result = false;
		}
	}
	return Result;
};

const bool operator<=(const Matrix& Left, const Matrix& Right) 
{
	if (&Left == &Right) return true;
	if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
	{
		cout << "Those matrices cannot be compared" << endl;
		return false;
	}
	bool Result = false;
	for (int i = 0; i < Left.Lines; ++i)
	{
		for (int j = 0; j < Left.Columns; ++j) 
		{
			if (Left.MatrixElements[i][j] <= Right.MatrixElements[i][j]) Result = true;
			else Result = false;
		}
	}
	return Result;
};

const bool operator==(const Matrix& Left, const Matrix& Right) 
{
	if (&Left == &Right) return true;
	if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
	{
		cout << "Those matrices cannot be compared" << endl;
		return false;
	}
	bool Result = false;
	for (int i = 0; i < Left.Lines; ++i)
	{
		for (int j = 0; j < Left.Columns; ++j)
		{
			if (Left.MatrixElements[i][j] == Right.MatrixElements[i][j]) Result = true;
			else Result = false;
		}
	}
	return Result;
};

const bool operator!=(const Matrix& Left, const Matrix& Right) 
{
	if (&Left == &Right) return false;
	if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
	{
		cout << "Those matrices cannot be compared" << endl;
		return false;
	}
	bool Result = false;
	for (int i = 0; i < Left.Lines; ++i)
	{
		for (int j = 0; j < Left.Columns; ++j)
		{
			if (Left.MatrixElements[i][j] != Right.MatrixElements[i][j]) Result = true;
			else Result = false;
		}
	}
	return Result;
};