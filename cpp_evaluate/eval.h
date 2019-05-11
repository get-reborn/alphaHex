#ifndef _EVAL_H_
#define _EVAL_H_

#include <queue>
#include <vector>
#include <algorithm>
#include <string.h>
#include <omp.h>
using namespace std;

#define MAX_SIZE 13
#define Inf SIZE *SIZE
#define BLUE -1
#define EMPTY 0
#define RED 1
#define SEARCH_WIDTH 64    //搜索宽度
#define DEPTHMAX 3       //最大深度
#define LIMIT_DIS SIZE * 4 //最大双距离
#define CHOOSE 1           //选择优先点的权重,越大优势方比重越大，1两者比重相等
#define CONE depth * 20    //锥形搜索宽度递减个数
#define CORE_SIZE 4 //CPU核心数，用于多线程
namespace eval
{
class Evaluate
{
public:
    Evaluate(int size, int Board[], int dis_B_R[], int dis_B_L[], int dis_W_U[], int dis_W_D[]);
    typedef pair<int, int> pos;
    struct feature
    {
        int p;
        int dis;
        bool friend operator<(feature a, feature b)
        {
            return a.dis < b.dis;
        }
    };
    void get_movenum(feature search_pos[], int color, int depth);
    int get_e(int color);

private:
    void double_dis(int color, int side);
    void find_neighbor(feature *n, pos P, int color, int side, int *index, bool *vis);
    void Updata_Potential();
    int SIZE;
    int *Dis_B_R;
    int *Dis_B_L;
    int *Dis_W_U;
    int *Dis_W_D;
    int *board;
    int Potential_B[MAX_SIZE * MAX_SIZE];
    int Potential_W[MAX_SIZE * MAX_SIZE];
    int Potential[MAX_SIZE * MAX_SIZE];
    feature P_W[MAX_SIZE * MAX_SIZE];
    feature P_B[MAX_SIZE * MAX_SIZE];
};
//void out_status();

} // namespace eval
#endif
