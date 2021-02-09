#include<iostream>
#include<cstring>
using namespace std;

struct student {
	int   id;
	char  name[13];
	char  dept[32];
	char  group[10];
	char  type[10];
	char  email[58];
	long long cell;	//phone number
};
struct LinkNode {	//separate link and data
	LinkNode * next;
	LinkNode * prev;
	student  * stu;
};
LinkNode * initLinkedList() {	//get a link linst and return the headnode
	LinkNode * phead = new LinkNode;
	LinkNode * ptail = new LinkNode;
	//head node
	phead->next = ptail;								
	phead->prev = NULL;
	phead->stu = NULL;
	
	//tail node
	ptail->next = NULL;									
	ptail->prev = phead;
	ptail->stu = NULL;

	return phead;
}
int readStructsIntoList(LinkNode* & node) {		//sequencial input by original order
	char buffer[256];
	int k = 0;
	LinkNode* Node = node;
	for (; gets(buffer); k++) {
		LinkNode* tanode = new LinkNode;
		student* ta = new student;

		sscanf(buffer, "%d%12s%31s%9s%9s%57s%I64d",
			&ta->id,
			ta->name,
			ta->dept,
			ta->group,
			ta->type,
			ta->email,
			&ta->cell);

		Node->next->prev = tanode;
		tanode->next = Node->next;
		tanode->prev = Node;
		Node->next = tanode;
		tanode->stu = ta;
		Node = tanode;
	}
	return k;
}
void insertionSort(LinkNode* l){//orderd and by group
	LinkNode* t = l;
	for (LinkNode* x = t->next;x->stu!=NULL;x=x->next) {
		for (LinkNode* y = x->prev; y->stu != NULL; y = y->prev) {
			if (strcmp(x->stu->group, y->stu->group) < 0) {//x.group<y.group 
				//switch x y
				y->prev->next = x; x->next->prev = y; y->next = x->next; x->prev = y->prev; y->prev = x; x->next = y;

				y = x;
				continue;
			}
			else {//x.group>=y.group
				break;
			}
		}
	}
}
int main(int argc, char* argv[]) {
	LinkNode * phead = initLinkedList();											// initialize
	LinkNode * ptail = phead->next;
	int n = readStructsIntoList(phead);												// input
	//cout<<test.1;
	insertionSort(phead->next);														// insertionsort
	//cout<<test.2;
	for (LinkNode * node = phead->next; node->stu!=NULL; node = node->next) {		//output
		cout << node->stu->id << "\t" 
			 << node->stu->name << "\t" 
			 << node->stu->dept << "\t" 
			 << node->stu->group << "\t" 
			 << node->stu->type << "\t" 
			 << node->stu->email << "\t" 
			 << node->stu->cell << "\t" 
			 << endl;
	}
	//cout<<phead->next->stu->name<<"\t"<<ptail->prev->stu->name;
	
	while (phead!=NULL) {																	//delete
		LinkNode* node = phead; phead = phead->next; delete node;
	}
	/*for (LinkNode * node = phead->next; node->stu!=NULL; node = node->next) {		
		cout << node->stu->id << "\t" 
			 << node->stu->name << "\t" 
			 << node->stu->dept << "\t" 
			 << node->stu->group << "\t" 
			 << node->stu->type << "\t" 
			 << node->stu->email << "\t" 
			 << node->stu->cell << "\t" 
			 << endl;
	}
	cout<<ptail->prev<<phead->next;*/
	return 0;
}
