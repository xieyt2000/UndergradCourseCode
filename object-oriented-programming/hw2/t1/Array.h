#pragma once
#include"Node.h"
#include<iostream>
class Array
{
public:
	Node* array;
	int length;
	Array(int n);
	Node& operator[](const int n);
	void update(int q, int r);
	void swap(int q, int r);
	void insert(int q, int r);
	~Array();
};