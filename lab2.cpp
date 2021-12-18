#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

using namespace std;

// The function of allocating memory for a two-dimensional array
double** malloc_array(long int n)
{
    double** matrix = new double*[n];
    for (int i = 0; i < n; i++)
        matrix[i] = new double[n];
    return matrix;
}

// Memory free function
void free_array(double** matrix,long int n)
{
    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;
}

// The function of initializing a matrix with random numbers from [0,1]
void rand_init_matrix(double** matrix,long int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = rand() / RAND_MAX;
}


// Matrix zeroing function
void zero_init_matrix(double** matrix, long int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0.0 ;
}

int main (int argc, char *argv[]) {
    int N = atoi (argv [1]);
    double** A, **B, **C;
    int num_thread = 10;
    cout << "Number of treads = " << num_thread << endl;

// Memory allocation for matrices A, B, C
    A = malloc_array(N);
    B = malloc_array(N);
    C = malloc_array(N);

// Initialization of matrices
    rand_init_matrix(A, N);
    rand_init_matrix(B, N);
    zero_init_matrix(C, N);
    clock_t t1;
    double t;

// Matrix multiplication with cycle order ijk
//Without omp
    t1 = clock();
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
    t1 = (clock() - t1)/ CLOCKS_PER_SEC;
    cout << "WITHOUT omp Time ijk loops is " << t1 << " seconds" <<  endl;

    //With omp
    zero_init_matrix(C, N);
    t = omp_get_wtime();
#pragma omp parallel num_threads(num_thread)
    {
#pragma omp for
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                for (int k = 0; k < N; k++)
                    C[i][j] += A[i][k] * B[k][j];
    }
    t = omp_get_wtime() - t;
    cout << "WITH omp Time ijk loops is " << t << " seconds" <<  endl;
cout << "Efficiency for ijk loops " << t1/t << endl;

// Matrix multiplication with cycle order jki
//Without omp
    zero_init_matrix(C, N);
    t1 = clock();
    for (int j = 0; j < N; j++)
        for (int k = 0; k < N; k++)
            for (int i = 0; i < N; i++)
                C[i][j] += A[i][k] * B[k][j];
    t1 = (clock() - t1)/ CLOCKS_PER_SEC;
    cout << "WITHOUT omp Time jki loops is " << t1 << " seconds" <<  endl;

    //With omp
    zero_init_matrix(C, N);
    t = omp_get_wtime();
#pragma omp parallel num_threads(num_thread)
    {
#pragma omp for
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                for (int i = 0; i < N; i++)
                    C[i][j] += A[i][k] * B[k][j];
    }
    t = omp_get_wtime() - t;
    cout << "WITH omp Time jki loops is " << t << " seconds" <<  endl;
    cout << "Efficiency for jki loops " << t1/t << endl;

// Matrix multiplication with cycle order ikj
//Without omp
    zero_init_matrix(C, N);
    t1 = clock();
    for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++)
            for (int j = 0; j < N; j++)
                C[i][j] += A[i][k] * B[k][j];
    t1 = (clock() - t1)/ CLOCKS_PER_SEC;
    cout << "WITHOUT omp Time ikj loops is " << t1 << " seconds" << endl;

    //With omp
    zero_init_matrix(C, N);
    t = omp_get_wtime();
#pragma omp parallel num_threads(num_thread)
    {
#pragma omp for
        for (int i = 0; i < N; i++)
            for (int k = 0; k < N; k++)
                for (int j = 0; j < N; j++)
                    C[i][j] += A[i][k] * B[k][j];
    }
    t = omp_get_wtime() - t;
    cout << "WITH omp Time ikj loops is " << t << " seconds" <<  endl;
    cout << "Efficiency for ikj loops " << t1/t << endl;

// Freeing memory occupied by matrices A, B, C
    free_array(A, N);
    free_array(B, N);
    free_array(C, N);

    return 0;
}