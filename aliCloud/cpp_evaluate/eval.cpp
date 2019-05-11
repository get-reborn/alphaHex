#include "eval.h"
#define left 0
#define up 1
#define right 2
#define down 3

using namespace eval;

const int dir[6][2] = {{-1, 0}, {0, -1}, {1, -1}, {1, 0}, {0, 1}, {-1, 1}};

void Evaluate::Updata_Potential()
{
    double_dis(BLUE, left);
    double_dis(BLUE, right);
    double_dis(RED, up);
    double_dis(RED, down);
    int index = 1;
    for (int p = SIZE + 1; p < SIZE * (SIZE - 1) - 1; p++)
    {
        if (board[p] == EMPTY)
        {
            Potential_B[p] = Dis_B_L[p] + Dis_B_R[p];
            Potential_W[p] = Dis_W_U[p] + Dis_W_D[p];

            feature f;
            f.p = p;
            f.dis = Potential_W[p];
            P_W[index] = f;
            f.dis = Potential_B[p];
            P_B[index] = f;
            index++;
        }
    }
    P_W[0].dis = index;
    P_B[0].dis = index;
}
void Evaluate::double_dis(int color, int side)
{
    if (color == BLUE)
    {
        if (side == left)
        {
            bool change = true;
            while (change)
            {
                change = false;
                for (int j = 1; j <= SIZE - 2; j++)
                {
                    for (int i = 1; i <= SIZE - 2; i++)
                    {
                        int po = i * SIZE + j;
                        if (board[po] == EMPTY && Dis_B_L[po] < LIMIT_DIS)
                        {
                            if (j == 1)
                            {
                                Dis_B_L[po] = 1;
                                continue;
                            }

                            bool vis[MAX_SIZE * MAX_SIZE] = {false};
                            vis[po] = true;
                            feature neighbor[MAX_SIZE * MAX_SIZE];
                            int index = 0;
                            find_neighbor(neighbor, pos(i, j), color, side, &index, vis);
                            sort(neighbor, neighbor + index);
                            if (index == 0)
                            {
                                //Dis_B_L[po] = Inf;
                                Dis_B_L[po] = LIMIT_DIS;
                            }
                            else if (index == 1)
                            {

                                if (Dis_B_L[po] != neighbor[0].dis + 1 /*&& Dis_B_L[po] < LIMIT_DIS*/)
                                {
                                    Dis_B_L[po] = neighbor[0].dis + 1;
                                    change = true;
                                }
                                //if (Dis_B_L[po] >= LIMIT_DIS)
                                //{
                                //    //Dis_B_L[po] = Inf;
                                //    continue;
                                //}
                            }
                            else
                            {
                                if (Dis_B_L[po] != neighbor[1].dis + 1 /* && Dis_B_L[po] < LIMIT_DIS*/)
                                {

                                    Dis_B_L[po] = neighbor[1].dis + 1;
                                    change = true;
                                }
                                //if (Dis_B_L[po] >= LIMIT_DIS)
                                //{
                                //    //Dis_B_L[po] = Inf;
                                //    continue;
                                //}
                            }
                        }
                        else
                        {
                            //Dis_B_L[po] = Inf;
                            Dis_B_L[po] = LIMIT_DIS;
                        }
                    }
                }
            }
        }
        if (side == right)
        {
            bool change = true;
            while (change)
            {
                change = false;
                for (int j = SIZE - 2; j >= 1; j--)
                {
                    for (int i = SIZE - 2; i >= 1; i--)
                    {
                        int po = i * SIZE + j;
                        if (board[po] == EMPTY && Dis_B_R[po] < LIMIT_DIS)
                        {
                            if (j == SIZE - 2)
                            {
                                Dis_B_R[po] = 1;
                                continue;
                            }

                            bool vis[MAX_SIZE * MAX_SIZE] = {false};
                            vis[po] = true;
                            feature neighbor[MAX_SIZE * MAX_SIZE];
                            int index = 0;
                            find_neighbor(neighbor, pos(i, j), color, side, &index, vis);
                            sort(neighbor, neighbor + index);
                            if (index == 0)
                            {
                                Dis_B_R[po] = LIMIT_DIS;
                            }
                            else if (index == 1)
                            {

                                if (Dis_B_R[po] != neighbor[0].dis + 1 /* && Dis_B_R[po] < LIMIT_DIS*/)
                                {
                                    Dis_B_R[po] = neighbor[0].dis + 1;
                                    change = true;
                                }
                                //if (Dis_B_R[po] >= LIMIT_DIS)
                                //{
                                //    //Dis_B_R[po] = LIMIT_DIS;
                                //    continue;
                                //}
                            }
                            else
                            {

                                if (Dis_B_R[po] != neighbor[1].dis + 1 /* && Dis_B_R[po] < LIMIT_DIS*/)
                                {
                                    Dis_B_R[po] = neighbor[1].dis + 1;
                                    change = true;
                                }
                                //if (Dis_B_R[po] >= LIMIT_DIS)
                                //{
                                //    //Dis_B_R[po] = LIMIT_DIS;
                                //    continue;
                                //}
                            }
                        }
                        else
                        {
                            Dis_B_R[po] = LIMIT_DIS;
                        }
                    }
                }
            }
        }
    }
    if (color == RED)
    {
        if (side == up)
        {
            bool change = true;
            while (change)
            {
                change = false;
                for (int i = 1; i <= SIZE - 2; i++)
                {
                    for (int j = 1; j <= SIZE - 2; j++)
                    {
                        int po = i * SIZE + j;
                        if (board[po] == EMPTY && Dis_W_U[po] < LIMIT_DIS)
                        {
                            if (i == 1)
                            {
                                Dis_W_U[po] = 1;
                                continue;
                            }

                            bool vis[MAX_SIZE * MAX_SIZE] = {false};
                            vis[po] = true;
                            feature neighbor[MAX_SIZE * MAX_SIZE];
                            int index = 0;
                            find_neighbor(neighbor, pos(i, j), color, side, &index, vis);
                            sort(neighbor, neighbor + index);
                            if (index == 0)
                            {
                                Dis_W_U[po] = LIMIT_DIS;
                            }
                            else if (index == 1)
                            {
                                if (Dis_W_U[po] != neighbor[0].dis + 1 /* && Dis_W_U[po] < LIMIT_DIS*/)
                                {
                                    Dis_W_U[po] = neighbor[0].dis + 1;
                                    change = true;
                                }
                                //if (Dis_W_U[po] >= LIMIT_DIS)
                                //{
                                //    //Dis_W_U[po] = Inf;
                                //    continue;
                                //}
                            }
                            else
                            {

                                if (Dis_W_U[po] != neighbor[1].dis + 1 /* && Dis_W_U[po] < LIMIT_DIS*/)
                                {
                                    Dis_W_U[po] = neighbor[1].dis + 1;
                                    change = true;
                                }
                                //if (Dis_W_U[po] >= LIMIT_DIS)
                                //{
                                //    //Dis_W_U[po] = Inf;
                                //    continue;
                                //}
                            }
                        }
                        else
                        {
                            Dis_W_U[po] = LIMIT_DIS;
                        }
                    }
                }
            }
        }
        if (side == down)
        {
            bool change = true;
            while (change)
            {
                change = false;
                for (int i = SIZE - 2; i >= 1; i--)
                {
                    for (int j = SIZE - 2; j >= 1; j--)
                    {
                        int po = i * SIZE + j;
                        if (board[po] == EMPTY && Dis_W_D[po] < LIMIT_DIS)
                        {
                            if (i == SIZE - 2)
                            {
                                Dis_W_D[po] = 1;
                                continue;
                            }

                            bool vis[MAX_SIZE * MAX_SIZE] = {false};
                            vis[po] = true;
                            feature neighbor[MAX_SIZE * MAX_SIZE];
                            int index = 0;
                            find_neighbor(neighbor, pos(i, j), color, side, &index, vis);
                            sort(neighbor, neighbor + index);
                            if (index == 0)
                            {
                                Dis_W_D[po] = LIMIT_DIS;
                            }
                            else if (index == 1)
                            {

                                if (Dis_W_D[po] != neighbor[0].dis + 1 /* && Dis_W_D[po] < LIMIT_DIS*/)
                                {
                                    Dis_W_D[po] = neighbor[0].dis + 1;
                                    change = true;
                                }
                                //if (Dis_W_D[po] >= LIMIT_DIS)
                                //{
                                //    //Dis_W_D[po] = Inf;
                                //    continue;
                                //}
                            }
                            else
                            {

                                if (Dis_W_D[po] != neighbor[1].dis + 1 /* && Dis_W_D[po] < LIMIT_DIS*/)
                                {
                                    Dis_W_D[po] = neighbor[1].dis + 1;
                                    change = true;
                                }
                                //if (Dis_W_D[po] >= LIMIT_DIS)
                                //{
                                //    //Dis_W_D[po] = Inf;
                                //    continue;
                                //}
                            }
                        }
                        else
                        {
                            Dis_W_D[po] = LIMIT_DIS;
                        }
                    }
                }
            }
        }
    }
}
void Evaluate::find_neighbor(feature *n, pos P, int color, int side, int *index, bool *vis)
{
    if (color == BLUE)
    {
        for (int i = 0; i < 6; i++)
        {
            pos p;
            p.first = P.first + dir[i][1];
            p.second = P.second + dir[i][0];
            int po = p.first * SIZE + p.second;
            if (p.first < SIZE - 1 && p.first > 0 && p.second <= SIZE - 1 && p.second >= 0 && !vis[po])
            {

                if (board[po] == BLUE)
                {
                    vis[po] = true;
                    find_neighbor(n, p, BLUE, side, index, vis);
                }
                else if (board[po] == RED)
                {
                    vis[po] = true;
                    continue;
                }
                else if (board[po] == EMPTY)
                {
                    vis[po] = true;
                    feature f;
                    f.p = po;
                    if (side == left)
                        f.dis = Dis_B_L[po];
                    else if (side == right)
                        f.dis = Dis_B_R[po];
                    n[(*index)++] = f;
                }
            }
        }
    }
    else if (color == RED)
    {
        for (int i = 0; i < 6; i++)
        {
            pos p;
            p.first = P.first + dir[i][1];
            p.second = P.second + dir[i][0];
            int po = p.first * SIZE + p.second;
            if (p.first <= SIZE - 1 && p.first >= 0 && p.second < SIZE - 1 && p.second > 0 && !vis[po])
            {
                if (board[po] == RED)
                {
                    vis[po] = true;
                    find_neighbor(n, p, RED, side, index, vis);
                }
                if (board[po] == BLUE)
                {
                    vis[po] = true;
                    continue;
                }
                if (board[po] == EMPTY)
                {
                    vis[po] = true;
                    feature f;
                    f.p = po;
                    if (side == up)
                        f.dis = Dis_W_U[po];
                    else if (side == down)
                        f.dis = Dis_W_D[po];
                    n[(*index)++] = f;
                }
            }
        }
    }
}

void Evaluate::get_movenum(feature search_pos[], int color, int depth)
{
    feature search_node[MAX_SIZE * MAX_SIZE];
    int index = 1;
    for (int po = SIZE + 1; po < SIZE * (SIZE - 1) - 1; po++)
    {
        if (board[po] == EMPTY)
        {
            if (color == BLUE)
            {
                Potential[po] = Potential_B[po] + Potential_W[po] * CHOOSE;
            }
            else
            {
                Potential[po] = Potential_B[po] * CHOOSE + Potential_W[po];
            }

            feature f;
            f.p = po;
            f.dis = Potential[po];
            search_node[index++] = f;
        }
    }

    sort(search_node + 1, search_node + index);
    if (index - 1 > SEARCH_WIDTH - CONE)
    {
        search_pos[0].dis = SEARCH_WIDTH - CONE;
        int t = 1;
        while (t <= SEARCH_WIDTH - CONE)
        {
            search_pos[t] = search_node[t];
            t++;
        }
    }
    else
    {
        search_pos[0].dis = index - 1;
        int t = 1;
        while (t <= index - 1)
        {
            search_pos[t] = search_node[t];
            t++;
        }
    }
}

int Evaluate::get_e(int color)
{
    int index = P_B[0].dis - 1;
    sort(P_B + 1, P_B + index);
    sort(P_W + 1, P_W + index);
    int e;
    int Pb = P_B[1].dis;
    int Pw = P_W[1].dis;
    int ab = 0;
    int aw = 0;
    int i = 1;
    while (i <= index)
    {
        if (P_B[i].dis == Pb)
            ab++;
        else
            break;
        i++;
    }
    i = 1;
    index = P_W[0].dis - 1;
    while (i <= index)
    {
        if (P_W[i].dis == Pw)
            aw++;
        else
            break;
        i++;
    }
    if (color == RED)
        e = 100 * (Pb - Pw) - (ab - aw);
    else
        e = 100 * (Pw - Pb) - (aw - ab);
    return e;
}

Evaluate::Evaluate(int size, int Board[], int dis_B_R[], int dis_B_L[], int dis_W_U[], int dis_W_D[])
{
    this->SIZE = size;
    this->board = Board;
    this->Dis_B_L = dis_B_L;
    this->Dis_B_R = dis_B_R;
    this->Dis_W_D = dis_W_D;
    this->Dis_W_U = dis_W_U;
    this->Updata_Potential();
}
