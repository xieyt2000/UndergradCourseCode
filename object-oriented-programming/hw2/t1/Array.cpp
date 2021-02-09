#include"Array.h"
#include"Node.h"
#include<iostream>
Array::Array(int n)
{
	length = n;
	array = new Node[n];
}
Node& Array::operator[](const int n)
{
	return array[n];
}
void Array::update(int q, int r)
{
	array[q] = array[r];
}
void Array::swap(int q, int r)
{
	Node tem(std::move(array[q]));
	array[q] = std::move(array[r]);
	array[r] = std::move(tem);
}
void Array::insert(int q, int r)
{
	for (int i = length - 1; i > q; i--)
	{
		array[i] = std::move(array[i - 1]);
	}
	Node tem(r);
	array[q] = std::move(tem);
}
Array::~Array()
{
	delete[] array;
}