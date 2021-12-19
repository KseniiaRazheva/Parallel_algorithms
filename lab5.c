#include <iostream>
#include <stdio.h>
#include "mpi.h"
using namespace std;

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	double time_start, time_finish;
	int rank, n, i;
	int multi = 1;
	int len;
	char* name = new char;
	MPI_Get_processor_name(name, &len);
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	time_start = MPI_Wtime();
	if (rank == 0)
	{
		int b[n];
		if (b[0] != 0)
		{
			MPI_Recv(&b[0], n, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			for (int j = 0; j < n; j++)
			{
				//cout << "Number is " << b[j] << endl;
				if ((b[j] % 2) == 0)
				{
					multi = multi * b[j];
					//cout << "Multiplication of even numbers " << multi << ", new multiplier is " << b[j] << endl;
				}
			}
		}
	}
	else
	{
		int a[n];
		for (int k = 0; k < n; k++)
		{
			a[k] = k+1;
			
		}
		MPI_Send(&a[0], n, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	time_finish = MPI_Wtime();
	cout << "processor " << name << ", process " << rank << " time = " << (time_finish - time_start) << endl;
	MPI_Finalize();
	return 0;
}