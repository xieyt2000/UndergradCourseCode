#include<iostream>
using namespace std;
int Tree[3000], N = 0, del=0;
bool flag = 1;;
struct tree {
	int value;
	tree* left;
	tree* right;
};
void GenerateStruct(int n, tree* t) {
	if (n > N - 1) {
		return;
	}
	if(flag) t->value = Tree[n];
	//else t->value = -2;
	if (n == del) {
		flag = 0;
		t->value = -1;
	}
	//if (Tree[n] != -1) {
		tree* Left = new tree;
		*Left = {-1,NULL,NULL};
		tree* Right = new tree;
		*Right = {-1,NULL,NULL};
		t->left = Left;
		t->right = Right;
		GenerateStruct(2 * n + 1, Left);
		GenerateStruct(2 * n + 2, Right);
	//}
	if (n == del) flag = 1;
}
void GenerateArray(tree* t, int n) {
	Tree[n] = t->value;
	//if (t->value == -2) return;
	if (t->left != NULL) GenerateArray(t->left, 2 * n + 1);
	if (t->right != NULL) GenerateArray(t->right, 2 * n + 2);
}
int main() {
	cin >> N;
	for (int i = 0;i < 3000;i++) {
		Tree[i] = -1;
	}	
	for (int i = 0;i < N;i++) {
		cin >> Tree[i];
	}
	tree* root = new tree;
	//GenerateStruct(0, root);
	//cout << root->value << root->left->right->value << endl;
	//GenerateArray(root, 0);
	//cout << root->value << root->left->right->value<<endl;
	/*for (int i = 0;i < N;i++) {
		if (Tree[i] != -2) {
			if (Tree[i] != -1) cout << Tree[i] << " ";
			else {
				bool flag2 = 0;
				for (int j = i;j < N;j++) {
					if(Tree[j]!=-1) {
						flag2 = 1;
						break;
					}
				}
				if (flag2) {
					cout << -1<<" ";
				}
			}
		}
	}*/
	int sum = 0, i = 0, DeptNum = 1;
	for (;1;i++) {
		if (sum >= N) break;
		sum = sum + DeptNum;
		DeptNum = 2 * DeptNum;
	}
	cout << i << endl;
	return 0;
}
