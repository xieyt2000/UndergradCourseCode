#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<stdlib.h>

const int MAX_NODES = 1e6 + 100;

int max(int t_a, int t_b)
{
	return (t_a > t_b ? t_a : t_b);
}


struct Node
{
	int succHeight = 0;//from Du Junyi, highest succ bro include self
	int index = 0;
	int size = 1;
	int height = 0;
	Node* firstChild = nullptr;
	Node* succBrother = nullptr;
	Node* prevBrother = nullptr;
	Node* parent = nullptr;
	Node(int t_index) :index(t_index) {}
	Node* prev()	//prev of self. prevBro or parent
	{
		return prevBrother ? prevBrother : parent;
	}
	int succBroSuccHeight()	//get succbro's succheight. if succbro is nullptr, return -1
	{
		return succBrother ? succBrother->succHeight : -1;
	}
	int childHeight()	//return firstChild's succHeight. if no child, return -1
	{
		return firstChild ? firstChild->succHeight : -1;
	}
};

class Tree
{
private:
	Node* root = nullptr;
	Node* allNodes[MAX_NODES];	//pointer to all nodes by index
	int N = 0;
	int M = 0;
	Node* levelTrav[MAX_NODES];

	void generateHightAndSize()
	{
		//level travel
		int left = 0; int right = 1;	//[left, right)
		levelTrav[0] = root;
		while (right - left > 0)
		{
			for (Node* i = levelTrav[left]->firstChild; i; i = i->succBrother)
			{
				levelTrav[right] = i;
				right++;
			}
			left++;
		}
		//get height and size
		for (int i = N - 1; i >= 0; i--)
		{
			Node* iNode = levelTrav[i];
			if (iNode->parent)
			{
				iNode->parent->size += iNode->size;
			}
			iNode->height = iNode->childHeight() + 1;
			iNode->succHeight = max(iNode->height, iNode->succBroSuccHeight());
		}
	}

	Node* findByRoute()	//input included
	{
		int routeLength;
		scanf("%d", &routeLength);
		Node* result = root;
		bool routeFinish = false;	//for illegal input
		for (int i = 0; i < routeLength; i++)
		{
			int curRank;
			scanf("%d", &curRank);
			if (routeFinish)
			{
				continue;
			}
			Node* tmpNode = result->firstChild;
			if (!tmpNode)
			{
				routeFinish = true;
				continue;
			}
			for (int j = 0; j < curRank; j++)
			{
				if (!tmpNode->succBrother)
				{
					routeFinish = true;
					break;
				}
				tmpNode = tmpNode->succBrother;
			}
			if (!routeFinish)
			{
				result = tmpNode;
			}
		}
		return result;
	}

	void updateHeightAboveAndLeft(Node* t_node)	//also update self's succHeight
	{
		Node* i = t_node;
		//for i itself
		i->height = i->childHeight() + 1;
		i->succHeight = max(i->height, i->succBroSuccHeight());
		i = i->prev();
		if (!i)
		{
			return;
		}
		//start from t_node.prev
		i->height = i->childHeight() + 1;
		while (true)
		{
			while (true)
			{
				int oriSuccHeight = i->succHeight;
				i->succHeight = max(i->height, i->succBroSuccHeight());
				if (i->succHeight == oriSuccHeight)	//i succheight hasn't changed. return
				{
					return;
				}
				if (!i->prevBrother)	//i is the first child, go to parent
				{
					break;
				}
				i = i->prevBrother;
			}
			if (!i->parent)	//i is root return
			{
				return;
			}
			i = i->parent;
			int oriHeight = i->height;
			i->height = i->firstChild->succHeight + 1;	//because i is prev i's parent, so i must has child.
			if (i->height == oriHeight) //parent hasn't change
			{
				return;
			}
		}
	}

	void updateSizeAbove(Node* t_node, int t_increase)
	{
		for (Node* p = t_node->parent; p; p = p->parent)
		{
			p->size += t_increase;
		}
	}

	void inputOriTree()
	{
		for (int i = 1; i <= N; i++)
		{
			allNodes[i] = new Node(i);
		}
		root = allNodes[1];
		for (int i = 1; i <= N; i++)
		{
			Node* curParent = allNodes[i];
			int childCount;
			scanf("%d", &childCount);
			Node* prevBro = nullptr;
			for (int j = 0; j < childCount; j++)
			{
				int curIndex;
				scanf("%d", &curIndex);
				Node* curChild = allNodes[curIndex];
				curChild->parent = curParent;
				if (j == 0)
				{
					curParent->firstChild = curChild;
				}
				else
				{
					prevBro->succBrother = curChild;
				}
				curChild->prevBrother = prevBro;
				prevBro = curChild;
			}
		}
		generateHightAndSize();
	}

	Node* getPrevChildByRank(Node* t_parent, int t_rank)
	{
		if (t_rank == 0)
		{
			return nullptr;
		}
		Node* result = t_parent->firstChild;
		for (int i = 1; i < t_rank; i++)
		{
			result = result->succBrother;
		}
		return result;
	}

	void move()
	{
		Node* src = findByRoute();
		//delete
		src->parent->size -= src->size;
		updateSizeAbove(src->parent, -src->size);
		if (!src->prevBrother)	//firstChild
		{
			src->parent->firstChild = src->succBrother;
		}
		else
		{
			src->prevBrother->succBrother = src->succBrother;
		}
		if (src->succBrother)	//not lastChild
		{
			src->succBrother->prevBrother = src->prevBrother;
		}
		updateHeightAboveAndLeft(src->prev());
		//add
		Node* dstParent = findByRoute();
		int dstRank;
		scanf("%d", &dstRank);
		src->parent = dstParent;
		src->prevBrother = getPrevChildByRank(dstParent, dstRank);
		src->succBrother = nullptr;
		if (!src->prevBrother)	//first child
		{
			if (dstParent->firstChild)	//parent already has child
			{
				dstParent->firstChild->prevBrother = src;
				src->succBrother = dstParent->firstChild;
			}
			dstParent->firstChild = src;
		}
		else	//not first child
		{
			if (src->prevBrother->succBrother)	//not last child
			{
				src->succBrother = src->prevBrother->succBrother;
				src->succBrother->prevBrother = src;
			}
			src->prevBrother->succBrother = src;
		}
		updateHeightAboveAndLeft(src);
		dstParent->size += src->size;
		updateSizeAbove(dstParent, src->size);
	}

	void query(int t_queryType)
	{
		Node* node = findByRoute();
		if (t_queryType == 1)
		{
			printf("%d\n", node->height);
		}
		else
		{
			printf("%d\n", node->size);
		}
	}

	void operate()
	{
		for (int i = 0; i < M; i++)
		{
			int cmdType;
			scanf("%d", &cmdType);
			switch (cmdType)
			{
			case 0:
				move();
				break;
			case 1:
				query(1);
				break;
			case 2:
				query(2);
				break;
			default:
				break;
			}
		}
	}
public:
	~Tree()
	{
		for (int i = 1; i <= N; i++)
		{
			delete allNodes[i];
		}
	}
	void exec()
	{
		scanf("%d%d", &N, &M);
		inputOriTree();	//OK
		operate();
	}
};

Tree tree;

int main()
{
	tree.exec();
	return 0;
}