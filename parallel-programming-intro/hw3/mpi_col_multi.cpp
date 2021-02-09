#include <mpi.h>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//#define DEBUG
/*
 * Modify the "multiply, run" to implement your parallel algorihtm.
 * Compile:
 *      this is a c++ style code
 */
using namespace std;

void serial(int n, double** matrix, double* vector, double** result);
void gen(int n, double*** matrix, double** vector);
void print(int n, double** matrix, double* vector);
void free(int n, double** matrix, double* vector);
void run(int n, double** matrix, double* vector);

int main(int argc, char* argv[]) {
	double** matrix = nullptr;
	double* vector = nullptr;
	if (argc < 2) {
		cout << "Usage: " << argv[0] << " n" << endl;
		return -1;
	}
	int n = atoi(argv[1]);
	run(n, matrix, vector);
	return 0;
}

void serial(int n, double** matrix, double* vector, double* result) {
	/*
	 * It is a serial algorithm to
	 * get the true value of matrix-vector multiplication
	 * please calculation the difference between true value and the value you obtain
	 *
	 */
	for (int i = 0; i < n; i++) {
		double temp = 0.0;
		for (int j = 0; j < n; j++) {
			temp += matrix[i][j] * vector[j];
		}
		result[i] = temp;
	}
}

void gen(int n, double*** matrix, double** vector) {
	/*
	 *  generate random matrix and vector,
	 *  In order to debug conveniently, you can define a const matrix and vector
	 *  but I will check your answer based on random matrix and vector
	 */
	(*matrix) = new double* [n];
	srand((unsigned)time(0));
	for (int i = 0; i < n; i++) {
		(*matrix)[i] = new double[n];
		for (int j = 0; j < n; j++) {
			(*matrix)[i][j] = -1 + rand() * 1.0 / RAND_MAX * 2;
		}
	}
	(*vector) = new double[n];
	for (int i = 0; i < n; i++) {
		(*vector)[i] = -1 + rand() * 1.0 / RAND_MAX * 2;
	}
}

void print(int n, double** matrix, double* vector) {
	for (int i = 0; i < n; i++) {
		cout << vector[i] << endl;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void printVector(int n, double* vector)
{
	for (int i = 0; i < n; i++)
	{
		cout << vector[i] << endl;
	}
}

void free(int n, double** matrix, double* vector) {
	delete[] vector;
	for (int i = 0; i < n; i++)
		delete[] matrix[i];
	delete[] matrix;
}

void printDiff(int n, double* vec1, double* vec2)
{
	double diff = 0.0;
	for (int i = 0; i < n; i++)
	{
		diff += fabs(vec1[i] - vec2[i]);
	}
	diff = sqrt(diff);
	cout << "error 2 norm: " << diff << endl;
}

void run(int n, double** matrix, double* vector) {
	 //init
	int myRank, commSize, localn;
	double serialTime, localParTime, parallelTime, localParTimeWoSca, parallelTimeWoSca;
	double* serialRes = nullptr, * parallelRes, * localParRes;
	serialRes = new double[n];
	memset(serialRes, n*sizeof(double), 0);
	MPI_Comm comm;
	MPI_Init(NULL, NULL);
	comm = MPI_COMM_WORLD;
	MPI_Comm_rank(comm, &myRank);
	MPI_Comm_size(comm, &commSize);
	localn = n / commSize;
	double* matrix1D = new double[n * n];
	double* localMat = new double[localn * n];
	double* localVec = new double[localn];
	parallelRes = new double[n];
	localParRes = new double[n];
	memset(parallelRes, 0, n * sizeof(double));
	if (myRank == 0)
	{
		gen(n, &matrix, &vector);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
			matrix1D[i * n + j] = matrix[i][j];
			}
		}
#ifdef DEBUG
		cout << "random matrix and vector" << endl;
		print(n, matrix, vector);
#endif // DEBUG
	}
	MPI_Datatype vectorBolok, tmpType;
	MPI_Type_vector(n, localn, n, MPI_DOUBLE, &tmpType);
	MPI_Type_create_resized(tmpType, 0, localn * sizeof(double), &vectorBolok);
	MPI_Type_commit(&vectorBolok);
	int* sendCounts = new int[commSize];
	int* displs = new int[commSize];
	for (int i = 0; i < commSize; i++)
	{
		sendCounts[i] = 1;
		displs[i] = i;
	}
	//serial
	if (myRank == 0)
	{
		double serialStrat = MPI_Wtime();
		serial(n, matrix, vector, serialRes);
		serialTime = MPI_Wtime() - serialStrat;
#ifdef DEBUG
		cout << "serial result" << endl;
		printVector(n, serialRes);
#endif // DEBUG
	}
	//parallel
	MPI_Barrier(comm);
	double parallelStart = MPI_Wtime();
	MPI_Scatterv(matrix1D, sendCounts, displs, vectorBolok, localMat, localn * n, MPI_DOUBLE, 0, comm);
	MPI_Scatter(vector, localn, MPI_DOUBLE, localVec, localn, MPI_DOUBLE, 0, comm);
	double localScaTime = MPI_Wtime() - parallelStart;
	for (int i = 0; i < n; i++)
	{
		double tmpSum = 0;
		for (int j = 0; j < localn; j++)
		{
			tmpSum += localMat[i * localn + j] * localVec[j];
		}
		localParRes[i] = tmpSum;
	}
	MPI_Reduce(localParRes, parallelRes, n, MPI_DOUBLE, MPI_SUM, 0, comm);
	localParTime = MPI_Wtime() - parallelStart;
	localParTimeWoSca = localParTime - localScaTime;
	MPI_Reduce(&localParTime, &parallelTime, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
	MPI_Reduce(&localParTimeWoSca, &parallelTimeWoSca, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
	if (myRank == 0)
	{
#ifdef DEBUG
		cout << "parallel result" << endl;
		printVector(n, parallelRes);
#endif // DEBUG
		printDiff(n, serialRes, parallelRes);
		cout << "Serial Time: " << serialTime << endl;
		cout << "Parallel Time: " << parallelTime << endl;
		cout << "Parallel Time Without Scattering: " << parallelTimeWoSca << endl;
	}
	//free
	MPI_Type_free(&vectorBolok);
	if (myRank == 0)
	{
		delete[] serialRes;
		free(n, matrix, vector);
	}
	delete[] localParRes;
	delete[] parallelRes;
	delete[] matrix1D;
	delete[] localMat;
	delete[] localVec;
	delete[] sendCounts;
	delete[] displs;
	MPI_Finalize();
}
