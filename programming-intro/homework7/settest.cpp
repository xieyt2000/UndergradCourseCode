#include<iostream>
using namespace std;

bool visA[100000000] = { 0 }, visB[100000000] = { 0 };
int maxAB;

void intersection() {
	for (int i = 0; i <= maxAB; i++)
		if (visA[i] && visB[i])
			cout << i << ' ';
	cout << endl;
	return;
}

void sum() {
	for (int i = 0; i <= maxAB; i++)
		if (visA[i] || visB[i])
			cout << i << ' ';
	cout << endl;
	return;
}

void difference() {
	for (int i = 0; i <= maxAB; i++)
		if (visA[i] && !visB[i])
			cout << i << ' ';
	cout << endl;
	return;
}

int main() {
	int temp;

	int lenA; 
	cin >> lenA;
	for (int i = 0; i < lenA; i++) {
		cin >> temp;
		visA[temp] = 1;
	}
	maxAB = temp;

	int lenB;
	cin >> lenB;
	for (int i = 0; i < lenB; i++) {
		cin >> temp;
		visB[temp] = 1;
	}

	maxAB = (maxAB > temp ? maxAB : temp);
	
	intersection();
	sum();
	difference();

	return 0;
}
