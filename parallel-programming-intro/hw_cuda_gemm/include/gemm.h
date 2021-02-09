// studentid: 2018011334
#include "util.h"
#include <cstdio>

//choose strategy
//#define BASELINE
//#define BLOCK
#define OUTER_PRODUCT

//A: M*K B:K*N C:M*N

//baseline parameter
const int DIM_THREAD_BLOCK_X = 32;
const int DIM_THREAD_BLOCK_Y = 8;

//copy from gemm in main.cu
template <class T>
__global__ void baseline(T *A, T *B, T *C, int m, int n, int k, T alpha, T beta)
{
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	// printf("col %d row %d\n", col, row);
	if ((col < n) && (row < m))
	{
		T tmp = beta * C[row * n + col];
		for (int i = 0; i < k; ++i)
		{
			tmp += alpha * A[row * k + i] * B[col + i * n];
		}
		C[row * n + col] = tmp;
	}
}

//dim of matrix block
const int DIM_BLOCK = 32;

template <class T>
__global__ void gemmBlock(T *A, T *B, T *C, int m, int n, int k, T alpha, T beta)
{
	int blockX = blockIdx.x, blockY = blockIdx.y;
	int threadX = threadIdx.x, threadY = threadIdx.y;

	//postition of C
	int col = blockX * DIM_BLOCK + threadX;
	int row = blockY * DIM_BLOCK + threadY;
	bool validRow = row < m, validCol = col < n;

	__shared__ T ABlock[DIM_BLOCK][DIM_BLOCK];
	__shared__ T BBlock[DIM_BLOCK][DIM_BLOCK];

	T tmp = 0;
	for (int ACol = threadX, BRow = threadY;
		 ACol < k || BRow < k;
		 ACol += DIM_BLOCK, BRow += DIM_BLOCK)
	{
		//read into shared mem
		if (validRow && ACol < k)
		{
			ABlock[threadY][threadX] = A[row * k + ACol];
		}
		if (validCol && BRow < k)
		{
			BBlock[threadY][threadX] = B[(BRow)*n + col];
		}
		__syncthreads();
		//calculate
		int AColBound = k - (ACol - threadX);
		if (validRow && validCol)
		{
			for (int i = 0;
				 i < DIM_BLOCK && i < AColBound; //assert row of BBlock is in bound
				 i++)
			{
				tmp += ABlock[threadY][i] * BBlock[i][threadX];
			}
		}
		__syncthreads();
	}
	if (validRow && validCol)
	{
		C[row * n + col] = alpha * tmp + beta * C[row * n + col];
	}
}

//size(dim) of block and vector
const int VEC_SIZE = 4;
const int BLOCK_SIZE = 16;
template <class T>
__global__ void gemmOuterProduct(T *A, T *B, T *C, int m, int n, int k, T alpha, T beta)
{
	int blockX = blockIdx.x, blockY = blockIdx.y;
	int threadX = threadIdx.x, threadY = threadIdx.y;

	__shared__ T ABlock[BLOCK_SIZE][BLOCK_SIZE];
	T CVec[BLOCK_SIZE] = {0};

	int ARowBegin = blockY * BLOCK_SIZE, BColBegin = BLOCK_SIZE * VEC_SIZE * blockX;
	int row = ARowBegin, col = BColBegin + BLOCK_SIZE * threadY + threadX;
	bool validCol = col < n;

	for (int AColBegin = 0, BRowBegin = 0;
		 AColBegin < k; //assert BRowBegin < k
		 AColBegin += BLOCK_SIZE, BRowBegin += BLOCK_SIZE)
	{
		//read into shared mem
		for (int i = 0; i < BLOCK_SIZE / VEC_SIZE; i++)
		{
			if ((AColBegin + threadX) < k && (ARowBegin + (i * VEC_SIZE + threadY)) < m)
			{
				//transpose to avoid bank conflict
				ABlock[threadX][i * VEC_SIZE + threadY] = A[k * (i * VEC_SIZE + threadY + ARowBegin) + threadX + AColBegin];
			}
			else
			{
				ABlock[threadX][i * VEC_SIZE + threadY] = 0;
			}
		}
		__syncthreads();
		//calculate
		if (validCol) //column in bound
		{
			T *BPtr = &B[BRowBegin * n + BLOCK_SIZE * threadY + threadX + BColBegin];
			for (int i = 0;
				 i < BLOCK_SIZE && (BRowBegin + i) < k;
				 i++, BPtr += n) //row in bound
			{
				T b = *BPtr;
				for (int j = 0; j < BLOCK_SIZE; j++)
				{
					CVec[j] += ABlock[i][j] * b;
				}
			}
		}
		__syncthreads();
	}
	//reduce result
	if (validCol)
	{
		for (int i = 0; i < BLOCK_SIZE && row < m; i++, row++)
		{
			C[n * row + col] = alpha * CVec[i] + beta * C[n * row + col];
		}
	}
}

template <class T>
double myGEMM(T *A, T *B, T *C, T alpha, T beta)
{
	printf("perform your gemm here on m=%d n=%d k=%d\n", M, N, K);
	bool preprocess = false;
	if (preprocess)
	{
		// your preprocess
		timestamp(t0);
		// your gemm

		checkCudaErrors(cudaDeviceSynchronize());
		timestamp(t1);
		return getDuration(t0, t1);
	}
	else
	{
		// your gemm
#ifdef BASELINE
		//baseline from main.cu
		dim3 block(DIM_THREAD_BLOCK_X, DIM_THREAD_BLOCK_Y);
		dim3 grid((N + block.x - 1) / block.x, (M + block.y - 1) / block.y);
		baseline<<<grid, block>>>(A, B, C, M, N, K, alpha, beta);
#endif
		//Block matrix multiplication
#ifdef BLOCK
		dim3 block(DIM_BLOCK, DIM_BLOCK);
		dim3 grid((N + block.x - 1) / block.x, (M + block.y - 1) / block.y);
		gemmBlock<<<grid, block>>>(A, B, C, M, N, K, alpha, beta);
#endif
#ifdef OUTER_PRODUCT
		dim3 block(BLOCK_SIZE, VEC_SIZE);
		dim3 grid((N + BLOCK_SIZE * VEC_SIZE - 1) / (BLOCK_SIZE * VEC_SIZE), (M + BLOCK_SIZE - 1) / BLOCK_SIZE);
		gemmOuterProduct<<<grid, block>>>(A, B, C, M, N, K, alpha, beta);
#endif
		checkCudaErrors(cudaDeviceSynchronize());
		return 0.f;
	}
}
