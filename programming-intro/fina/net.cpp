#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
struct node {
	char name[10];
	int delay;
	node* next;
	node* prev;
};
int main() {
	int Nodecount = 0;//0 is first
	int T;
	cin >> T;
	char order[20] = {};
	//node circle[2000];
	node start;
	for (int i = 1;i <= T;i++) {
		cin >> order;
		if (order[0] == 'A') {
			//cin >> circle[NodeIndi].delay >> circle[NodeIndi].name;
			//NodeIndi++;
			if (Nodecount != 0) {
				node* Tempt = new node;
				cin >> Tempt->delay >> Tempt->name;
				Tempt->next = &start;
				start.prev = Tempt;
				node* tempt = &start;
				for (int i = 0;i < Nodecount - 1;i++) {
					tempt = tempt->next;
				}
				tempt->next = Tempt;
				Tempt->prev = tempt;
			}
			else {
				cin >> start.delay >> start.name;
			}
			Nodecount++;
		}
		if (order[0] == 'E') {
			int m, n;
			cin >> m >> n;
			//int TemIndi = 0;
			node* CurNode = &start;
			for (int delcount = 0;delcount < n;delcount++) {
				for (int i = 1;i < m;i++) CurNode = CurNode->next;
				if (CurNode == &start) start = *CurNode->next;
				CurNode->prev->next = CurNode->next;
				CurNode->next->prev = CurNode->prev;
				//delete CurNode;
				CurNode = CurNode->next;
			}
			Nodecount = Nodecount - n;
		}
		if (order[0] == 'M') {
			node* target = &start;
			int dir, dis;
			cin >> dir >> dis;
			if (dir == 0) {
				for (int i = 1;i <= dis;i++) {
					target = target->next;
				}
			}
			else {
				for (int i = 1;i <= dis;i++) {
					target = target->prev;
				}
			}
			node t = start;
			start = *target;
			*target = t;
		}
		/*if (order[0] == 'S') {
			for (int i = Nodecount;i > 0;i++) {
				for(node* j=&start)
			}
		}*/
		if (order[0] == 'D') {
			node* t = &start;
			char Name[10];
			cin >> Name;
			bool find = 0;
			while (!find) {
				if (t->next = &start) break;
				t = t->next;
				if (strcmp(t->name, Name) == 0) {
					find = 1;
					break;
				}
			}
			if (find) {
				if (t == &start) start = *t->next;
				t->prev->next = t->next;
				t->next->prev = t->prev;
				Nodecount--;
			}
		}
	}
	node* t = &start;
	char Name[10];
	cin >> Name;
	bool find = 0;
	if (Nodecount == 0) {
		cout << -1 << endl;
		return 0;
	}
	long long count = 0;
	while (!find) {
		if (t->next = &start) break;
		t = t->next;
		if (strcmp(t->name, Name) == 0) {
			find = 1;
			break;
		}
	}
	if(!find) cout << -1 << endl;
	else {
		for (node T = start;T.next = t;T = *T.next) {
			cout << T.name << endl;
			count += T.delay;
		}
		cout << count << endl;
	}
	return 0;
}
