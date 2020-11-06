#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;
int main(void){
	int ball=0;
	int comm_sz;
	int my_rank;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if(my_rank != 0){
		MPI_Recv(&ball,1,MPI_INT,my_rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("proceso %d recibio la pelota de %d",my_rank,my_rank-1);
	}else{
		ball = ball+1;
	}

	MPI_Send(&ball,1,MPI_INT,(my_rank+1)%comm_sz,0,MPI_COMM_WORLD);

	if(my_rank == 0){
		MPI_Recv(&ball,1,MPI_INT,comm_sz-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("proceso %d recibe la pelota de proceso %d\n",my_rank,comm_sz-1);
	}
	MPI_Finalize();	
	return 0;
}
