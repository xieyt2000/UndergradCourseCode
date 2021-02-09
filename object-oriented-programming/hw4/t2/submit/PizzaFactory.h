#pragma once
#include "pizza.h"
#include <string>
#include <vector>
#include <iostream>
class PizzaFactory   //同时存储并构造plate和pizza
{
private:
	vector<Pizza*> ordered_pizzas;
	vector<Plate*> plates;
public:
	Plate *find_empty_plate() {
		Plate *empty_plate = nullptr;
		for (Plate *plate : plates)
			if (!plate->contains_pizza()) {
				empty_plate = plate;
				break;
			}
		return empty_plate;
	}
	void makePlates(vector<string> names)
	{
		for (auto i : names)
		{
			plates.push_back(new Plate(i));
		}
	}
	Pizza* make1Pizza(const string& type)
	{
		Plate *plate = find_empty_plate();
		if (plate == nullptr) return nullptr;
		Pizza* pizza = nullptr;
		if (type == "Seafood Pizza")
		{
			pizza= new Pizza("Seafood Pizza", 30, 90);
			pizza->cut();
		}
		else if (type == "Beef Pizza")
		{
			pizza = new Pizza("Beef Pizza", 20, 40);
		}
		else if (type == "Fruit Pizza")
		{
			pizza = new Pizza("Fruit Pizza", 0, 0);
		}
		else if (type == "Sausage Pizza")
		{
			pizza = new Pizza("Sausage Pizza", 40, 20);
			pizza->cut();
		}
		else if (type == "Cheese Pizza")
		{
			pizza = new Pizza("Cheese Pizza", 0, 20);
			pizza->cut();
		}
		else if (type == "Tomato Pizza")
		{
			pizza = new Pizza("Tomato Pizza", 20, 0);
		}
		pizza->cook();
		pizza->put_on(plate);
		return pizza;
	}
	void make_orderd_pizzas(vector<string> types)
	{
		for (auto i : types)
		{
			Pizza* tmp = make1Pizza(i);
			ordered_pizzas.push_back(tmp);
		}
	}
	void tell_orderd_pizzas()
	{
		int count = 0;
		for (Pizza *pizza : ordered_pizzas)
			if (pizza != nullptr) ++count;
		cout << "Ordered " << count << " plates of pizza." << endl;
	}
	void eatPizzas()
	{
		for (Pizza *pizza : ordered_pizzas)
			if (pizza != nullptr) {
				pizza->eat();
			}
	}
	void eatPizzasAndDelete()
	{
		for (Pizza *pizza : ordered_pizzas)
			if (pizza != nullptr) 
			{
				pizza->eat();
				delete pizza;
				pizza = nullptr;
			}
	}
	void clear_orderd_pizzas()
	{
		ordered_pizzas.clear();
	}
	void deletePizzas()
	{
		for (Pizza *pizza : ordered_pizzas)
		{
			if (pizza != nullptr)
			{
				delete pizza;
				pizza = nullptr;
			}
		}
	}
	//此函数在本程序中未被调用，但为了工厂的完整性仍应存在
	void deletePlates()
	{
		for (Plate *plate : plates)
		{
			if (plate != nullptr)
			{
				delete plate;
				plate = nullptr;
			}
		}
	}
	//此函数在本程序中未被调用，但为了工厂的完整性仍应存在
	void clear_plates()
	{
		plates.clear();
	}
	~PizzaFactory()
	{
		for (Pizza *pizza : ordered_pizzas)
		{
			if (pizza != nullptr)
				delete pizza;
		}
		for (Plate *plate : plates)
		{
			if (plate != nullptr)
				delete plate;
		}
	}
};