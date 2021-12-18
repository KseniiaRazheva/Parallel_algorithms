#include <iostream>
#include <cstdlib>
#include <omp.h>
using namespace std;

int main (int argc, char *argv[]) {
    int N = atoi (argv [1]);
    int *array = new int[N];
    for (int i = 0; i < N; ++i)
    {
        array[i] = rand();
    }
    int max_element = array[0];
   for (int num_thread = 1; num_thread < 11; ++num_thread)
   {
       double t = omp_get_wtime();
#pragma omp parallel for reduction(max:max_element) num_threads(num_thread)
       for (int k = 0; k < N; k++)
       {
           if (max_element < array[k])
           {
               max_element = array[k];
           }
       }

       cout << "\n Max element = " << max_element;
       cout << "\n Number of threads = " << num_thread;
       cout << "\n Execution time in seconds = " << omp_get_wtime() - t;
   }
    delete[] array;
    return 0;
}