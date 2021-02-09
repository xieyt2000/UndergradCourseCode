#include "sort.h"
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<stdlib.h>

const int MAX_N = 1000100;

int* globalArray;

struct Data	//store the element in the array with index indicating which part they come from
{
	int value;  //index
	int index;  //which part they come from
	Data() {}
	Data(int t_v, int t_i) : value(t_v), index(t_i) {}
};

bool compare2(int t_a, int t_b) //compare if x<y 
{
	int max, min;
	compare(t_a, t_b, t_b, &max, &min);
	return max == t_b;
}

//with middle
void compare3(int t_a, int t_b, int t_c, int* t_max, int* t_mid, int* t_min)
{
	compare(t_a, t_b, t_c, t_max, t_min);
	if (t_a != *t_max && t_a != *t_min) *t_mid = t_a;
	else if (t_b != *t_max && t_b != *t_min) *t_mid = t_b;
	else *t_mid = t_c;
}

void compare3(const Data& t_a, const Data& t_b, const Data& t_c, Data* t_max, Data* t_mid, Data* t_min)
{
	int max, min;
	Data input[5];
	input[0] = t_a; input[1] = t_b; input[2] = t_c;
	compare(t_a.value, t_b.value, t_c.value, &max, &min);
	for (int i = 0; i < 3; i++)
	{
		if (input[i].value == max) *t_max = input[i];
		else if (input[i].value == min) *t_min = input[i];
		else *t_mid = input[i];
	}
}


//4 way merge sort. divide the array into 4 subarrays
//part1: [low, qar1)  part2:[qar1, mid)  part3:[mid, qar3)  part4:[qar3, high)

//copy of each subarray. dont need to copy part4.
int arrP1[MAX_N];
int arrP2[MAX_N];
int arrP3[MAX_N];


int* arrPtrs[10]; //pointer to all 4 parts   [1, 4]
int arrLen[10]; //length of all 4 parts [1,4]
int arrIters[10];   //for iteration arr[iter] is unvisited
int* tarArr; //the target position(in globalArray)
int tarArrIter = 0;	//same as arrIters

inline void mergeInitialize(int t_low)
{
	arrPtrs[1] = globalArray + t_low;
	for (int i = 0; i < arrLen[1]; i++) arrP1[i] = arrPtrs[1][i];
	arrPtrs[2] = arrPtrs[1] + arrLen[1];
	for (int i = 0; i < arrLen[2]; i++) arrP2[i] = arrPtrs[2][i];
	arrPtrs[3] = arrPtrs[2] + arrLen[2];
	for (int i = 0; i < arrLen[3]; i++) arrP3[i] = arrPtrs[3][i];
	arrPtrs[4] = arrPtrs[3] + arrLen[3];
	arrPtrs[1] = arrP1; arrPtrs[2] = arrP2; arrPtrs[3] = arrP3;
	tarArrIter = 0;
	memset(arrIters, 0, sizeof(arrIters));
}

//called when one part is empty. iterate over 4 parts. if only <4 elements left, trivial sort and return true(finished). else move elements to empty array.
inline bool test4way()
{
	int leftNum = 0;
	for (int i = 1; i <= 4; i++)
		leftNum += arrLen[i] - arrIters[i];

	if (leftNum < 4)    //finishd
	{
		int left[5];	//all the elements left
		for (int i = 1, j = 0; i <= 4; i++)
		{
			for (; arrIters[i] < arrLen[i]; arrIters[i]++)
			{
				left[j] = arrPtrs[i][arrIters[i]];
				j++;
			}
		}
		if (leftNum == 3)
		{
			compare3(left[0], left[1], left[2], &tarArr[tarArrIter + 2], &tarArr[tarArrIter + 1], &tarArr[tarArrIter]);
		}
		else if (leftNum == 2)
		{
			compare(left[0], left[1], left[1], &tarArr[tarArrIter + 1], &tarArr[tarArrIter]);
		}
		else if (leftNum == 1)
		{
			tarArr[tarArrIter] = left[0];
		}
		return true;
	}
	else    //unfinishd
	{
		int emptyIndex = 0;
		int maxLen = 0;
		int maxIndex;	//array with the most element left
		for (int i = 1; i <= 4; i++)
		{
			if (arrLen[i] <= arrIters[i]) emptyIndex = i;
			if ((arrLen[i] - arrIters[i] > maxLen))
			{
				maxLen = arrLen[i] - arrIters[i];
				maxIndex = i;
			}
		}
		if (emptyIndex == 0)	//no empty part. might happen in the first test4way(before any merge)
		{
			return false;
		}
		//'move' half of the unvisited element in the max part to the empty part
		arrLen[emptyIndex] = (arrLen[maxIndex] - arrIters[maxIndex]) / 2;
		arrLen[maxIndex] -= arrLen[emptyIndex];
		arrPtrs[emptyIndex] = arrPtrs[maxIndex] + arrLen[maxIndex];	//dont need to copy memory, move pointer is ok and safe
		arrIters[emptyIndex] = 0;
	}
	return false;
}



inline void merge(int t_low, int t_qar1, int t_mid, int t_qar3, int t_high)
{
	tarArr = globalArray + t_low;
	arrLen[1] = t_qar1 - t_low; arrLen[2] = t_mid - t_qar1;
	arrLen[3] = t_qar3 - t_mid; arrLen[4] = t_high - t_qar3;
	mergeInitialize(t_low);
	//4 way merge
	while (true)
	{
		if (test4way()) //finish. the test function also sort the trivial case (when return true)
		{
			break;
		}
		//all 4 parts arenot empty

		//iterData are from top of each part. in every iteration, premise: iterData[1] < iterData[2]. 
		//then we compare iterData[1], [3], [4]. put the min to target and we have mid < max as the premise of the next iteration.
		Data iterData[10];
		for (int i = 1; i <= 4; i++)	//initialize with top value in each part
		{
			iterData[i] = Data(arrPtrs[i][arrIters[i]], i);
		}
		if (compare2(iterData[2].value, iterData[1].value))
		{
			Data tmp = iterData[1];
			iterData[1] = iterData[2]; iterData[2] = tmp;
		}	//now we have the premise

		while (true)
		{
			Data max, mid, min;
			compare3(iterData[1], iterData[3], iterData[4], &max, &mid, &min);
			//add a element to target
			tarArr[tarArrIter] = min.value;
			tarArrIter++;
			//rebuild iterData
			iterData[3] = iterData[2];
			iterData[1] = mid;
			iterData[2] = max;
			arrIters[min.index]++;
			if (arrIters[min.index] >= arrLen[min.index])	//one part is empty. break and go to test
			{
				break;
			}
			iterData[4] = Data(arrPtrs[min.index][arrIters[min.index]], min.index);
		}
	}
}


inline void mergeSort(int t_low, int t_high) //[low, high)
{
	if (t_high - t_low < 2) //only 1 element
	{
		return;
	}
	int mid = (t_low + t_high) / 2;
	int qar1 = (t_low + mid) / 2, qar3 = (t_high + mid) / 2;    //one quarter and 3 quarters
	mergeSort(t_low, qar1); mergeSort(qar1, mid);
	mergeSort(mid, qar3); mergeSort(qar3, t_high);
	merge(t_low, qar1, mid, qar3, t_high);
}


void sort(int n, int limit, int* a)
{
	globalArray = a;
	mergeSort(0, n);
}
