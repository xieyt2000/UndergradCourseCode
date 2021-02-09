#include "kth.h"
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<stdlib.h>


const int MAX_N = 500100;
const int MAX_K = 2000100;

int aSortedRank[MAX_N];
int bSortedRank[MAX_N];
int cSortedRank[MAX_N];

int nGlobal, kGlobal;

enum whichArray
{
	a, b, c
};

inline bool acompare(int t_cmp1, int t_cmp2)
{
	return compare(t_cmp1, 1, 1, t_cmp2, 1, 1);
}

inline bool bcompare(int t_cmp1, int t_cmp2)
{
	return compare(1, t_cmp1, 1, 1, t_cmp2, 1);
}

inline bool ccompare(int t_cmp1, int t_cmp2)
{
	return compare(1, 1, t_cmp1, 1, 1, t_cmp2);
}

template <typename T> inline void swap(T& t_a, T& t_b)
{
	T t = t_a;
	t_a = t_b;
	t_b = t;
}


//heap and heap sort from dsacpp
//rank range [0, n)
#define lchild(x) ((x << 1) + 1)
#define rchild(x) ((1 + x) << 1)
#define parent(x) ((x - 1) >> 1)

inline void percolateDown(bool (*t_cmp)(int, int), int t_down, int* t_arr, int t_n) //for heap sort
{
	int parent = t_down;
	while (true)
	{
		int lc = lchild(parent);
		if (lc >= t_n) break;
		int rc = rchild(parent);
		int biggerc;
		if (rc < t_n && t_cmp(t_arr[lc], t_arr[rc]))
			biggerc = rc;
		else
			biggerc = lc;
		if (t_cmp(t_arr[parent], t_arr[biggerc]))
		{
			swap(t_arr[parent], t_arr[biggerc]);
			parent = biggerc;
			continue;
		}
		break;
	}
}

void heapify(bool (*t_cmp)(int, int), int* t_arr)
{
	for (int i = nGlobal / 2 - 1; 0 <= i; i--)
	{
		percolateDown(t_cmp, i, t_arr, nGlobal);
	}

}

void heapSort(whichArray t_which)
{
	int* arr = nullptr; bool (*cmpFun)(int, int) = nullptr;
	switch (t_which)
	{
	case a:
		arr = aSortedRank;
		cmpFun = acompare;
		break;
	case b:
		arr = bSortedRank;
		cmpFun = bcompare;
		break;
	case c:
		arr = cSortedRank;
		cmpFun = ccompare;
		break;
	default:
		break;
	}
	heapify(cmpFun, arr);
	for (int i = nGlobal - 1; i > 0; i--)
	{
		swap(arr[0], arr[i]);
		percolateDown(cmpFun, 0, arr, i);
	}
}

struct Point	//the correspoding rank in "xSortedRank" (x is a, b, c)
{
	int aRank = 0;
	int bRank = 0;
	int cRank = 0;
	Point() {}
	Point(int t_x, int t_y, int t_z) : aRank(t_x), bRank(t_y), cRank(t_z) {}
};

bool pointcmp(const Point& t_a, const Point& t_b)
{
	return compare(aSortedRank[t_a.aRank], bSortedRank[t_a.bRank], cSortedRank[t_a.cRank], 
		aSortedRank[t_b.aRank], bSortedRank[t_b.bRank], cSortedRank[t_b.cRank]);
}


class Heap	//the root is the smallest
{
private:
	Point data[3 * MAX_K];
	int size = 0;

	inline void percolateUp(int t_up)
	{
		for (int i = t_up; i > 0;)
		{
			int j = parent(i);
			if(!pointcmp(data[i],data[j]))	//parent is smaller
				break;
			swap(data[i], data[j]);
			i = j;
		}
	}

	inline void percolateDown(int t_down) //for heap
	{
		int parent = t_down;
		while (true)
		{
			int lc = lchild(parent);
			if (lc >= size) break;
			int rc = rchild(parent);
			int smallerc;
			if (rc < size && !pointcmp(data[lc], data[rc]))
				smallerc = rc;
			else
				smallerc = lc;
			if (!pointcmp(data[parent], data[smallerc]))
			{
				swap(data[parent], data[smallerc]);
				parent = smallerc;
				continue;
			}
			break;
		}
	}

	inline void insert(const Point& t_new)
	{
		data[size] = t_new;
		size++;
		percolateUp(size - 1);
	}

	inline Point delMax()
	{
		Point max = data[0];
		size--;
		data[0] = data[size];
		percolateDown(0);
		return max;
	}

public:
	Point exec()
	{
		Point ret(0, 0, 0);
		insert(ret);
		for (int i = 0; i < kGlobal; i++)
		{
			ret = delMax();
			if (ret.cRank < nGlobal - 1)	//every point goes up along z
			{
				insert(Point(ret.aRank, ret.bRank, ret.cRank + 1));
			}
			if (ret.cRank == 0)
			{
				if (ret.bRank < nGlobal - 1)	//only points on xy plane go forward along y
				{
					insert(Point(ret.aRank, ret.bRank + 1, ret.cRank));
				}
				if (ret.bRank == 0 && ret.aRank < nGlobal - 1)	//only points on x aixs go forward along x
				{
					insert(Point(ret.aRank + 1, ret.bRank, ret.cRank));
				}
			}
		}
		return ret;
	}
};
Heap heap;


void initialize()
{
	for (int i = 0; i < nGlobal; i++)
	{
		aSortedRank[i] = i + 1;
		bSortedRank[i] = i + 1;
		cSortedRank[i] = i + 1;
	}
}

void get_kth(int n, int k, int* x, int* y, int* z) 
{
	nGlobal = n;
	kGlobal = k;
	initialize();
	heapSort(a); heapSort(b); heapSort(c);
	Point res = heap.exec();
	*x = aSortedRank[res.aRank]; *y = bSortedRank[res.bRank]; *z = cSortedRank[res.cRank];
}
