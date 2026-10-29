#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

// Prototipos de funciones
int* crearArreglo(int tam);
void llenarArreglo(int *a, int tam);
void imprimirArreglo(int *a, int tam);

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int idProc, numProc;
    int suma = 0;
    int *array = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProc);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);

    if (argc != 2) {
        if (idProc == 0) {
            fprintf(stderr, "Uso: mpirun -np <procesos> %s <tamano_arreglo>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    int N = atoi(argv[1]);

    if (N <= 0) {
        if (idProc == 0) {
            fprintf(stderr, "Error: El tamaño del arreglo debe ser mayor a 0.\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (numProc < 2) {
        if (idProc == 0) {
            fprintf(stderr, "Error: Se requieren al menos 2 procesos (1 maestro, n-1 trabajadores).\n");
        }
        MPI_Finalize();
        return 1;
    }

    int nDatos = N / (numProc - 1);
    int nDatosU = nDatos + (N % (numProc - 1));

    if (idProc == 0) {
        array = crearArreglo(N);
        llenarArreglo(array, N);

        for (int iProc = 1; iProc <= numProc - 2; iProc++) {
            int offset = (iProc - 1) * nDatos;
            MPI_Send(&array[offset], nDatos, MPI_INT, iProc, 0, MPI_COMM_WORLD);
        }

        int offsetU = (numProc - 2) * nDatos;
        MPI_Send(&array[offsetU], nDatosU, MPI_INT, numProc - 1, 0, MPI_COMM_WORLD);

        imprimirArreglo(array, N);
        printf("\nSumas Parciales\n");

        for (int iProc = 1; iProc <= numProc - 1; iProc++) {
            int sumap = 0;
            MPI_Recv(&sumap, 1, MPI_INT, iProc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Proceso %d = Suma parcial: %d\n", iProc, sumap);
            suma += sumap;
        }

        printf("Suma total: %d\n", suma);

    } else {
        if (idProc == numProc - 1) {
            nDatos = nDatosU;
        }

        array = crearArreglo(nDatos);

        MPI_Recv(array, nDatos, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 0; i < nDatos; i++) {
            suma += array[i];
        }

        MPI_Send(&suma, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (array != NULL) {
        free(array);
    }

    MPI_Finalize();
    return 0;
}

int* crearArreglo(int tam) {
    int *a = (int *)malloc(tam * sizeof(int));
    if (a == NULL) {
        fprintf(stderr, "Error al asignar memoria dinámica.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    return a;
}

void llenarArreglo(int *a, int tam) {
    for (int i = 0; i < tam; i++) {
        a[i] = rand() % 10;
    }
}

void imprimirArreglo(int *a, int tam) {
    printf("Arreglo completo: ");
    for (int i = 0; i < tam; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
