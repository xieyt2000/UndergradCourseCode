#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <cmath>
#include "PizzaFactory.h"
using namespace std;
// ori code are marked as comment

/*vector<Plate *> plates;
 
Plate *find_empty_plate() {
	Plate *empty_plate = nullptr;
	for (Plate *plate : plates)
		if (!plate->contains_pizza()) {
			empty_plate = plate;
			break;
		}
	return empty_plate;
}


Pizza *make_seafood_pizza() {
	Plate *plate = find_empty_plate();
	if (plate == nullptr) return nullptr;
	Pizza *pizza = new Pizza("Seafood Pizza", 30, 90);
	pizza->cook();
	pizza->cut();
	pizza->put_on(plate);
	return pizza;
}

Pizza *make_beef_pizza() {
	Plate *plate = find_empty_plate();
	if (plate == nullptr) return nullptr;
	Pizza *pizza = new Pizza("Beef Pizza", 20, 40);
	pizza->cook();
	pizza->put_on(plate);
	return pizza;
}

Pizza *make_fruit_pizza() {
	Plate *plate = find_empty_plate();
	if (plate == nullptr) return nullptr;
	Pizza *pizza = new Pizza("Fruit Pizza", 0, 0);
	pizza->cook();
	pizza->put_on(plate);
	return pizza;
}

Pizza *make_sausage_pizza() {
	Plate *plate = find_empty_plate();
	if (plate == nullptr) return nullptr;
	Pizza *pizza = new Pizza("Sausage Pizza", 40, 20);
	pizza->cook();
	pizza->cut();
	pizza->put_on(plate);
	return pizza;
}

Pizza *make_tomato_pizza() {
	Plate *plate = find_empty_plate();
	if (plate == nullptr) return nullptr;
	Pizza *pizza = new Pizza("Tomato Pizza", 20, 0);
	pizza->cook();
	pizza->put_on(plate);
	return pizza;
}

Pizza *make_cheese_pizza() {
	Plate *plate = find_empty_plate();
	if (plate == nullptr) return nullptr;
	Pizza *pizza = new Pizza("Cheese Pizza", 0, 20);
	pizza->cook();
	pizza->cut();
	pizza->put_on(plate);
	return pizza;
}
*/

int main() {
	
	PizzaFactory pizzaFacory;
	vector<string> platesNames; 
	vector<string> pizzaTypes;
	platesNames = { "red","white","golden","titanium","yellow" };
	pizzaFacory.makePlates(platesNames);
	pizzaTypes = { "Seafood Pizza", "Beef Pizza", "Fruit Pizza", "Sausage Pizza", "Tomato Pizza", "Cheese Pizza" };
	pizzaFacory.make_orderd_pizzas(pizzaTypes);
	pizzaFacory.tell_orderd_pizzas();
	pizzaFacory.eatPizzasAndDelete();
	pizzaFacory.clear_orderd_pizzas();
	pizzaTypes.clear();
	pizzaTypes = { "Cheese Pizza", "Tomato Pizza", "Sausage Pizza", "Fruit Pizza", "Beef Pizza", "Seafood Pizza" };
	pizzaFacory.make_orderd_pizzas(pizzaTypes);
	pizzaFacory.tell_orderd_pizzas();
	pizzaFacory.eatPizzas();

	/*plates.push_back(new Plate("red"));
	plates.push_back(new Plate("white"));
	plates.push_back(new Plate("golden"));
	plates.push_back(new Plate("titanium"));
	plates.push_back(new Plate("yellow"));

	vector<Pizza *> ordered_pizzas;
	ordered_pizzas.push_back(make_seafood_pizza());
	ordered_pizzas.push_back(make_beef_pizza());
	ordered_pizzas.push_back(make_fruit_pizza());
	ordered_pizzas.push_back(make_sausage_pizza());
	ordered_pizzas.push_back(make_tomato_pizza());
	ordered_pizzas.push_back(make_cheese_pizza());
	int count = 0;
	for (Pizza *pizza : ordered_pizzas)
		if (pizza != nullptr) ++count;
	cout << "Ordered " << count << " plates of pizza." << endl;
	for (Pizza *pizza : ordered_pizzas)
		if (pizza != nullptr) {
			pizza->eat();
			delete pizza;
		}

	ordered_pizzas.clear();
	ordered_pizzas.push_back(make_cheese_pizza());
	ordered_pizzas.push_back(make_tomato_pizza());
	ordered_pizzas.push_back(make_sausage_pizza());
	ordered_pizzas.push_back(make_fruit_pizza());
	ordered_pizzas.push_back(make_beef_pizza());
	ordered_pizzas.push_back(make_seafood_pizza());
	count = 0;
	for (Pizza *pizza : ordered_pizzas)
		if (pizza != nullptr) ++count;
	cout << "Ordered " << count << " plates of pizza." << endl;
	for (Pizza *pizza : ordered_pizzas)
		if (pizza != nullptr)
			pizza->eat();

	for (Pizza *pizza : ordered_pizzas)
		delete pizza;
	for (Plate *plate : plates)
		delete plate;*/

	return 0;

}