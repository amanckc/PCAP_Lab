#include<stdio.h>
#include "mpi.h"
#include<stdlib.h>

int main(int argc,char**argv){

	int size,rank;
	MPI_Status status;

	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int arr[1000];
	MPI_Buffer_attach(arr,1000);

	int x,i=0;
	
	if(rank==0){
		for(i=0;i<size-1;i++){
			scanf("%d",&x);
			MPI_Bsend(&x,1,MPI_INT,i+1,0,MPI_COMM_WORLD);
		}
	}
	else{
		if(rank%2==0){
			MPI_Recv(&x,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
			printf("Rank:%d, Number Received:%d, Modified Number:%d\n",rank,x,x*x);
		}
		else{
			MPI_Recv(&x,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
			printf("Rank:%d, Number Received:%d, Modified Number:%d\n",rank,x,x*x*x);
		}
	}
	MPI_Finalize();
}