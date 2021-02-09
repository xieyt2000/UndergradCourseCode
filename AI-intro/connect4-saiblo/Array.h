#pragma once
#include "constants.h"

//fixed length vector. simple encapsulation
template<typename T, int N = MAX_M>
class Array
{
private:
	T data[N];
	int size = 0;
public:
	Array() {}
	inline void push(const T& in)
	{
		data[size] = in;
		size++;
	}

	inline T pop()
	{
		size--;
		return data[size];
	}

	inline T& operator[](int i)
	{
		return data[i];
	}

	inline T& last()
	{
		return data[size - 1];
	}

	inline int getSize() const
	{
		return size;
	}

	inline void clear()
	{
		size = 0;
	}

	inline bool empty()
	{
		return size == 0;
	}
	
	inline bool full()
	{
		return size == N;
	}
};