#include <mpi.h>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <omp.h>
//#define DEBUG
/*
 * Modify the "multiply, run" to implement your parallel algorihtm.
 * Compile:
 *      this is a c++ style code
 */
using namespace std;

void serial(int n, double** matrix, double* vector, double** result, int localn);
void gen(int n, double*** matrix, double** vector);
void print(int n, double** matrix, double* vector);
void free(int n, double** matrix, double* vector);
void run(int n, double** matrix, double* vector, int numThreads);

int main(int argc, char* argv[]) {
	double** matrix = nullptr;
	double* vector = nullptr;
	if (argc < 3) {
		cout << "Usage: " << argv[0] << " n" << endl;
		return -1;
	}
	int n = atoi(argv[1]);
	int numThreads = atoi(argv[2]);
	run(n, matrix, vector, numThreads);
	return 0;
}

void serial(int n, double** matrix, double* vector, double* result, int localn) {
	/*
	 * It is a serial algorithm to
	 * get the true value of matrix-vector multiplication
	 * please calculation the difference between true value and the value you obtain
	 *
	 */
	const int matPerRow = n / localn;	//how many submatrix in one row? == n / localn;
	for (int i = 0; i < matPerRow; i++)
	{
		for (int j = 0; j < matPerRow; j++)
		{
			const int vectorStart = j * localn, resVectorStart = i * localn;
			for (int ii = 0; ii < localn; ii++)
			{
				double tmpRes = 0;
				for (int jj = 0; jj < localn; jj++)
				{
					tmpRes += matrix[resVectorStart + ii][vectorStart + jj] * vector[vectorStart + jj];
				}
				result[resVectorStart + ii] += tmpRes;
			}
		}
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

double serialDiff(int n, double* vec1, double* vec2)
{
	double diff = 0.0;
	for (int i = 0; i < n; i++)
	{
		diff += (vec1[i] - vec2[i]) * (vec1[i] - vec2[i]);
	}
	diff = sqrt(diff);
	return diff;
}

double ompDiff(int n, double* vec1, double* vec2, int numThreads)
{
	double diff = 0.0;
#pragma omp parallel for num_threads(numThreads) reduction(+ : diff)
	for (int i = 0; i < n; i++)
	{
		diff += (vec1[i] - vec2[i]) * (vec1[i] - vec2[i]);
	}
	diff = sqrt(diff);
	return diff;
}

void run(int n, double** matrix, double* vector, int numThreads) 
{
	//init
	int myRank, commSize, localn;
	double serialTime, localMPICompTime, MPICompTime, MPIComuTime, localMPIComuTime, localOmpCompTime, ompCompTime;
	double* serialRes = nullptr, * MPIRes, * localMPIRes;
	serialRes = new double[n];
	memset(serialRes, n * sizeof(double), 0);
	MPI_Comm comm;
	MPI_Init(NULL, NULL);
	comm = MPI_COMM_WORLD;
	MPI_Comm_rank(comm, &myRank);
	MPI_Comm_size(comm, &commSize);
	int sqrComSize = sqrt(commSize);
	localn = n / sqrComSize;	//localn * localn matrix \times localn vector
	int vectorStart = myRank % sqrComSize * localn;
	int resVecStart = myRank / sqrComSize * localn;
	double* matrix1D = new double[n * n];
	double* localMat = new double[localn * localn];
	MPIRes = new double[n];
	localMPIRes = new double[n];
	memset(MPIRes, 0, n * sizeof(double));
	memset(localMPIRes, 0, n * sizeof(double));
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
	else
	{
		vector = new double[n];
	}
	MPI_Datatype matBolok, tmpType;
	MPI_Type_vector(localn, localn, n, MPI_DOUBLE, &tmpType);
	MPI_Type_create_resized(tmpType, 0, localn * sizeof(double), &matBolok);
	MPI_Type_commit(&matBolok);
	int* sendCounts = new int[commSize];
	int* displs = new int[commSize];
	for (int i = 0; i < sqrComSize; i++)
	{
		for (int j = 0; j < sqrComSize; j++)
		{
			sendCounts[i * sqrComSize + j] = 1;
			displs[i * sqrComSize + j] = i * n + j;
		}
	}
	//serial
	if (myRank == 0)
	{
		memset(serialRes, 0, n * sizeof(double));
		double serialStrat = MPI_Wtime();
		serial(n, matrix, vector, serialRes, localn);
		serialTime = MPI_Wtime() - serialStrat;
#ifdef DEBUG
		cout << "serial result" << endl;
		printVector(n, serialRes);
#endif // DEBUG
	}

	//MPI
	double MPIStart, MPICompStart, MPICompFin, MPIFin;
	MPI_Barrier(comm);
	MPIStart = MPI_Wtime();
	MPI_Scatterv(matrix1D, sendCounts, displs, matBolok, localMat, localn * localn, MPI_DOUBLE, 0, comm);
	MPI_Bcast(vector, n, MPI_DOUBLE, 0, comm);

	//compute without omp. output the diff with serial
	MPICompStart = MPI_Wtime();
	for (int i = 0; i < localn; i++)
	{
		double tmpSum = 0;
		for (int j = 0; j < localn; j++)
		{
			tmpSum += localMat[i * localn + j] * vector[vectorStart + j];
		}
		localMPIRes[resVecStart + i] = tmpSum;
	}
	MPICompFin = MPI_Wtime();
	MPI_Reduce(localMPIRes, MPIRes, n, MPI_DOUBLE, MPI_SUM, 0, comm);
	MPIFin = MPI_Wtime();
	if (myRank == 0)
	{
		cout << "MPI without openmp vs serial result diff" << endl;
		double diff = serialDiff(n, serialRes, MPIRes);
		cout << "error 2 norm (by serial): " << diff << endl;
	}

	//compute with omp. keep the result
	MPI_Barrier(comm);
	double ompCompStart, ompCompFin;
	ompCompStart = MPI_Wtime();
#pragma omp parallel for num_threads(numThreads)
	for (int i = 0; i < localn; i++)
	{
		double tmpSum = 0;
		for (int j = 0; j < localn; j++)
		{
			tmpSum += localMat[i * localn + j] * vector[vectorStart + j];
		}
		localMPIRes[resVecStart + i] = tmpSum;
	}
	ompCompFin = MPI_Wtime();

	MPI_Reduce(localMPIRes, MPIRes, n, MPI_DOUBLE, MPI_SUM, 0, comm);
	localMPICompTime = MPICompFin - MPICompStart;
	localMPIComuTime = MPIFin - MPIStart - localMPICompTime;
	localOmpCompTime = ompCompFin - ompCompStart;
	MPI_Reduce(&localMPICompTime, &MPICompTime, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
	MPI_Reduce(&localMPIComuTime, &MPIComuTime, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
	MPI_Reduce(&localOmpCompTime, &ompCompTime, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
	
	if (myRank == 0)
	{
#ifdef DEBUG
		cout << "parallel result" << endl;
		printVector(n, parallelRes);
#endif // DEBUG
		cout << "MPI with oenmp vs serial result diff" << endl;
		double serDiffTimeStart = MPI_Wtime();
		double diff = serialDiff(n, serialRes, MPIRes);
		double serDiffTime = MPI_Wtime() - serDiffTimeStart;
		cout << "error 2 norm (by serial): " << diff << endl;
		double ompDiffTimeStart = MPI_Wtime();
		diff = ompDiff(n, serialRes, MPIRes, numThreads);
		double ompDiffTime = MPI_Wtime() - ompDiffTimeStart;
		cout << "error 2 norm (by openmp): " << diff << endl;
		cout << "Serial 2-norm time: " << serDiffTime << endl;
		cout << "Openmp 2-norm time: " << ompDiffTime << endl;
		cout << "Serial matrix time: " << serialTime << endl;
		cout << "MPI computing time: " << MPICompTime << endl;
		cout << "MPI communicating time: " << MPIComuTime << endl;
		cout << "OMP computing time: " << ompCompTime << endl;
	}
	//free
	MPI_Type_free(&matBolok);
	if (myRank == 0)
	{
		delete[] serialRes;
		free(n, matrix, vector);
	}
	delete[] localMPIRes;
	delete[] MPIRes;
	delete[] matrix1D;
	delete[] localMat;
	delete[] sendCounts;
	delete[] displs;
	MPI_Finalize();
}
