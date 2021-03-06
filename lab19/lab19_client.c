#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char **argv)
{
	int rank, message_recv;
	int message = 42;
	MPI_Init(&argc, &argv);
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Status status;
	MPI_Comm intercomm;
	strcpy(port_name, argv[1]);
	cout << "Attempt to connect" << endl;
	MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	//MPI_Send(&rank, 1, MPI_INT, 0, 0, intercomm);
	cout << "Server connection" << endl;
	MPI_Send(&message, 1, MPI_INT, 0, 0, intercomm);
	cout << "Client sent value: " << message << endl;
	MPI_Recv(&message_recv, 1, MPI_INT, 0, 0, intercomm, &status);
	cout << "Client got value: " << message_recv << endl;
	MPI_Finalize();
	return 0;
}