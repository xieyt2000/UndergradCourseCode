const double PI = 3.14;

class Shape {
	double *size;
	string id;
public:
	static int count;
	Shape(double *size) : size(size) {
		id = " " + to_string(count);	
		count++;								
	}
	virtual double get_area() = 0;
	virtual string type() = 0;
	friend ostream &operator <<(ostream &out, Shape *w) {
		return out << w->id << ": " << w->get_area();
	}
	//3
	double getsize(int index) {
		return size[index];
	}
	//end 3 start 4
	void addtype(string type) {
		id = type + id;
	}
	void replacetype(string type, int ori) {
		id.replace(0, ori, type);
	}
	//end 4 start 5
	virtual ~Shape() {
		if (id.find("Rectangle") == 0) delete[] size;
		else delete size;
	}
};	
class Rectangle : public Shape {				//2
public:
	/*IntegerWrapper(double *size)
		: Shape(size) {}*/
	Rectangle(double* size) 
		:Shape(size) {							//1
		addtype(type());							//4
	}		
	virtual double get_area() { 
		//return size[0] * size[1]; 
		return getsize(0) * getsize(1);			//3
	}
	virtual string type() {
		return "Rectangle";
	}
	int angles() {
		return 4;
	}
};

class Square : public Rectangle {				//2
public:
	Square(double *size)
		: Rectangle(size) {
		int a = sizeof("Rectangle");
		replacetype(type(), sizeof("Rectangle")-1);	//4
	}
	virtual double get_area() { 
		//return size[0] * size[0];				//3
		return getsize(0) * getsize(0);
	}
	virtual string type() {
		return "Square";
	}
};

class Circle : public Shape {					//2
public:
	Circle(double *size)
		: Shape(size) {
		addtype(type());							//4
	}
	virtual double get_area() { 
		//return PI * size[0] * size[0];		//3
		return PI * getsize(0) * getsize(0);
	}
	virtual string type() {
		return "Circle";
	}
};
