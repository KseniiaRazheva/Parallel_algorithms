#include <iostream>
#include <mpi.h>
using namespace std;
int main(int argc, char** argv)
{
    int rank, size;
    int sum1 = 0;
    int sum2 = 0;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = 1000000;
    int n1 = n / size;
    int* a = new int[n];
    int* b = new int[n];
    int* sum = new int[size];
    int* a1 = new int[n];
    int* b1 = new int[n];
    if (rank == 0)
    {
        for (int i = 0; i < n; i++)
        {
            a[i] = 1;
            b[i] = 1;
        }
    }
    MPI_Scatter(&a[0], n1, MPI_INT, &a1[0], n1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&b[0], n1, MPI_INT, &b1[0], n1, MPI_INT, 0, MPI_COMM_WORLD);
    
    for (int i = 0; i < n1; i++)
    {
        sum1 += a1[i] * b1[i];
    }

    MPI_Gather(&sum1, 1, MPI_INT, &sum[0], 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (int i = 0; i < size; i++)
        {
            sum2 += sum[i];
        }
        cout << "Result " << sum2 << endl;
    }
    MPI_Finalize();
    return 0;

}