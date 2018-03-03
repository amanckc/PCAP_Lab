#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv []) {

	int size, rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int number;
	
	int i;

	if (rank == 0) {

		scanf("%d",&number);
		MPI_Ssend(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&number, 1,MPI_INT, size -1,0, MPI_COMM_WORLD,&status);
		printf("%d\n",number);


	} else {
		MPI_Recv(&number, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
		number++;
		MPI_Send(&number, 1,MPI_INT, (rank+1)%size,0,MPI_COMM_WORLD);
	}

	MPI_Finalize();
}