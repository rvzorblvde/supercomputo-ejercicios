/* Libraries */
#include <stdio.h>      // IO Funcitons
#include <stdlib.h>     // Use of rand()
#include <time.h>       // Use of time() for the random seed

/* Numeric constants */
#define N 12    // Array size

/* Function prototypes */
void fillArray (int arrayA[N], int arrayB[N]);                          // Fill arrays with random numbers
void showArrays (int arrayA[N], int arrayB[N]);                         // Show the arrays created in the previous function
void arrayAdditions(int arrayA[N], int arrayB[N], int arrayC[N]);       // Add the arrays into a new one
void showResults(int arrayC[N]);                                        // Show the results of the new array

/* Main Function */
int main ()
{
    srand(time(NULL));     // Intializes seed for random numbers

    int A[N];
    int B[N];
    int C[N];

    fillArray(A, B);
    showArrays(A, B);
    arrayAdditions(A, B, C);
    showResults(C);

    return (0);
}

void fillArray (int arrayA[N], int arrayB[N]) {
    int i;

    for (i = 0; i < N; i++) {
        arrayA[i] = rand() % 10 + 1;
        arrayB[i] = rand() % 10 + 1;
    }
}

void showArrays (int arrayA[N], int arrayB[N]) {
    int i;

    printf("\nArreglo A:\n");
    for (i = 0; i < N; i++) {
        printf("%d\t", arrayA[i]);
    }
    printf("\n");

    printf("\nArreglo B: \n");
    for (i = 0; i < N; i++) {
        printf("%d\t", arrayB[i]);
    }
    printf("\n");
}

void arrayAdditions(int arrayA[N], int arrayB[N], int arrayC[N]) {
    int i;
    for (i = 0; i < N; i++) {
        arrayC[i] = arrayA[i] + arrayB[i];
    }
}

void showResults(int arrayC[N]) {
    int i;

    printf("\nArreglo C:\n");
    for (i = 0; i < N; i++) {
        printf("%d\t", arrayC[i]);
    }
    printf("\n");
}
