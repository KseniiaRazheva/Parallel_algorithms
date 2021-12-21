#include <stdio.h>
#include <iostream>
#include "mpi.h"
#define n 10
using namespace std;

void max(void *a, void *b, int *l, MPI_Datatype *type) {
		b = 0;
		if (b < a)
		{
			b = a;
		}
	}

int main(int argc, char **argv)
{
	int rank, size, i;
	int a;
	int b;
	MPI_Init(&argc, &argv);
	MPI_Op op;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	a = rank + 7;
	
	//printf("process %d a[0] = %d\n", rank, a);
	MPI_Op_create(&max, 1, &op);
	MPI_Reduce(&a, &b, 1, MPI_INT, op , 0, MPI_COMM_WORLD);
	MPI_Op_free(&op);

	if (rank == 0)
	{
		cout << "Maximum number for my function " << b << endl;
	}

	MPI_Reduce(&a, &b, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		cout << "Maximum number for MPI_MAX function " << b << endl;
	}
		
	MPI_Finalize();
}