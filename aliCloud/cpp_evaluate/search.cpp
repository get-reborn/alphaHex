#include "search.h"
using namespace sear;

#define INF 0x3f3f3f3f

// red -> RED | blue -> BLUE
//extern "C"{
//    SearchTree stPlayer;
//    void setFirst(bool first,int x,int y){
//        //
//        stPlayer = SearchTree();
//        if (first)
//            stPlayer.set_first(RED,pos(x + 1,y + 1));
//        printf("init success!\n");
//    }
//    //my color
//    int  getMove(int x,int y){
//        stPlayer.set_Human_pos(pos(x + 1,y + 1),RED );
//        stPlayer.get_AI_pos(BLUE);
//        pos ans = stPlayer.get_ans();
//        printf("move success!\n");
//        printf("[x:%i,y:%i]\n",ans.first,ans.second);
//        return (ans.first * 11 + ans.second);
//    }
//}

void display()
{
	printf("ok");
}
int SearchTree::find_father(int color, int p, node &n)
{
	if (color == BLUE)
	{
		int *B_par;
		B_par = n.B_par;
		return B_par[p] == p ? p : B_par[p] = find_father(BLUE, B_par[p], n);
	}
	else
	{
		int *W_par;
		W_par = n.W_par;
		return W_par[p] == p ? p : W_par[p] = find_father(RED, W_par[p], n);
	}
}

bool SearchTree::is_connect(int color, int x, int y, node &n)
{
	int fx = find_father(color, x, n);
	int fy = find_father(color, y, n);
	return fx == fy;
}

void SearchTree::merge(int color, int x, int y, node &n)
{
	int fx = find_father(color, x, n);
	int fy = find_father(color, y, n);
	if (fx != fy)
	{
		if (color == BLUE)
		{
			int *B_par;
			B_par = n.B_par;
			B_par[fx] = fy;
		}
		else
		{
			int *W_par;
			W_par = n.W_par;
			W_par[fx] = fy;
		}
	}
}

void SearchTree::connect_neighbor(int color, SearchTree::pos p, node &n)
{
	for (int i = 0; i < 6; i++)
	{
		SearchTree::pos x;
		x.first = p.first + dir[i][1];
		x.second = p.second + dir[i][0];
		int po = x.first * SIZE + x.second;
		if (this->Board[po] == color)
		{
			merge(color, p.first * SIZE + p.second, po, n);
		}
	}
}

void SearchTree::Move(int color, SearchTree::pos p, node &n)
{
	int po = p.first * SIZE + p.second;
	if (color == BLUE)
	{
		this->Board[po] = BLUE;
		connect_neighbor(color, p, n);
	}
	else
	{
		this->Board[po] = RED;
		connect_neighbor(color, p, n);
	}
}

void SearchTree::Unmove(SearchTree::pos p)
{
	int po = p.first * SIZE + p.second;
	Board[po] = EMPTY;
}

void SearchTree::Copy_node(node &child, node &father)
{
	for (int p = 0; p < SIZE * SIZE; p++)
	{
		child.B_par[p] = father.B_par[p];
		child.W_par[p] = father.W_par[p];
		child.dis_B_L[p] = father.dis_B_L[p];
		child.dis_B_R[p] = father.dis_B_R[p];
		child.dis_W_U[p] = father.dis_W_U[p];
		child.dis_W_D[p] = father.dis_W_D[p];
	}
}

int SearchTree::alphabeta(node n, int depth, int alpha, int beta, bool player, int color)
{
	int enemy;
	if (color == RED)
		enemy = BLUE;
	else
		enemy = RED;

	Evaluate evaluate(SIZE, Board, n.dis_B_R, n.dis_B_L, n.dis_W_U, n.dis_W_D);

	if (depth == 0)
	{
		this->value = evaluate.get_e(color);
		Evaluate::feature children_pos[MAX_SIZE * MAX_SIZE];
		evaluate.get_movenum(children_pos, color, depth);
		int t = children_pos[0].dis;
		int index = 1;
		while (index <= t)
		{
			int v;
			node child;
			Copy_node(child, n);
			Evaluate::feature child_pos = children_pos[index++];
			int i = child_pos.p / SIZE;
			int j = child_pos.p % SIZE;
			Move(color, pos(i, j), child);

			v = alphabeta(child, 1, alpha, beta, HUMAN, color);

			this->Move_Array[child_pos.p] = v + 2000 * LIMIT_DIS; //È¡ÕýÊý
			Unmove(pos(i, j));
		}
	}
	else
	{

		if (color == BLUE)
		{
			if (is_connect(color, SIZE, 2 * SIZE - 1, n))
			{
				return 1000 * LIMIT_DIS;
			}
		}
		else
		{
			if (is_connect(color, 1, (SIZE - 1) * SIZE + 1, n))
			{
				return 1000 * LIMIT_DIS;
			}
		}
		if (enemy == BLUE)
		{
			if (is_connect(enemy, SIZE, 2 * SIZE - 1, n))
			{
				return -1000 * LIMIT_DIS;
			}
		}
		else
		{
			if (is_connect(enemy, 1, (SIZE - 1) * SIZE + 1, n))
			{
				return -1000 * LIMIT_DIS;
			}
		}

		if (depth == DEPTHMAX)
		{
			return evaluate.get_e(color);
		}

		if (player == AI)
		{

			int v = -INF;
			//int t = SEARCH_WIDTH - CONE;
			Evaluate::feature children_pos[MAX_SIZE * MAX_SIZE];
			evaluate.get_movenum(children_pos, color, depth); //AI is RED
			/*if (children_pos[0].dis < t)
			{
				t = children_pos[0].dis;
			}*/
			int t = children_pos[0].dis;
			int index = 1;
			while (index <= t)
			{
				node child;
				Copy_node(child, n);
				Evaluate::feature child_pos = children_pos[index++];
				int i = child_pos.p / SIZE;
				int j = child_pos.p % SIZE;
				Move(color, pos(i, j), child);

				v = max(v, alphabeta(child, depth + 1, alpha, beta, HUMAN, color));
				if (alpha < v)
				{
					alpha = v;
				}
				Unmove(pos(i, j));
				if (beta <= alpha)
				{
					break;
				}
			}
			return v;
		}
		else
		{

			int v = INF;
			Evaluate::feature children_pos[MAX_SIZE * MAX_SIZE];
			evaluate.get_movenum(children_pos, enemy, depth); //HUMAN is BLUE
			int t = children_pos[0].dis;
			int index = 1;
			while (index <= t)
			{
				node child;
				Copy_node(child, n);
				Evaluate::feature child_pos = children_pos[index++];
				int i = child_pos.p / SIZE;
				int j = child_pos.p % SIZE;
				Move(enemy, pos(i, j), child);
				v = min(v, alphabeta(child, depth + 1, alpha, beta, AI, color));
				beta = min(beta, v);
				Unmove(pos(i, j));
				if (beta <= alpha)
				{
					break;
				}
			}
			return v;
		}
	}
}
double *SearchTree::Get_Move_Array(int turn)
{
	alphabeta(root, 0, -INF, INF, AI, turn);
	double sum = 0;
	for (int i = 0; i < SIZE * SIZE; i++)
	{
		sum += Move_Array[i];
	}

	array = new double[SIZE * SIZE];
	//delete[] array;

	for (int i = 0; i < SIZE * SIZE; i++)
	{
		array[i] = Move_Array[i] / sum;
	}
	return array;
}
int SearchTree::Get_Value()
{
	return this->value;
}

SearchTree::SearchTree(int size, int board[])
{
	this->SIZE = size;
	// ÆåÅÌ±ßÔµ´¦Àí

	memset(root.dis_B_L, 0, sizeof(root.dis_B_L));
	memset(root.dis_B_R, 0, sizeof(root.dis_B_R));
	memset(root.dis_W_D, 0, sizeof(root.dis_W_D));
	memset(root.dis_W_U, 0, sizeof(root.dis_W_U));
	// ²¢²é¼¯³õÊ¼»¯ && ¸´ÖÆÆåÅÌ
	for (int p = 0; p < SIZE * SIZE; p++)
	{
		this->Board[p] = board[p];
		this->root.B_par[p] = p;
		this->root.W_par[p] = p;
	}
	for (int m = 1; m <= SIZE - 2; m++)
	{
		this->Board[m * SIZE] = BLUE;
		this->Board[(m + 1) * SIZE - 1] = BLUE;
		this->Board[m] = RED;
		this->Board[(SIZE - 1) * SIZE + m] = RED;
	}
	// ±ßÔµ²¢²é¼¯·Ö×é
	for (int m = 1; m <= SIZE - 2; m++)
	{
		this->root.B_par[m * SIZE] = SIZE;
		this->root.B_par[(m + 1) * SIZE - 1] = 2 * SIZE - 1;
		this->root.W_par[m] = 1;
		this->root.W_par[(SIZE - 1) * SIZE + m] = (SIZE - 1) * SIZE + 1;
	}
	for (int i = 1; i <= this->SIZE - 2; i++)
	{
		for (int j = 1; j <= this->SIZE - 2; j++)
		{
			if (this->Board[i * this->SIZE + j] != EMPTY)
				connect_neighbor(this->Board[i * this->SIZE + j], pos(i, j), root);
		}
	}
}
SearchTree::~SearchTree()
{
	delete[] array;
}