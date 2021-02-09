#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Plate {
	string _id;
	class Pizza *pizza;

public:
	Plate(const string &id) : _id(id), pizza(nullptr) {}
	~Plate() {
		cout << "Sold " << _id << " plate." << endl;
	}
	bool contains_pizza() const {
		return this->pizza != nullptr;
	}
	void hold_pizza(Pizza *pizza) {
		this->pizza = pizza;
	}
	const string &id() const {
		return _id;
	}
};