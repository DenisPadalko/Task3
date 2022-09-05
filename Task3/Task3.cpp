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
	cout << "Matrix M: " << endl;
	for (int i = 0; i < M.GetLines(); ++i)
	{
		for (int j = 0; j < M.GetColumns(); ++j)
		{
			cout << M.GetMatrix()[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << "Overloaded operations +, -, *, /" << endl << endl;
	Matrix Result = M + M;
	cout << "M + M" << endl << endl;
	for (int i = 0; i < Result.GetLines(); ++i)
	{
		for (int j = 0; j < Result.GetColumns(); ++j)
		{
			cout << Result.GetMatrix()[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << "M - M" << endl << endl;
	Result = M - M;
	for (int i = 0; i < Result.GetLines(); ++i)
	{
		for (int j = 0; j < Result.GetColumns(); ++j)
		{
			cout << Result.GetMatrix()[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << "M * M" << endl << endl;
	Result = M * M;
	for (int i = 0; i < Result.GetLines(); ++i)
	{
		for (int j = 0; j < Result.GetColumns(); ++j)
		{
			cout << Result.GetMatrix()[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << "M / M" << endl << endl;
	Result = M / M;
	for (int i = 0; i < Result.GetLines(); ++i)
	{
		for (int j = 0; j < Result.GetColumns(); ++j)
		{
			cout << Result.GetMatrix()[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << "M + M + M" << endl << endl;
	Result = M + M + M;
	for (int i = 0; i < Result.GetLines(); ++i)
	{
		for (int j = 0; j < Result.GetColumns(); ++j)
		{
			cout << Result.GetMatrix()[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << "M / 0" << endl << endl;
	Result = M / 0;
	for (int i = 0; i < Result.GetLines(); ++i)
	{
		for (int j = 0; j < Result.GetColumns(); ++j)
		{
			cout << Result.GetMatrix()[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << "M + \"222\" + M + 111 + M" << endl << endl;
	Result = M + "222" + M + 111 + M;
	for (int i = 0; i < Result.GetLines(); ++i)
	{
		for (int j = 0; j < Result.GetColumns(); ++j)
		{
			cout << Result.GetMatrix()[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << "Overloaded operations +=, -=, *=, /=" << endl << endl;
	cout << "\"Temp\" matrix:" << endl;
	Matrix Temp = M;
	for (int i = 0; i < Temp.GetLines(); ++i)
	{
		for (int j = 0; j < Temp.GetColumns(); ++j)
		{
			cout << Temp.GetMatrix()[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << "Temp += M" << endl << endl;
	Temp += M;
	for (int i = 0; i < Temp.GetLines(); ++i)
	{
		for (int j = 0; j < Temp.GetColumns(); ++j)
		{
			cout << Temp.GetMatrix()[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << "Temp -= M" << endl << endl;
	Temp -= M;
	for (int i = 0; i < Temp.GetLines(); ++i)
	{
		for (int j = 0; j < Temp.GetColumns(); ++j)
		{
			cout << Temp.GetMatrix()[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << "Temp *= M" << endl << endl;
	Temp = M;
	Temp *= M;
	for (int i = 0; i < Temp.GetLines(); ++i)
	{
		for (int j = 0; j < Temp.GetColumns(); ++j)
		{
			cout << Temp.GetMatrix()[i][j] << " ";
		}
		cout << endl;
	}
	Temp = M;
	cout << endl << "Temp /= M" << endl << endl;
	Temp /= M;
	for (int i = 0; i < Temp.GetLines(); ++i)
	{
		for (int j = 0; j < Temp.GetColumns(); ++j)
		{
			cout << Temp.GetMatrix()[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << "Overloaded operations >, <, >=, <=, ==, !=" << endl << endl;
	cout << "\"Temp\" matrix:" << endl;
	Temp = M;
	for (int i = 0; i < Temp.GetLines(); ++i)
	{
		for (int j = 0; j < Temp.GetColumns(); ++j)
		{
			cout << Temp.GetMatrix()[i][j] << " ";
		}
		cout << endl;
	}
	bool Res = Temp < M;
	cout << "Temp < M" << endl;
	if (Res) cout << "True" << endl;
	else cout << "False" << endl;
	Res = Temp > M;
	cout << "Temp > M" << endl;
	if (Res) cout << "True" << endl;
	else cout << "False" << endl;
	Res = Temp >= M;
	cout << "Temp >= M" << endl;
	if (Res) cout << "True" << endl;
	else cout << "False" << endl;
	Res = Temp <= M;
	cout << "Temp <= M" << endl;
	if (Res) cout << "True" << endl;
	else cout << "False" << endl;
	Res = Temp == M;
	cout << "Temp == M" << endl;
	if (Res) cout << "True" << endl;
	else cout << "False" << endl;
	Res = Temp != M;
	cout << "Temp != M" << endl;
	if (Res) cout << "True" << endl;
	else cout << "False" << endl;
	return 0;
}