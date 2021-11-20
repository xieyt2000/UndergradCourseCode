#include "UCT.h"
#include <cmath>
#include <cstdlib>
#include <iostream>


//a pool of nodes to avoid new and delete
Array<UCTNode, MAX_NODE> nodePool;




UCTNode* UCT::treePolicy(int board[][MAX_N], int top[], int& winner)
{
	UCTNode* iterNode = &root;
	while (true)
	{
		if (!iterNode->avaMoveY.empty() && !nodePool.full())
		{
			return expand(*iterNode, board, top, winner);
		}
#ifdef NODE_NOT_FULL
		if (nodePool.full())
		{
			throw "?";
		}
#endif // NODE_NOT_FULL
		if (iterNode->children.empty())
		{
			return iterNode;
		}
		iterNode = select(*iterNode, board, top, winner);
	}
	return iterNode;
}

UCTNode* UCT::select(UCTNode& parent, int currentBoard[][MAX_N], int currentTop[], int& winner)
{
	UCTNode* ret = nullptr;
	double score = DOB_NEG_INF;
	for (int i = 0; i < parent.children.getSize(); i++)
	{
		UCTNode* child = parent.children[i];
		double tmpScore = child->winRate() + UCB_EXPLOR * sqrtLogTotal / sqrt(child->visits);
		if (tmpScore > score)
		{
			score = tmpScore;
			ret = child;
		}
	}
	winner = takeMove(ret->move, currentBoard, currentTop, ret->player);
	return ret;
}

UCTNode* UCT::expand(UCTNode& parent, int currentBoard[][MAX_N], int currentTop[], int& winner)
{
	int moveY = parent.avaMoveY.pop();
	Point move(currentTop[moveY] - 1, moveY);
	nodePool.push(UCTNode(anotherPlayer(parent.player), move, &parent));
	UCTNode* child = &(nodePool.last());
	parent.children.push(child);
	winner = takeMove(move, currentBoard, currentTop, child->player);
	if (winner < 0)	//game not end
	{
		copyMoveFromTop(currentTop, currentBoard, *child);
	}
	return child;
}

int UCT::defaultPolicy(int player, int currentBoard[][MAX_N], int currentTop[])
{
	Array<Point> avaiMoves;
	int winner = -1;
	int currentPlayer = player;
	while (winner < 0)
	{
		currentPlayer = anotherPlayer(currentPlayer);	//the player to take move
		getAvaiMoveFromTop(currentTop, N, avaiMoves);
		Point randMove = avaiMoves[rand() % avaiMoves.getSize()];
		winner = takeMove(randMove, currentBoard, currentTop, currentPlayer);
	}
	return winnerToResult(player, winner);
}

int UCT::guidedPolicy(int player, int currentBoard[][MAX_N], int currentTop[])
{
	Array<Point> avaiMoves;
	int moveScores[MAX_N];
	int winner = -1;
	int currentPlayer = player;
	while (winner < 0)
	{
		currentPlayer = anotherPlayer(currentPlayer);	//the player to take move
		getAvaiMoveFromTop(currentTop, N, avaiMoves);
		int totalScore = 0;
		for (int i = 0; i < avaiMoves.getSize(); i++)
		{
			moveScores[i] = getMoveScore(avaiMoves[i].x, avaiMoves[i].y, M, N, currentBoard, currentPlayer);
			moveScores[i] += getMoveScore(avaiMoves[i].x, avaiMoves[i].y, M, N, currentBoard, anotherPlayer(currentPlayer));
			totalScore += moveScores[i];
		}
		int accumScore = 0;
		int randNum = rand() % totalScore;
		Point move;
		for (int i = 0; i < avaiMoves.getSize(); i++)
		{
			accumScore += moveScores[i];
			if (randNum < accumScore)
			{
				move = avaiMoves[i];
				break;
			}
		}
		winner = takeMove(move, currentBoard, currentTop, currentPlayer);
	}
	return winnerToResult(player, winner);
}

void UCT::backProp(UCTNode& startNode, int result)
{
	for (UCTNode* iterNode = &startNode; iterNode != nullptr; iterNode = iterNode->parent)
	{
		iterNode->wins += result;
		result = -result;
		iterNode->visits++;
	}
}

void UCT::revertMove(const Point& move, int board[][MAX_N], int top[], const int movePlayer)
{
	board[move.x][move.y] = 0;
	top[move.y]++;
	if (move.y == ban.y && move.x == (ban.x + 1))
	{
		top[move.y]++;
	}
}

int UCT::takeMove(const Point& move, int board [][MAX_N], int top[], const int movePlayer)
{
	bool win = false;
	board[move.x][move.y] = movePlayer;
	top[move.y]--;
	if (move.y == ban.y && move.x == (ban.x + 1))
	{
		top[move.y]--;
	}
	if (movePlayer == USER)
	{
		win = userWin(move.x, move.y, M, N, board);
	}
	else
	{
		win = machineWin(move.x, move.y, M, N, board);
	}
	if (win)
	{
		return movePlayer;
	}
	if (isTie(N, top))
	{
		return 0;
	}
	return -1;
}

void UCT::copyBoard(const int src[][MAX_N], int dst[][MAX_N])
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			dst[i][j] = src[i][j];
		}
	}
}

void UCT::copyTop(const int src[], int dst[])
{
	for (int i = 0; i < N; i++)
	{
		dst[i] = src[i];
	}
}

inline void UCT::copyMoveFromTop(int top[], int currentBoard[][MAX_N], UCTNode& node)
{
	for (int i = 0; i < N; i++)
	{
		if (top[i] > 0)
		{
			node.avaMoveY.push(i);
		}
	}
}



Point UCT::main()
{
	clock_t start = clock();
	srand(time(nullptr));
	int searchCnt = 0;
	while (true)
	{
		searchCnt++;
#ifdef USE_TIME_LIMIT
		if (searchCnt % 1000 == 0)
		{
			clock_t tmpEnd = clock();
			if ((tmpEnd - start) > TIME_LIMIT)
			{
				std::cerr<<searchCnt<<std::endl;
				break;
			}
		}
#endif // USE_TIME_LIMIT
#ifdef USE_COUNT_LIMIT
		if (searchCnt > COUNT_LIME)
		{
			break;
		}
#endif // USE_COUNT_LIMIT
		int currentBoard[MAX_M][MAX_N];
		int currentTop[MAX_N];
		copyBoard(oriBoard, currentBoard);
		copyTop(oriTop, currentTop);
		int winner = -1;
		UCTNode* expandedNode = treePolicy(currentBoard, currentTop, winner);
		int result;
		if (winner < 0)
		{
#ifdef USE_GUIDED_POLICY
			result = guidedPolicy(expandedNode->player, currentBoard, currentTop);
#else
			result = defaultPolicy(expandedNode->player, currentBoard, currentTop);
#endif	// USE_GUIDED_POLICY
		}
		else
		{
			result = winnerToResult(expandedNode->player, winner);
		}
		backProp(*expandedNode, result);
		total++;
		sqrtLogTotal = sqrt(log(total));
	}
	return root.mostVisitedChildMove();
}

UCT::UCT(const int t_m, const int t_n, const Point& t_ban, const int t_player, int** t_board, const int* t_top)
	: M(t_m), N(t_n), ban(t_ban), oriPlayer(t_player), root(anotherPlayer(oriPlayer), Point(-1,-1), nullptr)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			oriBoard[i][j] = t_board[i][j];
		}
	}
	for (int i = 0; i < N; i++)
	{
		oriTop[i] = t_top[i];
	}
	copyMoveFromTop(oriTop, oriBoard, root);
}

UCT::~UCT()
{
	nodePool.clear();
}

double UCTNode::winRate() const
{
	return (wins + 0.0) / visits;
}

inline Point UCTNode::mostVisitedChildMove()
{
	int maxVisits = -1;
	Point retPoint;
	for (int i = 0; i < children.getSize(); i++)
	{
		UCTNode* iterChild = children[i];
		if (iterChild->visits > maxVisits)
		{
			maxVisits = iterChild->visits;
			retPoint = iterChild->move;
		}
	}
	return retPoint;
}
