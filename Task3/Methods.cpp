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
	}
	AnotherMatrix.MatrixElements = nullptr;
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
	}
	AnotherMatrix.MatrixElements = nullptr;

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
	Matrix M(Left);
	for (int i = 0; i < Left.Lines; ++i) 
	{
		for (int j = 0; j < Left.Columns; ++j)
		{
			if (((Right.MatrixElements[i][j] > 0) && (Left.MatrixElements[i][j] > (DBL_MAX - Right.MatrixElements[i][j]))) ||
				((Right.MatrixElements[i][j] < 0) && (Left.MatrixElements[i][j] < (DBL_MIN - Right.MatrixElements[i][j]))))
			{
				cout << "An overflow occurred while adding matrices" << endl;
				M.MatrixElements[i][j] = 0;
			}
			else
			{
				M.MatrixElements[i][j] = Left.MatrixElements[i][j] + Right.MatrixElements[i][j];
			};
		}
	}
	return M;
};

const Matrix operator- (const Matrix& Left, const Matrix& Right) 
{
	if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
	{
		cout << "Failed to subtract matrices" << endl;
		return 0;
	}
	Matrix M(Left);
	for (int i = 0; i < Left.Lines; ++i)
	{
		for (int j = 0; j < Left.Columns; ++j)
		{
			if (((Right.MatrixElements[i][j] > 0) && (Left.MatrixElements[i][j] < (DBL_MIN + Right.MatrixElements[i][j]))) ||
				((Right.MatrixElements[i][j] < 0) && (Left.MatrixElements[i][j] > (DBL_MAX + Right.MatrixElements[i][j]))))
			{
				cout << "An overflow occurred while subtracting matrices" << endl;
				M.MatrixElements[i][j] = 0;
			}
			else
			{
				M.MatrixElements[i][j] = Left.MatrixElements[i][j] - Right.MatrixElements[i][j];
			};
		}
	}
	return M;
};

const Matrix operator* (const Matrix& Left, const Matrix& Right) 
{
	if (Left.Columns != Right.Lines)
	{
		cout << "Failed to multiply matrices" << endl;
		return 0;
	}
	Matrix M(Left.GetMatrix(), Left.Lines, Right.Columns);
	for (int i = 0; i < Left.Lines; ++i)
	{
		for (int j = 0; j < Right.Columns; ++j)
		{
			M.MatrixElements[i][j] = Left.MatrixElements[i][j] * Right.MatrixElements[i][j];
		}
	}
	return M;
};

const Matrix operator* (const Matrix& Left, const int Number)
{
	Matrix M(Left);
	for (int i = 0; i < Left.Lines; ++i)
	{
		for (int j = 0; j < Left.Columns; ++j)
		{
			M.MatrixElements[i][j] = Left.MatrixElements[i][j] * Number;
		}
	}
	return M;
};
void MatrixTransposition(Matrix& M) // Функція транспонування матриці, необхідна для ділення матриць
{
	double Number;
	for (int i = 0; i < M.GetLines(); ++i)
	{
		for (int j = i; j < M.GetColumns(); ++j)
		{
			Number = M.GetMatrix()[i][j];
			M.SetMatrixElem(M.GetMatrix()[j][i], i, j);
			M.SetMatrixElem(Number, j, i);
		}
	}
	int Temp = M.GetLines();
	M.SetLines(M.GetColumns());
	M.SetColumns(Temp);
}

void GetMatr(const double** mas, double** p, const int i, const int j, const int m) 
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
			p[ki][kj] = mas[ki + di][kj + dj];
		}
	}
}

const double FindDeterminant(const Matrix& M) // функція знаходження визначника матриці, необхідна для ділення матриць
{
	double Determinant = 0;
	int k, n;
	double** p;
	p = new double* [M.GetLines()];
	for (int i = 0; i < M.GetLines(); ++i) p[i] = new double[M.GetLines()];
	k = 1; //(-1) в степені i
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
			GetMatr(M.GetMatrix(), p, i, 0, M.GetLines());
			Matrix TempMatrix((const double**)(p), n, n);
			Determinant = Determinant + k * M.GetMatrix()[i][0] * FindDeterminant(TempMatrix);
			k = -k;
		}
	}
	return Determinant;
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
	Matrix M(Left.GetMatrix(), Left.Lines, Right.Columns);
	Matrix Copy(Right);
	MatrixTransposition(Copy);
	for (int i = 0; i < Right.Lines; ++i)
	{
		for (int j = 0; j < Right.Columns; ++j)
		{
			Copy.MatrixElements[i][j] /= Determinant;
		}
	}
	for (int i = 0; i < M.Lines; ++i)
	{
		for (int j = 0; j < M.Columns; ++j)
		{
			if (Right.MatrixElements[i][j] == 0)
			{
				cout << "The divisor was equal to 0" << endl;
				M.MatrixElements[i][j] = 0;
			}
			else 
			{
				M.MatrixElements[i][j] *= Copy.MatrixElements[i][j];
			};
		}
	}
	return M;
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
			else
			{
				MatrixElements[i][j] += AnotherMatrix.MatrixElements[i][j];
			};
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
			else
			{
				MatrixElements[i][j] -= AnotherMatrix.MatrixElements[i][j];
			};
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
	int TempLines = Lines;
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
			MatrixElements[i][j] = Temp[i][j] * AnotherMatrix.MatrixElements[i][j];
		}
	}

	for (int i = 0; i < TempLines; ++i)
	{
		delete[] Temp[i];
	}
	delete[] Temp;
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
	Matrix M(GetMatrix(), Lines, AnotherMatrix.Columns);
	Matrix Copy(AnotherMatrix);
	MatrixTransposition(Copy);
	for (int i = 0; i < AnotherMatrix.Lines; ++i)
	{
		for (int j = 0; j < AnotherMatrix.Columns; ++j)
		{
			Copy.MatrixElements[i][j] /= Determinant;
		}
	}
	for (int i = 0; i < M.Lines; ++i)
	{
		for (int j = 0; j < M.Columns; ++j)
		{
			if (AnotherMatrix.MatrixElements[i][j] == 0)
			{
				cout << "The divisor was equal to 0" << endl;
				M.MatrixElements[i][j] = 0;
			}
			else
			{
				M.MatrixElements[i][j] *= Copy.MatrixElements[i][j];
			};
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