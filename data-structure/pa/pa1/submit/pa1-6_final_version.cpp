#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<stdlib.h>

const int MAX_LENGTH = 1e7;

//cursor between prev and succ
struct Cursor
{
	int prev;
	int succ;
	Cursor(int t_p, int t_s) : prev(t_p), succ(t_s) {}
	bool valid()
	{
		return prev != -1 && succ != -1;
	}
};

//for reverse purpose, links between nodes are undirected
//for time purpose, don't free the space after node deleted(i.e. don't change freeStrat)
class List
{
private:
	enum CursorSide
	{
		left, right
	};
	enum CursorRelativePos
	{
		defalt,	//leftCuror left of rightCursor
		reversed,
		coincide
	};
	char* m_data;
	int* m_adj1, * m_adj2;	//default: adj1 is prev and adj2 is succ
	int m_dataHead, m_dataTail, m_freeStart;
	Cursor m_leftCursor, m_rightCursor;
	CursorRelativePos relativePos = defalt;

	Cursor* getCursor()
	{
		char cursorChar;
		cursorChar = getchar();
		if (cursorChar == 'L')
		{
			return &m_leftCursor;
		}
		else
		{
			return &m_rightCursor;
		}
	}

	Cursor* getAnotherCursor(Cursor* t_cursor)
	{
		return (t_cursor == &m_leftCursor ? &m_rightCursor : &m_leftCursor);
	}

	int& getAnotherAdj(int t_index, int t_knownAdj)
	{
		if (m_adj1[t_index] != t_knownAdj)
		{
			return m_adj1[t_index];
		}
		return m_adj2[t_index];
	}

	int& getThisAdj(int t_index, int t_knownAdj)
	{
		if (m_adj1[t_index] == t_knownAdj)
		{
			return m_adj1[t_index];
		}
		return m_adj2[t_index];
	}

	void move(Cursor* t_cursor, CursorSide t_moveSide)	//might cause change in cursor relative pos
	{
		if ((t_cursor->prev == m_dataHead && t_moveSide == left)
			|| (t_cursor->succ == m_dataTail && t_moveSide == right))
		{
			printf("F\n");
			return;
		}
		int newPrev, newSucc;
		switch (t_moveSide)
		{
		case left:
		{
			newSucc = t_cursor->prev;
			newPrev = getAnotherAdj(t_cursor->prev, t_cursor->succ);
			break;
		}
		case right:
		{
			newPrev = t_cursor->succ;
			newSucc = getAnotherAdj(t_cursor->succ, t_cursor->prev);
			break;
		}
		}
		//set cursor
		Cursor* anothoerCursor = getAnotherCursor(t_cursor);
		if (relativePos == coincide)
		{
			if (t_cursor == &m_leftCursor)
			{
				if (t_moveSide == left) relativePos = defalt;
				else relativePos = reversed;
			}
			else
			{
				if (t_moveSide == left) relativePos = reversed;
				else relativePos = defalt;
			}
		}
		else
		{
			if (newPrev == anothoerCursor->prev) relativePos = coincide;
		}
		t_cursor->prev = newPrev; t_cursor->succ = newSucc;
		printf("T\n");
	}

	void insert(Cursor* t_cursor)	//wont cause change in cursor relative pos
	{
		getchar();//space
		char insertChar;
		insertChar = getchar();
		int prevIndex = t_cursor->prev, succIndex = t_cursor->succ;
		m_data[m_freeStart] = insertChar;
		m_adj1[m_freeStart] = prevIndex; m_adj2[m_freeStart] = succIndex;	//set insert prev and succ
		getThisAdj(prevIndex, succIndex) = m_freeStart;	//succ of prev set to insert
		getThisAdj(succIndex, prevIndex) = m_freeStart;	//prev of succ set to insert
		//set cursor
		t_cursor->prev = m_freeStart;
		if (relativePos == coincide)
		{
			getAnotherCursor(t_cursor)->prev = m_freeStart;
		}
		m_freeStart++;
		printf("T\n");
	}

	void delete_(Cursor* t_cursor)	//might cause change in cursor relative pos
	{
		if (t_cursor->succ == m_dataTail)
		{
			printf("F\n");
			return;
		}
		int prevIndex = t_cursor->prev, delIndex = t_cursor->succ;
		int succIndex = getAnotherAdj(delIndex, prevIndex);
		getThisAdj(prevIndex, delIndex) = succIndex;	//succ of prev set to succ
		getThisAdj(succIndex, delIndex) = prevIndex;	//prev of succ set to prev
		//set cursor
		t_cursor->succ = succIndex;
		Cursor* anotherCursor = getAnotherCursor(t_cursor);
		if (relativePos == coincide)
		{
			anotherCursor->succ = succIndex;
		}
		if (anotherCursor->succ == t_cursor->succ)
		{
			relativePos = coincide;
			anotherCursor->prev = t_cursor->prev;
		}
		printf("T\n");
	}

	void reverse()
	{
		if (relativePos != defalt)
		{
			printf("F\n");
			return;
		}
		//set the node outside the reverse interval
		getThisAdj(m_leftCursor.prev, m_leftCursor.succ) = m_rightCursor.prev;
		getThisAdj(m_rightCursor.succ, m_rightCursor.prev) = m_leftCursor.succ;
		//set the node inside the interval
		getThisAdj(m_leftCursor.succ, m_leftCursor.prev) = m_rightCursor.succ;
		getThisAdj(m_rightCursor.prev, m_rightCursor.succ) = m_leftCursor.prev;
		//set cursor
		int tmpIndex = m_leftCursor.succ;
		m_leftCursor.succ = m_rightCursor.prev;
		m_rightCursor.prev = tmpIndex;
		printf("T\n");
	}

	void show()
	{
		for (int i_prev = m_dataHead, i_succ = getAnotherAdj(m_dataHead, -1); i_succ != m_dataTail;)
		{
			printf("%c", m_data[i_succ]);
			int tmp = i_succ;
			i_succ = getAnotherAdj(i_succ, i_prev);
			i_prev = tmp;
		}
		printf("\n");
	}

	void debugShow()
	{
		for (int i_prev = m_dataHead, i_succ = getAnotherAdj(m_dataHead, -1); i_succ != m_dataTail;)
		{
			if (i_prev == m_leftCursor.prev) printf("[");
			if (i_prev == m_rightCursor.prev) printf("]");
			printf("%c", m_data[i_succ]);
			int tmp = i_succ;
			i_succ = getAnotherAdj(i_succ, i_prev);
			i_prev = tmp;
		}
		if (m_dataTail == m_leftCursor.succ) printf("[");
		if (m_dataTail == m_rightCursor.succ) printf("]");
	}

public:
	List() : m_dataHead(0), m_dataTail(1), m_freeStart(2), m_leftCursor(0, 1), m_rightCursor(0, 1)
	{
		m_data = new char[MAX_LENGTH];
		m_adj1 = new int[MAX_LENGTH];
		m_adj2 = new int[MAX_LENGTH];
		m_adj2[m_dataHead] = m_dataTail; m_adj1[m_dataHead] = -1;
		m_adj2[m_dataTail] = -1; m_adj1[m_dataTail] = m_dataHead;
		m_adj2[m_freeStart] = 3; m_adj1[m_freeStart] = -1;
		m_adj2[MAX_LENGTH - 1] = -1; m_adj1[MAX_LENGTH - 1] = MAX_LENGTH - 2;
		for (int i = 3; i < MAX_LENGTH - 1; i++)
		{
			m_adj2[i] = i + 1;
			m_adj1[i] = i - 1;
		}
	}

	~List()
	{
		delete[] m_data;
		delete[] m_adj1;
		delete[] m_adj2;
	}

	void exec()
	{
		char* inputStr = new char[3300000];
		scanf("%s", inputStr);
		int inputLen = strlen(inputStr);
		for (int i = 0; i < inputLen; i++)
		{
			m_data[i + 1] = inputStr[i];
			m_adj1[i + 1] = i; m_adj2[i + 1] = i + 2;
		}
		m_dataTail = inputLen + 1; m_dataHead = 0;
		m_adj1[m_dataHead] = -1; m_adj2[m_dataHead] = 1;
		m_adj1[m_dataTail] = m_dataTail - 1; m_adj2[m_dataTail] = -1;
		m_freeStart = m_dataTail + 1;
		delete[] inputStr;
		m_leftCursor.prev = m_dataHead; m_leftCursor.succ = m_adj2[m_dataHead];
		m_rightCursor.prev = m_adj1[m_dataTail]; m_rightCursor.succ = m_dataTail;
		int N;
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
		{
			char cmdType;
			getchar();	//\n
			cmdType = getchar();
			switch (cmdType)
			{
			case '<':
				getchar();	//space
				move(getCursor(), left);
				break;
			case '>':
				getchar();	//space
				move(getCursor(), right);
				break;
			case 'I':
				getchar();	//space
				insert(getCursor());
				break;
			case 'D':
				getchar();	//space
				delete_(getCursor());
				break;
			case 'R':
				reverse();
				break;
			case 'S':
				show();
				break;
			default:
				break;
			}
			//debugShow();	//debug	
			//printf("\n");
		}
	}
};

int main()
{
	List list;
	list.exec();
	return 0;
}