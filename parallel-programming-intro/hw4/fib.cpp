#include"pthreadClass.h"
#include<cstdlib>
#include<iostream>
#include<chrono>
#include<cmath>

using namespace std;
using namespace std::chrono;

int maxThread, threadCnt;
long n;
Mutex threadCntMutex;

void* serialFib(void* inputN)
{
	long n = long(inputN);
	if (n <= 2)
	{
		return (void*)1;
	}
	return (void*)((long)serialFib((void*)(n - 1)) + (long)serialFib((void*)(n - 2)));
}

void* parallelFib(void* inputN)
{
	long n = (long)inputN;
	if (n <= 2)
	{
		return (void*)1;
	}
	bool newThread = false;
	threadCntMutex.lock();
	if (threadCnt < maxThread)
	{
		threadCnt++;
		newThread = true;
	}
	threadCntMutex.unlock();
	if (newThread)
	{
		pthread_t thread;
		pthread_create(&thread, nullptr, parallelFib, (void*)(n - 2));
		long nm1Fib = (long)serialFib((void*)(n - 1));
		void* outputNm2Fib;
		pthread_join(thread, &outputNm2Fib);
		threadCntMutex.lock();
		threadCnt--;
		threadCntMutex.unlock();
		long nm2Fib = (long)outputNm2Fib;
		return (void*)(nm1Fib + nm2Fib);
	}
	else
	{
		return (void*)((long)parallelFib((void*)(n - 1)) + (long)parallelFib((void*)(n - 2)));
	}
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		return 1;
	}
	n = atoi(argv[2]);
	maxThread = atoi(argv[1]);
	threadCnt = 0;
	long parRes, serRes;
	auto begin = steady_clock::now();
	parRes = (long)parallelFib((void*)n);
	auto end = steady_clock::now();
	cout << "Parallel result = " << parRes << endl;
	cout << "Parallel time (μs) = " << duration_cast<microseconds>(end - begin).count() << endl;
	begin = steady_clock::now();
	serRes = (long)serialFib((void*)n);
	end = steady_clock::now();
	cout << "Serial result = " << serRes << endl;
	cout << "Serial time (μs) = " << duration_cast<microseconds>(end - begin).count() << endl;
	cout << "Result difference = " << abs(serRes - parRes) << endl;
	return 0;
}