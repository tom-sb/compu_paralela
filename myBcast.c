#include <stdio.h>
#include <string.h>
#include <mpi.h>

void myBcast(int my_rank, int comm_sz,int globalVar);
const int MAX_STRING = 100;
int main(void){
	int globalVar=0;
	int local=0;
	int comm_sz;
	int my_rank;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	myBcast(my_rank,comm_sz,globalVar);

	local = 3;
	MPI_Reduce(&local,&globalVar,1,MPI_INT,MPI_PROD,0,MPI_COMM_WORLD);

	if(my_rank == 0){
		printf("la suma es: %d\n",globalVar);
	}
	MPI_Finalize();	
	return 0;
}

void myBcast(int my_rank, int comm_sz,int globalVar){
	for(int i = 0;i < comm_sz;i++){
		if(i == my_rank){
			MPI_Send(&globalVar,1,MPI_INT,my_rank,0,MPI_COMM_WORLD);
		}
	}
}
