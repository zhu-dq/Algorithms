/*
	学习迪杰斯特拉算法
	INT_MAX 表示正无穷
	假设有如下带权邻接矩阵
	严老师 数据结构  P189
*/
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
#define WEIGHTMATRIX map<int,map<int,int>>
#define S map<int,int> 
#define U vector<int>

void findShortPos(int v_0, WEIGHTMATRIX & w_matrix, U & u, S & s)
{
	int pos = 0;
	int value = INT_MAX;
	for (auto & si : s)
	{
		for (auto & ui : w_matrix[si.first])
		{
			if (s.count(ui.first))
				continue;
			if (ui.second + si.second < w_matrix[v_0][ui.first])
				w_matrix[v_0][ui.first] = ui.second + si.second;
			if (w_matrix[v_0][ui.first] < value)
			{
				value = w_matrix[v_0][ui.first];
				pos = ui.first;
			}
		}
	}

	s.insert(pos, w_matrix[v_0][pos]);
	u.erase(find(u.begin(), u.end(), pos));
}

/*
	核心算法
	v_0:计算v_0到其他点的最短距离
	S ：已经找到的最短距离的点的集合
	U ：没找到的最短距离的点的集合
*/
void Dijkstra()
{
	int v_0;
	S  s;
	U  u;
	//初始化数据结构
	WEIGHTMATRIX w_matrix;
	/*
	初始化带权邻接矩阵
	假设 V0--V5 的每个id为 110-INT_MAX15
	*/
	w_matrix[110] = { { 110, INT_MAX }, { 111, INT_MAX }, { 112, 10 }, { 113, INT_MAX }, { 114, 30 }, { 115, 100 } };
	w_matrix[111] = { { 110, INT_MAX }, { 111, INT_MAX }, { 112, 5 }, { 113, INT_MAX }, { 114, INT_MAX }, { 115, INT_MAX } };
	w_matrix[112] = { { 110, INT_MAX }, { 111, INT_MAX }, { 112, INT_MAX }, { 113, 50 }, { 114, INT_MAX }, { 115, INT_MAX } };
	w_matrix[113] = { { 110, INT_MAX }, { 111, INT_MAX }, { 112, INT_MAX }, { 113, INT_MAX }, { 114, INT_MAX }, { 115, 10 } };
	w_matrix[114] = { { 110, INT_MAX }, { 111, INT_MAX }, { 112, INT_MAX }, { 113, 20 }, { 114, INT_MAX }, { 110, 60 } };
	w_matrix[115] = { { 110, INT_MAX }, { 111, INT_MAX }, { 112, INT_MAX }, { 113, INT_MAX }, { 114, INT_MAX }, { 110, INT_MAX } };
	v_0 = 110;
	s.insert(110,0);
	u = {111,112,113,114,115};
	//第一次，查找与v_0有连接的所有的点中最近的点
	int pos = w_matrix[110].begin()->first;
	for (auto & item : w_matrix[110])
	{
		if (item.second == INT_MAX)
			continue;
		if (item.second < w_matrix[110][pos])
			pos = item.first;
	}
	s.insert(pos, w_matrix[110][pos]);
	u.erase(find(u.begin(),u.end(),pos));
	while (!u.empty())
	{
		//从S中寻找最短的
		findShortPos(v_0, w_matrix,u,s);
	}
}
int main()
{
	Dijkstra();
	return 0;
}