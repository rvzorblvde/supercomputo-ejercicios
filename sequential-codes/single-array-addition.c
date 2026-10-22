#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 8

/* Function prototypes */
void fillArray(int array[N]);
int addition(int array[N]);
void showResults(int res);

int main()
{
    srand(time(0));

    int array[N];
    int res;

    fillArray(array);
    res = addition(array);
    showResults(res);

    return (0);
}

void fillArray(int array[N]) {
    int i;

    printf("\n Array: \t");

    for (i = 0; i < N; i++) {
        array[i] = rand() % 10 + 1;
        printf("%d \t", array[i]);
    }

    printf("\n\n");
}

int addition(int array[N]){
    int i, acum = 0;

    for (i = 0; i < N; i++) {
        acum += array[i];
    }

    return(acum);
}

void showResults(int res) {
    printf("\nResult: %d\n", res);
}
