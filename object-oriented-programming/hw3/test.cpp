#include<iostream>
using namespace std;
#include<string>
class Shape {
	double *size;
	string id;
public:
	static int count;
	Shape(double *size) : size(size) {
		id = type() + " " + to_string(count);
		count++;
	}
	virtual double get_area() = 0;
	virtual string type() = 0;
	friend ostream &operator <<(ostream &out, Shape *w) {
		return out << w->id << ": " << w->get_area();
	}
};

class Rectangle : public Shape {
public:
	Rectangle(double *size)
		: Shape(size) {}
	virtual double get_area() { return size[0] * size[1]; }
	virtual string type() {
		return "Rectangle";
	}
	int angles() {
		return 4;
	}
};
int main(){
	return 0;
}
