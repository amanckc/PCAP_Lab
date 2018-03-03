#include "mpi.h"
#include<stdio.h>
#include<string.h>


int main(int argc, char *argv[]){
	int size,rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int num;

	if(rank == 0){
		for(int i = 0;i<size-1;i++){
			//printf("Enter number:\n");
			scanf("%d",&num);
			MPI_Send(&num,1,MPI_INT,i+1,100,MPI_COMM_WORLD);
		}
	}else{
		MPI_Recv(&num,1,MPI_INT,0,100,MPI_COMM_WORLD,&status);
		printf("%d\n",num);
	}

	MPI_Finalize();
}