#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "mpi.h"
using namespace std;
int main(int argc, char **argv)
{
	int r, message_recv;
	int message = 25;
	MPI_Init(&argc, &argv);
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Status status;
	MPI_Comm intercomm;
	MPI_Open_port(MPI_INFO_NULL, port_name);
	cout << "portname: " << port_name << endl;
	MPI_Comm_accept(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	cout << "Server connection" << endl;
	//MPI_Recv(&r, 1, MPI_INT, 0, 0, intercomm, &status);
	MPI_Send(&message, 1, MPI_INT, 0, 0, intercomm);
	cout << "Server sent value: " << message << endl;
	MPI_Recv(&message_recv, 1, MPI_INT, 0, 0, intercomm, &status);
	cout << "Server got value: " << message_recv << endl;
	MPI_Comm_free(&intercomm);
	MPI_Close_port(port_name);
	MPI_Finalize();
	return 0;
}
