#pragma once
#include "Point.h"
#include "constants.h"
#include "Array.h"
#include "Judge.h"
#include "function.h"
#include <cstdlib>


struct UCTNode	//only store the top. no need to store board
{
	int player;	//which player takes `move`
	Point move;	//parent take this move and go to myself
	int visits = 0;
	int wins = 0;	//simulate. if `player` win through this node, wins++
	Array<UCTNode*> children;
	Array<int> avaMoveY;	//status to expand child. Y of available moves. get X of the move by `currentTop`. anotherplayer take these moves
	UCTNode* parent;
	UCTNode(int t_player, const Point& t_move, UCTNode* t_parent) : player(t_player), move(t_move), parent(t_parent) {}
	inline double winRate() const;
	UCTNode() {}
	
	inline Point mostVisitedChildMove();	//move of child with most visits
};

//Upper Confidence Tree for Monte Carlo
class UCT
{
private:
	const int M;
	const int N;
	const Point ban;
	const int oriPlayer;
	int oriBoard[MAX_M][MAX_N];
	int oriTop[MAX_N];
	UCTNode root;
	int total = 0;
	double sqrtLogTotal = 0;	//sqrt(ln(totla)). accelerate UCB computation

	//select and expand. output the status to board and top. if select to a leaf (game end), winner >=0.
	UCTNode* treePolicy(int board[][MAX_N], int top[], int& winner);
	//select the child with best score. return nullptr if no child
	UCTNode* select(UCTNode& parent, int currentBoard[][MAX_N], int currentTop[], int& winner);
	//expand child from parent.avaMoveTop.pop()
	UCTNode* expand(UCTNode& parent, int currentBoard[][MAX_N], int currentTop[], int& winner);
	//simulate with default policy (random choose each step). return winner (0, 1, 2)
	int defaultPolicy(int player, int board[][MAX_N], int top[]);
	//simulate with guided policy (with value function). return winner (0, 1, 2)
	int guidedPolicy(int player, int board[][MAX_N], int top[]);
	//backpropagate from node to root
	void backProp(UCTNode& startNode, int result);
	//revert the move taken
	void revertMove(const Point& move, int board[][MAX_N], int top[], const int movePlayer);
	//take a move in board, return win(player, 1 or 2), draw(0) or not end(-1)
	int takeMove(const Point& move, int currentBoard[][MAX_N], int currentTop[], const int movePlayer);
	//copy src board to dst board
	void copyBoard(const int src[][MAX_N], int dst[][MAX_N]);
	//copy src top to dst top
	void copyTop(const int src[], int dst[]);
	//get a node's childres's moe from top
	inline void copyMoveFromTop(int top[], int currentBoard[][MAX_N], UCTNode& node);

public:
	Point main();	//entrance to uct search
	UCT(const int t_m, const int t_n, const Point& t_ban, const int t_player, int** t_board, const int* t_top);
	~UCT();
};