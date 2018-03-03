#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv []) {

	int size, rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int len,l;
	int arr[25];

	int sum;
	double t1, t2;

	if (rank == 0) {

		scanf("%d",&len);
		for (int i = 0; i < len; ++i) {
			scanf("%d",&arr[i]);
		}
		
		MPI_Ssend(&len,1,MPI_INT,1,100,MPI_COMM_WORLD);
		MPI_Ssend(&arr, len, MPI_INT, 1, 101, MPI_COMM_WORLD);

	} else {

		t1 = MPI_Wtime();
		
		MPI_Recv(&l,1,MPI_INT,0,100,MPI_COMM_WORLD, &status);
		MPI_Recv(&arr, l, MPI_INT, 0, 101, MPI_COMM_WORLD, &status);

		sum = 0;
		for (int i = 0; i < l; ++i) {
			sum += *(arr + i);
		}	

		t2 = MPI_Wtime();

		printf("%d. Sum: %d (%lf s)\n", rank, sum, t2 - t1);

	} 

	MPI_Finalize();
}