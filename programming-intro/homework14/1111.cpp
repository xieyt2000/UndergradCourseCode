#include<iostream>
#include<cstring>
using namespace std;
struct object {
	double price;
	double save;
	double pay;
	int index;
};
object wishlist[2000] = { 0,0,0,0 };
int main() {
	double S;
	int N;
	cin >> S >> N;
	int discount;
	for (int i = 1;i <= N;i++) {
		cin >> wishlist[i].price >> discount;
		wishlist[i].index = i;
		if (discount) {
			wishlist[i].save = wishlist[i].price / 2;
			wishlist[i].pay = wishlist[i].save;
		}
		else wishlist[i].pay = wishlist[i].price;
	}
	for (int i = N;i > 1;i--) {
		for (int j = 1;j < i;j++) {
			if (wishlist[j].save < wishlist[j + 1].save) {
				object t = wishlist[j];
				wishlist[j] = wishlist[j + 1];
				wishlist[j + 1] = t;
			}
			if (wishlist[j].save == wishlist[j + 1].save) {
				if (wishlist[j].price > wishlist[j + 1].price) {
					object t = wishlist[j];
					wishlist[j] = wishlist[j + 1];
					wishlist[j + 1] = t;
				}
			}
		}
	}
	int count = 0;
	double spend = 0;
	int buy[2000] = {  };//start from 1 to count
	for (int i = 1;i <= N;i++) {
		if ((spend + wishlist[i].pay) > S) continue;
		spend = wishlist[i].pay + spend;				
		count++;
		buy[count] = i;
	}
	int out[2000];
	if (count == 0) cout << 0;	
	else {
		for (int i = 1;i <= count;i++) out[i] = wishlist[buy[i]].index;
		for (int i = count;i > 1;i--) {
			for (int j = 1;j < i;j++) {
				if (out[j] > out[j + 1]) {
					int t = out[j];
					out[j] = out[j + 1];
					out[j + 1] = t;
				}
			}
		}
		for (int i = 1;i <= count;i++) cout << out[i] << " ";
	}
	cout << endl;
	//cout<<count;
	return 0;
}
