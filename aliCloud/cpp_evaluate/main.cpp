#include <iostream>
#include "eval.h"
#include "search.h"
using namespace std;
using namespace sear;
using namespace eval;
//g++ -o libpymcts.so -shared -fPIC main.cpp eval.cpp search.cpp
#ifndef MODEL_DISPLAY
//#define MODEL_DISPLAY
#endif
extern "C"
{
	double getMove(int *board, int size, double *ans, double *value)
	{
		int treeSize = size + 2; //0 10 | 0 12
		//cout<<size<<endl;
		int treeBoard[treeSize * treeSize];
		double *arr;
		for (size_t i = 0; i < treeSize * treeSize; ++i)
		{
			treeBoard[i] = 0;
		}

		for (size_t i = 1; i < treeSize - 1; ++i)
		{
			for (size_t j = 1; j < treeSize - 1; ++j)
			{
				treeBoard[i * treeSize + j] = board[(i - 1) * size + (j - 1)];
			}
		}
#ifdef MODEL_DISPLAY
		for (size_t i = 0; i < treeSize; ++i)
		{
			for (size_t j = 0; j < treeSize; ++j)
			{
				cout << treeBoard[i * treeSize + j] << " ";
			}
			cout << endl;
		}
		cout << "=============================================" << endl;
#endif
		SearchTree tree(treeSize, treeBoard);
		arr = tree.Get_Move_Array(RED);
		for (size_t i = 0; i < size; ++i)
		{
			for (size_t j = 0; j < size; ++j)
			{
				ans[i * size + j] = arr[(i + 1) * treeSize + (j + 1)];
			}
		}
		return tree.Get_Value();
	}
}