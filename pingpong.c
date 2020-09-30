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
	for(int i = 0;i<12;i++){
		if(my_rank == i%2){
			ball ++;
			printf("proceso %d goleo la pelota, ya van %d golpes \n",my_rank,ball);
			MPI_Send(&ball,1,MPI_INT,!my_rank,0,MPI_COMM_WORLD);
		}else{
			MPI_Recv(&ball,1,MPI_INT,!my_rank,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("proceso %d recibio la pelota de %d, ya van %d golpes \n",my_rank,!my_rank,ball);
		}
	}

	MPI_Finalize();	
	return 0;
}
