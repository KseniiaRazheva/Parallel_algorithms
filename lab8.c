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
    double T;

    for (int k = 1; k < (1000001); k=k*10)
    {
        double L = k * sizeof(int);
        int* a = new int[k];
        int* b = new int[k];
        if (rank == 0)
        {
            T = 0.0;
        }
        for (int av = 0; av < 10; av++)
        {
            for (int i = 0; i < k; i++)
            {
                a[i] = 1;
            }
            if (rank == 0)
            {
                double start_time = MPI_Wtime();
                MPI_Send(&a[0], k, MPI_INT, 1, 0, MPI_COMM_WORLD);
                MPI_Recv(&a[0], k, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
                double end_time = MPI_Wtime();
                T += end_time - start_time;
            }
            if (rank == 1)
            {
                MPI_Recv(&b[0], k, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
                MPI_Send(&b[0], k, MPI_INT, 0, 0, MPI_COMM_WORLD);
            }
        }
        delete[] a;
        delete[] b;
        if (rank == 0)
        {
            cout <<"k = " << k << ", L = " << (L/1024) << ", T = " << (T/10) << endl;
            double R = (2 * 10 * (L / (1024.0*1024.0))) / (T / 10);
            cout << "Bandwidth R = " << R << " MB/s" << endl;
        }  
    }
    int* c = new int[0];
    int* d = new int[0];
    if (rank == 0)
    {
        T = 0.0;
    }
    for (int av = 0; av < 10; av++)
    {
        if (rank == 0)
        {
            double start_time = MPI_Wtime();
            MPI_Send(&c[0], 0, MPI_INT, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&c[0], 0, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
            double end_time = MPI_Wtime();
            T += end_time - start_time;
        }
        if (rank == 1)
        {
            MPI_Recv(&d[0], 0, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            MPI_Send(&d[0], 0, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
    delete[] c;
    delete[] d;
    if (rank == 0)
    {
        cout << "T = " << (T / 10) << endl;
        double s = (T/10)/(2*10);
        cout << "Latency  s = " << s << endl;
    }
    MPI_Finalize();
    return 0;
}