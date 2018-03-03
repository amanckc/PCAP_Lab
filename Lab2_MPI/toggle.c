#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv []) {

	int size, rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	char word[20];

	int i,l, len;

	if (rank == 0) {
		printf("Enter length\n");
		scanf("%d",&len);
		scanf("%s",word);

		MPI_Ssend(&len,1,MPI_INT, 1, 100, MPI_COMM_WORLD);
		MPI_Ssend(word, len, MPI_CHAR, 1, 101, MPI_COMM_WORLD);

		printf("%d. Sent: %s\n", rank, word);

		//MPI_Recv(word, len, MPI_CHAR, 1, 102, MPI_COMM_WORLD, &status);

		//printf("%d. Recv: %s\n", rank, word);

	} else {

		MPI_Recv(&l,1,MPI_INT, 0, 100, MPI_COMM_WORLD, &status);

		MPI_Recv(word, l, MPI_CHAR, 0, 101, MPI_COMM_WORLD, &status);

		printf("%d. Recv: %s\n", rank, word);

		for (i = 0; i < l; ++i) {
			char z = *(word + i);
			if (z >= 'A' && z <= 'Z')
				*(word + i) += 32;
			else if (z >= 'a' && z <= 'z')
				*(word + i) -= 32;
		}

		//MPI_Ssend(word, len, MPI_CHAR, 0, 102, MPI_COMM_WORLD);

		printf("%d. Sent: %s\n", rank, word);

	}

	MPI_Finalize();
}