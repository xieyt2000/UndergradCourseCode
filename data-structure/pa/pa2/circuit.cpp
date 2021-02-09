#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<stdlib.h>

//#define root trieNodes[0];

const int MAX_NUMS = 5e5 + 100;
const int MAX_NODES = 2e7;

struct ListNode
{
	int data = -1;
	int succ = -1;
};

struct TrieNode	//node means inner node
{
	int leftChild = -1;	//means 0 in this digit
	int rightChild = -1;	//means 1 in this digit
	bool valid = false;	//insert then valid = true. delete then valid = false
};

struct TrieLeaf	//correspond to a number
{
	int head = -1;	//LeafIndexList[head] is the first list node. because of input order, list follows ascending order
	int tail = -1;	//LeafIndexList[head] is the last list node
	bool valid = false;	//insert then valid = true. delete then valid = false
};

TrieNode trieNodes[MAX_NODES];
TrieLeaf trieLeaves[MAX_NUMS];
ListNode leafIndexList[MAX_NUMS];	//list using cursor
int usedNodes = 1;	//trieNodes[usedNode] is unused
int usedLeaves = 0;	//trieLeaf[usedLeaves] in unused
int usedListNodes = 0;	//LeafIndexList[usedListNodes] in unused
int n, k;
unsigned long long allNum[MAX_NUMS];

bool validLeftChild(const TrieNode& t_test)
{
	int leftChild = t_test.leftChild;
	if (leftChild == -1) return false;
	return trieNodes[leftChild].valid;
}
bool validRightChild(const TrieNode& t_test)
{
	int rightChild = t_test.rightChild;
	if (rightChild == -1) return false;
	return trieNodes[rightChild].valid;
}
bool validLeftLeaf(const TrieNode& t_test)
{
	int leftChild = t_test.leftChild;
	if (leftChild == -1) return false;
	return trieLeaves[leftChild].valid;
}
bool validRightLeaf(const TrieNode& t_test)
{
	int rightChild = t_test.rightChild;
	if (rightChild == -1) return false;
	return trieLeaves[rightChild].valid;
}
bool noValidChid(const TrieNode& t_test)
{
	return !(validLeftChild(t_test) || validRightChild(t_test));
}
bool noValidChildLeaf(const TrieNode& t_test)
{
	return !(validLeftLeaf(t_test) || validRightLeaf(t_test));
}

int newNode()
{
	usedNodes++;
	return usedNodes - 1;
}

int newLeaf()
{
	usedLeaves++;
	return usedLeaves - 1;
}

void leafInsertIndex(TrieLeaf& t_leaf, int t_index)
{
	leafIndexList[usedListNodes].data = t_index;
	if (t_leaf.head == -1)
	{
		t_leaf.head = usedListNodes;
	}
	else
	{
		leafIndexList[t_leaf.tail].succ = usedListNodes;
	}
	t_leaf.tail = usedListNodes;
	usedListNodes++;
}
int leafGetHead(const TrieLeaf& t_leaf)
{
	return leafIndexList[t_leaf.head].data;
}
bool leafDeleteHead(TrieLeaf& t_leaf)	//return if leaf.list empty
{
	int succOfHead = leafIndexList[t_leaf.head].succ;
	t_leaf.head = succOfHead;
	if (succOfHead == -1)
	{
		t_leaf.tail = -1;
		return true;
	}
	return false;
}

void getBoolStrFromNum(unsigned long long t_num, bool* t_boolStr)
{
	for (int i = 0; i < 64; i++)
	{
		t_boolStr[i] = (t_num % 2 == 1);
		t_num >>= 1;
	}
}

void saveBoolStrAsNum(int t_index, bool* t_boolStr)	//higher digit saved as lower digit in long long int
{
	unsigned long long& oprNum = allNum[t_index];
	oprNum = 0;
	for (int i = 0; i < 64; i++)
	{
		if (t_boolStr[i])
		{
			oprNum += (unsigned long long)1 << i;
		}
	}
}

void insertNum(int t_index, bool* t_boolStr)	//higher digit in the top
{
	saveBoolStrAsNum(t_index, t_boolStr);
	int iterNodeIndex = 0;
	for (int i = 0; i < 63; i++)	//inner node
	{
		bool rightTurn = t_boolStr[i];
		TrieNode& iterNode = trieNodes[iterNodeIndex];
		int& childNodeIndex = (rightTurn ? iterNode.rightChild : iterNode.leftChild);
		if (childNodeIndex == -1)	//create a new node
		{
			childNodeIndex = newNode();
		}
		trieNodes[childNodeIndex].valid = true;	//the child might be there but deleted before. mark it as valid.
		iterNodeIndex = childNodeIndex;
	}
	//leaf
	bool rightTurn = t_boolStr[63];
	TrieNode& iterNode = trieNodes[iterNodeIndex];
	//iterNode.childIsLeaf = true;
	int& childNodeIndex = (rightTurn ? iterNode.rightChild : iterNode.leftChild);
	if (childNodeIndex == -1)	//create a new leaf
	{
		childNodeIndex = newLeaf();
	}
	trieLeaves[childNodeIndex].valid = true;	//the child might be there but deleted before. mark it as valid.
	leafInsertIndex(trieLeaves[childNodeIndex], t_index);
}

void searchAndOutput(int t_index)
{
	unsigned long long curNums = allNum[t_index];
	bool curBoolStr[70];
	getBoolStrFromNum(curNums, curBoolStr);
	int iterNodeIndex = 0;
	for (int i = 0; i < 63; i++)	//travase the inner nodes
	{
		const TrieNode& iterNode = trieNodes[iterNodeIndex];
		bool leftTurn = curBoolStr[i];	//by greedy algorithm, the path want to go left or right
		if (leftTurn)
		{
			leftTurn = validLeftChild(iterNode);
		}
		else
		{
			leftTurn = !validRightChild(iterNode);
		}
		iterNodeIndex = (leftTurn ? iterNode.leftChild : iterNode.rightChild);
	}
	//travase the leaf
	const TrieNode& iterNode = trieNodes[iterNodeIndex];
	bool leftTurn = curBoolStr[63];
	if (leftTurn)
	{
		leftTurn = validLeftLeaf(iterNode);
	}
	else
	{
		leftTurn = !validRightLeaf(iterNode);
	}
	iterNodeIndex = (leftTurn ? iterNode.leftChild : iterNode.rightChild);
	printf("%d\n", leafGetHead(trieLeaves[iterNodeIndex]) - 1);	//num index start form 1. output -1
}

void getPath(int t_index, int* t_path)
{
	bool boolStr[70];
	getBoolStrFromNum(allNum[t_index], boolStr);
	int iterIndex = 0;
	for (int i = 0; i < 65; i++)
	{
		t_path[i] = iterIndex;
		iterIndex = (boolStr[i] ? trieNodes[iterIndex].rightChild : trieNodes[iterIndex].leftChild);
	}
}

void deleteNum(int t_index)
{
	int pathIndex[70];	//0 is root 63 is leaf
	getPath(t_index, pathIndex);
	int pathIterIndex = 64;
	TrieLeaf& leaf = trieLeaves[pathIndex[pathIterIndex]];
	if (!leafDeleteHead(leaf))	//after delete, not empty
	{
		return;
	}
	leaf.valid = false;
	pathIterIndex--;
	int iterIndex = pathIndex[pathIterIndex];
	if (!noValidChildLeaf(trieNodes[iterIndex]))
	{
		return;
	}
	trieNodes[iterIndex].valid = false;
	pathIterIndex--;
	iterIndex = pathIndex[pathIterIndex];
	while (true)
	{
		TrieNode& iterNode = trieNodes[iterIndex];
		if (!noValidChid(iterNode))
		{
			break;
		}
		iterNode.valid = false;
		if (iterIndex == 0)	//root has no valid child
		{
			break;
		}
		pathIterIndex--;
		iterIndex = pathIndex[pathIterIndex];
	}
}

int main()
{
	trieNodes[0].valid = true;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= (n + k + 1); i++)
	{
		if (i <= n)
		{
			char numStr[70];
			scanf("%s", numStr);
			bool boolStr[70];
			for (int j = 0; j < 64; j++)
			{
				boolStr[j] = (numStr[j] == '1');
			}
			insertNum(i, boolStr);
			getBoolStrFromNum(allNum[i], boolStr);
			int i = 1;
		}
		//already input min(i,n) nums
		if (i > k + 1)	//k+2 numbers input. search begins
		{
			searchAndOutput(i - (k + 1));
			if (i > (2 * k + 2))	//2k+3 numbers input. delete begains
			{
				deleteNum(i - (2 * k + 2));
			}
		}
	}
	return 0;
}