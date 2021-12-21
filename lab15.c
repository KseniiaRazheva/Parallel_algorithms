#include <iostream>
#include <cstdlib>
#include "mpi.h"
using namespace std;

int main(int argc, char **argv)
{
	int rank, size, i, rbuf;
	MPI_Init(&argc, &argv);
	MPI_Group group, new_group;
	MPI_Comm new_comm;
	int ranks[128], new_rank;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_group(MPI_COMM_WORLD, &group);

	for (i = 0; i < size / 2; i++) ranks[i] = i;

	if (rank < size / 2) MPI_Group_incl(group, size / 2, ranks, &new_group); 
	//MPI_Group_incl -  создает группу newgroup, которая состоит из size / 2 процессов из group с номерами ranks[0],..., ranks[128]
	// процесс с номером i в newgroup есть процесс с номером ranks[i] в group
	//

	else MPI_Group_excl(group, size / 2, ranks, &new_group);
	//MPI_GROUP_EXCL создает группу процессов newgroup, которая получена путем удаления из group процессов с номерами ranks[0],..., ranks[128].
	
	MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_comm);
	MPI_Allreduce(&rank, &rbuf, 1, MPI_INT, MPI_SUM, new_comm);
	//&rank - начальный адрес буфера посылки
	//&rbuf - начальный адрес буфера приема
	//1 - количество элементов в буфере посылки
	//MPI_SUM - операция

	MPI_Group_rank(new_group, &new_rank);
	
	//Display values: "rank =, newrank =, rbuf ="

	cout << "Rank = " << rank << ",  newrank = " << new_rank << ", rbuf = " << rbuf << endl;
	
	MPI_Finalize();
}