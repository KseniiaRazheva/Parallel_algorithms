#include <iostream>
#include <cstdlib>
#include "mpi.h"
using namespace std;
int main(int argc, char **argv)
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int n = 500;

//matrix initialization by each process
	int** a = new int*[n];
	int** b = new int*[n];
	int** c = new int*[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[n];
		b[i] = new int[n];
		c[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = rand() % 10;
			b[i][j] = rand() % 10;
			c[i][j] = 0;
		}
	}
		
	MPI_Barrier(MPI_COMM_WORLD); //barrier process synchronization

// start timing for each process
	double start_time = MPI_Wtime();

// matrix multiplication
	for (int i = 0; i < n; i++)
		for (int k = 0; k < n; k++)
			for (int j = 0; j < n; j++)
				c[i][j] += a[i][k] * b[k][j];

// end of timing
	double end_time = MPI_Wtime();

// output the execution time of matrix multiplication at each process
	cout << "Execution time of matrix multiplication at " << rank << " process " << (end_time - start_time) << endl;
	MPI_Finalize();
}