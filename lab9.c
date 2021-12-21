#include <iostream>
#include <mpi.h>
using namespace std;
int main(int argc, char** argv)
{
    int rank, size;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int sum1 = 0;
    double T;
    int n = 1000000;
    int n1 = n / size;
    int* a = new int[n];
    int* a1 = new int[n1];
    int* sum = new int[size];
    int sumReduce = 0;
    double start_time;

    //With cascade model
    if (rank == 0)
    {
        T = 0.0;
        for (int i = 0; i < n; i++)
        {
            a[i] = 1;
        }
        start_time = MPI_Wtime();
    }

    MPI_Scatter(&a[0], n1, MPI_INT, &a1[0], n1, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < n1; i++)
    {
        sum1 += a1[i];
    }

    if (rank == 1)
    {
        MPI_Send(&sum1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    if (rank == 0)
    {
        cout << "Summation at the stage of 4 processes " << sum1 << endl;
        MPI_Recv(&sum[0], 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        sum1 += sum[0];
        cout << "Summation at the stage of 2 processes " << sum1 << endl;
        MPI_Recv(&sum[0], 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);
        sum1 += sum[0];
        cout << "Summation at the stage of 1 processes " << sum1 << endl;
        double end_time = MPI_Wtime();
        T += end_time - start_time;
        cout << "Time spent on cascade model " << T << "sec." << endl;
    }
    if (rank == 3)
    {
        MPI_Send(&sum1, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
    }
    if (rank == 2)
    {
        MPI_Recv(&sum[0], 1, MPI_INT, 3, 0, MPI_COMM_WORLD, &status);
        sum1 += sum[0];
        MPI_Send(&sum1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    //With MPI_Reduce
    sum1 = 0;
    if (rank == 0)
    {
        T = 0.0;
        for (int i = 0; i < n; i++)
        {
            a[i] = 1;
        }
        start_time = MPI_Wtime();
    }

    MPI_Scatter(&a[0], n1, MPI_INT, &a1[0], n1, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < n1; i++)
    {
        sum1 += a1[i];
    }

    MPI_Reduce(&sum1, &sumReduce, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        cout << "Summation when using MPI_Reduce " << sumReduce << endl;
        double end_time = MPI_Wtime();
        T += end_time - start_time;
        cout << "Time spent when using MPI_Reduce " << T << "sec." << endl;
    }

    MPI_Finalize();
    return 0;
}