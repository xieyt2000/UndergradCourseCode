#include <algorithm>
#include <iostream>
#include <vector>

#include <cassert>
#include <cmath>

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

class Pizza {
	Plate *plate;
	string name;
	int ketchup, cheese;
	bool cooked;
	bool cutted;

public:
	Pizza(const string &name, int ketchup, int cheese)
			: name(name), ketchup(ketchup), cheese(cheese), cooked(false), cutted(false), plate(nullptr) {}
	void cook() {
		this->cooked = true;
	}
	void cut() {
		this->cutted = true;
	}
	void put_on(Plate *plate) {
		this->plate = plate;
		plate->hold_pizza(this);
	}
	~Pizza() {
		this->plate->hold_pizza(nullptr);
		cout << "Washed " << this->plate->id() << " plate." << endl;
	}
	void eat() {
		cout << "Eating " << this->name << " (";
		float total = (this->ketchup + this->cheese) / 100.0f;
		if (total == 0.0f) total = 1.0f;
		cout << static_cast<int>(round(this->ketchup / total)) << "% ketchup";
		cout << " and ";
		cout << static_cast<int>(round(this->cheese / total)) << "% cheese";
		if (this->cooked || this->cutted) {
			cout << " that is";
            if (this->cooked) cout << " cooked";
            if (this->cooked && this->cutted) cout << " and";
            if (this->cutted) cout << " cutted";
		}
	    cout << ") from " << this->plate->id() << " plate.";
        cout << endl;
	}
};

vector<Plate *> plates;

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


int main() {
	plates.push_back(new Plate("red"));
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
		delete plate;

	return 0;
}