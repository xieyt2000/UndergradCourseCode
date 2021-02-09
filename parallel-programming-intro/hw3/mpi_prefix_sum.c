#define _CRT_SECURE_NO_WARNINGS
//#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

//generate a random array. elemet range: [0 ,9]
void genRandArr(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        arr[i] = rand() % 10;
    }
}

void printArr(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int commSz, myRank;
    int localArr[10], localSum[10];
    MPI_Comm comm;

    MPI_Init(NULL, NULL);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &commSz);
    MPI_Comm_rank(comm, &myRank);

    srand(10 * myRank + time(NULL));
    genRandArr(localArr, 10);

    printf("Random array from %d:  ", myRank);
    printArr(localArr, 10);

    localSum[0] = localArr[0];
    for (int i = 1; i < 10; i++)
    {
        localSum[i] = localSum[i - 1] + localArr[i];
    }
    int predSum;
    MPI_Scan(&localSum[9], &predSum, 1, MPI_INT, MPI_SUM, comm);
    for (int i = 0; i < 10; i++)
    {
        localSum[i] += predSum - localSum[9];
    }
#ifdef DEBUG
    printArr(localSum, 10);
#endif // DEBUG


    int* result = NULL;
    if (myRank == 0)
    {
        result = malloc(10 * commSz * sizeof(int));
    }
    MPI_Gather(localSum, 10, MPI_INT, result, 10, MPI_INT, 0, comm);
    if (myRank == 0)
    {
        printArr(result, 10 * commSz);
    }
    

    MPI_Finalize();

    return 0;
}
