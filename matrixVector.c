void Read vector(double local a[],int local n, int n, char vec name[], int my rank, MPI_Comm comm){
	double∗ a = NULL;
	int i;

	if (my rank == 0) {
		a = malloc(n∗sizeof(double));
		printf("Enter the vector %s\n", vec name);
		for (i = 0; i < n; i++)
			scanf("%lf", &a[i]);
			MPI Scatter(a, local n, MPI DOUBLE, local a, local n, MPI DOUBLE, 0, comm);
		free(a);
	} else {
		MPI Scatter(a, local n, MPI DOUBLE, local a, local n, MPI DOUBLE, 0, comm);
	}
}



void Print vector(double local b[],	int local n, int n, char title[], int my rank. MPI Comm comm){
	double∗ b = NULL;
	int i;

	if (my rank == 0) {
		b = malloc(n∗sizeof(double));
		MPI Gather(local b, local n, MPI DOUBLE, b, local n, MPI DOUBLE, 0, comm);
		printf("%s\n", title);
		for (i = 0; i < n; i++)
			printf("%f ", b[i]);
		printf("\n");
		free(b);
	} else {
		MPI Gather(local b, local n, MPI DOUBLE, b, local n, MPI DOUBLE, 0, comm);
	}
}
