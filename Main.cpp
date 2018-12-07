#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
	int tam = atoi(argv[1]);
	int size, rank, sum = 0, i, j, k;
	int **a, **b, **c;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Começa a contar o tempo:
	double start = MPI_Wtime();

	// Criando um array de ponteiros
	a = (int **)malloc(tam * sizeof(int*));
	b = (int **)malloc(tam * sizeof(int*));
	c = (int **)malloc(tam * sizeof(int*));

	// Alocando memória para as matrizes
	for (i = 0; i < tam; i++) {
		a[i] = (int *)malloc(tam * sizeof(int));	// Matriz 1
		b[i] = (int *)malloc(tam * sizeof(int));	// Matriz 2
		c[i] = (int *)malloc(tam * sizeof(int));	// Matriz resultado
	}

	// Inicializando as matrizes e colocando valor 1 dentro
	for (i = 0; i < tam; i++) {
		for (j = 0; j < tam; j++) {
			a[i][j] = 1;
			b[i][j] = 1;
		}
	}

	// Dividindo as tarefas nos para os processos
	for (i = rank; i < tam; i = i + size) {
		for (j = 0; j < tam; j++) {
			sum = 0;
			for (k = 0; k < tam; k++) {
				sum = sum + a[i][k] * b[k][j];
			}
			c[i][j] = sum;
		}
	}

	// Se não for o master, ele envia o resultado para o rank master
	if (rank != 0) {
		for (i = rank; i < tam; i = i + size)
			MPI_Send(&c[i][0], tam, MPI_INT, 0, 10 + i, MPI_COMM_WORLD);
	}

	// Rank master, ele receberá todas as partes calculadas dos outros processos
	if (rank == 0) {
		for (j = 1; j < size; j++) {
			for (i = j; i < tam; i = i + size) {
				MPI_Recv(&c[i][0], tam, MPI_INT, j, 10 + i, MPI_COMM_WORLD, &status);
			}
		}
	}

	// Espera até ter o resultado completo então imprime a matriz resultado
	MPI_Barrier(MPI_COMM_WORLD);

	// Imprimindo Matriz:
	/*if (rank == 0) {
		for (i = 0; i < tam; i++) {
			for (j = 0; j < tam; j++) {
				printf("%d\t", c[i][j]);
			}
			printf("\n");
		}
	}*/
	
	// Finalizando MPI
	double end = MPI_Wtime();
	if (rank == 0)
		printf("Tempo total: %.5f", end - start);
		MPI_Finalize();
	return 0;
}
