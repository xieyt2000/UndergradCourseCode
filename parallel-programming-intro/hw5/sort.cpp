#include <omp.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>

//#define QSORT
// #define SER_COUNT_SORT
// #define PAR_COUNT_SORT
// #define SER_FAST_COUNT_SORT
#define PAR_FAST_COUNT_SORT

using std::qsort;
using std::cout;
using std::endl;
const int MAX = 50;	//all elements in array is in range [0, MAX)
using std::is_sorted;
using std::memset;


int cmpInt(const void* a, const void* b)
{
	int aInt = *(int*)a, bInt = *(int*)b;
	//avoid overfolow
	if (aInt < bInt)
	{
		return -1;
	}
	if (aInt > bInt)
	{
		return 1;
	}
	return 0;
}

void outputArr(const int a[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void serCountSort(const int a[], const int n, int res[])
{
	for (int i = 0; i < n; i++)
	{
		int count = 0;
		for (int j = 0; j < n; j++)
		{
			if (a[j] < a[i])
			{
				count++;
			}
			else if (a[j] == a[i] && j < i)
			{
				count++;
			}
		}
		res[count] = a[i];
	}
}

void parCountSort(const int a[], const int n, int res[], int numThreads)
{
#pragma omp parallel for num_threads(numThreads)
	for (int i = 0; i < n; i++)
	{
		int count = 0;
		for (int j = 0; j < n; j++)
		{
			if (a[j] < a[i])
			{
				count++;
			}
			else if (a[j] == a[i] && j < i)
			{
				count++;
			}
		}
		res[count] = a[i];
	}
}

void serFastCountSort(const int a[], const int n, int res[])
{
	int count[MAX];
	memset(count, 0, MAX * sizeof(int));
	int resRank = 0;
	for (int i = 0; i < n; i++)
	{
		count[a[i]]++;
	}
	int countAccu[MAX];
	countAccu[0] = count[0];
	for (int i = 1; i < MAX; i++)
	{
		countAccu[i] = count[i] + countAccu[i - 1];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (i < countAccu[j])
			{
				res[i] = j;
				break;
			}
		}
	}
}

void parFastSort(const int a[], const int n, int res[], int numThreads)
{
	int globalCount[MAX];
	memset(globalCount, 0, MAX * sizeof(int));
	int resRank = 0;
#pragma omp parallel num_threads(numThreads)
	{
#pragma omp for reduction(+: globalCount)
		for (int i = 0; i < n; i++)
		{
			globalCount[a[i]]++;
		}
		int countAccu[MAX];
		countAccu[0] = globalCount[0];
		for (int i = 1; i < MAX; i++)
		{
			countAccu[i] = globalCount[i] + countAccu[i - 1];
		}
#pragma omp for schedule(guided, 100000)
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				if (i < countAccu[j])
				{
					res[i] = j;
					break;
				}
			}
		}
	}
}

void outputSorted(const int res[], const int n, const char name[])
{
	cout << name;
	if (is_sorted(res, res + n))
	{
		cout << " correct!";
	}
	else
	{
		cout << " wrong!";
	}
	cout << endl;
}

int main(int argc, char** argv)
{
	//init
	srand(time(0));
	int n = atoi(argv[1]);
	int numThreads = atoi(argv[2]);
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % MAX;
	}

	//qsort
#ifdef QSORT
	int* qsortRes = new int[n];
	memcpy(qsortRes, a, n * sizeof(int));
	double qSortStart = omp_get_wtime();
	qsort(qsortRes, n, sizeof(int), cmpInt);
	double qSortTime = omp_get_wtime() - qSortStart;
	cout << "qsort time: " << qSortTime << endl;
	outputSorted(qsortRes, n, "qsort");
	delete[] qsortRes;
#endif // QSORT

	//serial count sort
#ifdef SER_COUNT_SORT
	int* serCountSortRes = new int[n];
	double serCountSortStart = omp_get_wtime();
	serCountSort(a, n, serCountSortRes);
	double serCountSortTime = omp_get_wtime() - serCountSortStart;
	cout << "serial count sort time: " << serCountSortTime << endl;
	outputSorted(serCountSortRes, n, "serial count sort");
	delete[] serCountSortRes;
#endif // SER_COUNT_SORT


	//parallel count sort
#ifdef PAR_COUNT_SORT
	int* parCountSortRes = new int[n];
	double parCountSortStart = omp_get_wtime();
	parCountSort(a, n, parCountSortRes, numThreads);
	double parCountSortTime = omp_get_wtime() - parCountSortStart;
	cout << "parallel count sort time: " << parCountSortTime << endl;
	outputSorted(parCountSortRes, n, "paralllel count sort");
	delete[] parCountSortRes;
#endif // PAR_COUNT_SORT

	//serial fast count sort 
#ifdef SER_FAST_COUNT_SORT
	int* serFastSortRes = new int[n];
	double serFastSortStart = omp_get_wtime();
	serFastCountSort(a, n, serFastSortRes);
	double serFastSortTime = omp_get_wtime() - serFastSortStart;
	cout << "serial fast count sort time: " << serFastSortTime << endl;
	outputSorted(serFastSortRes, n, "serial fast count sort");
	delete[] serFastSortRes;
#endif // SER_FAST_COUNT_SORT

	//paralledl fast count sort
#ifdef PAR_FAST_COUNT_SORT
	int* parFastSortRes = new int[n];
	double parFastSortStart = omp_get_wtime();
	parFastSort(a, n, parFastSortRes, numThreads);
	double parFastSortTime = omp_get_wtime() - parFastSortStart;
	cout << "parallel fast count sort time: " << parFastSortTime << endl;
	outputSorted(parFastSortRes, n, "paralla fast count sort");
	delete[] parFastSortRes;
#endif // PAR_FAST_COUNT_SORT

	delete[] a;
	return 0;
}