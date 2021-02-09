using namespace std;

class A
{
	A& a;
	int b;
	public:
		void operator++(int a){
			b=b+a;
		}
	A():a(*this) { }
};	
int main()
{
	A a;
	++(2)a;
	return 0;
}
