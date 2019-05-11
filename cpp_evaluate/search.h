#ifndef SEARCH_H
#define SEARCH_H

#include "eval.h"
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <iostream>
#define AI true
#define HUMAN false

using namespace std;
using namespace eval;
namespace sear
{
class SearchTree
{
public:
	//typedef pair<int, int> pos;
	SearchTree(int size, int board[]);
	~SearchTree();
	double *Get_Move_Array(int turn);
	int Get_Value();
	/*bool set_Human_pos(pos p, int color);
        bool get_AI_pos(int color);
        pos get_ans();*/
	//void set_first(int color,pos position);
private:
	int ans;
	int SIZE;
	int value;
	double *array;
	const int dir[6][2] = {{-1, 0}, {0, -1}, {1, -1}, {1, 0}, {0, 1}, {-1, 1}};
	typedef pair<int, int> pos;
	int Board[MAX_SIZE * MAX_SIZE] = {0};
	int Move_Array[MAX_SIZE * MAX_SIZE] = {0};
	struct node
	{
		int B_par[MAX_SIZE * MAX_SIZE];
		int W_par[MAX_SIZE * MAX_SIZE];
		int dis_B_R[MAX_SIZE * MAX_SIZE];
		int dis_B_L[MAX_SIZE * MAX_SIZE];
		int dis_W_U[MAX_SIZE * MAX_SIZE];
		int dis_W_D[MAX_SIZE * MAX_SIZE];
	};
	node root;
	int find_father(int color, int p, node &n);
	bool is_connect(int color, int x, int y, node &n);
	void merge(int color, int x, int y, node &n);
	void connect_neighbor(int color, pos p, node &n);
	void Move(int color, pos p, node &n);
	void Unmove(pos p);
	void Copy_node(node &child, node &father);
	int alphabeta(node n, int depth, int alpha, int beta, bool player, int color);
};

} // namespace sear

#endif
