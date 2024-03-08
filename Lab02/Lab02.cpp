// C++ program to find Determinant of a matrix
#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <algorithm>
using std::cout;
using std::endl;
using std::setw;
using namespace std;


#define N 10


void getCofactor(long long mat[N][N], long long temp[N][N], long long p,
				long long q, long long n)
{
	long long i = 0, j = 0;

	
	for (long long row = 0; row < n; row++)
	{
		for (long long col = 0; col < n; col++)
		{
			
			if (row != p && col != q)
			{
				temp[i][j++] = mat[row][col];

				
				if (j == n - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
}


long long determinantOfMatrix(long long mat[N][N], long long n)
{
	long long D = 0; 

	
	if (n == 1)
		return mat[0][0];

	long long temp[N][N]; 

	long long sign = 1; 

	
	for (long long f = 0; f < n; f++)
	{
		
		getCofactor(mat, temp, 0, f, n);
		D += sign * mat[0][f]
			* determinantOfMatrix(temp, n - 1);

		
		sign = -sign;
	}

	return D;
}


void display(long long mat[N][N], long long row, long long col)
{
	for (long long i = 0; i < row; i++)
	{
		for (long long j = 0; j < col; j++)
			cout <<" " << mat[i][j];
		cout <<"\n";
	}
}


int main()
{

	long long mat[N][N];
	// FILE HANDLING
    ifstream file("mat1.txt");
    if (!file) {
        cout << "Can't Open File" << endl;
        return 1;
    }


    for (long long i = 0; i < N; i++) {
        for (long long j = 0; j < N; j++)
            file >> mat[i][j];
    }

    display(mat, N, N);

    cout<< endl;

	cout <<"Determinant of the matrix is : " << determinantOfMatrix(mat, N);
	return 0;
}