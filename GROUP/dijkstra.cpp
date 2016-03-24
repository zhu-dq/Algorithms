/*
学习迪杰斯特拉算法
INT_MAX 表示正无穷
假设有如下带权邻接矩阵
严老师 数据结构  P189

这个算法是有一个论点支持的，即：
假设S是已求得最短路径的终点的集合，则：
下一条最短路径（vi）必是下面两种情况之一：
1. v0-vi
2. v0-S-vi

有人要问了：有可能存在一个点 vj（vj不属于S）  v0-vj-vi 比上面两个要小
答：不可能，这个算法比的就是哪个点距离短，我就收了谁。显然v0-vj 比v0-vj-vi要短，我现在已经在考虑vi了，说明vj已经被我收了啊
*/
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
#define WEIGHTMATRIX map<int,map<int,int>>
#define S map<int,int> 
#define U vector<int>

//int findShortPos(int v_0, WEIGHTMATRIX & w_matrix, U & u, S & s)//优化
pair<int, int> findShortPos(int v_0, WEIGHTMATRIX & w_matrix, U & u, S & s, pair< int, int> si)//优化
{
	int pos = 0;
	int value = INT_MAX;
	/*
		为什么可以不用遍历，因为这是重复劳动！！！
		假设总共三个节点：s1、s2、s3
		第一次： s = {s1}
		v0-ui 的距离  v1-s1-ui的情况我全遍历了,并且知道v0-s2最短
		第二次： s = {s1,s2}
		v0-ui 的距离  v1-s1-ui的情况我全遍历了  (这里很明显是重复劳动啊,因为v1-s1-ui我已经考虑过了啊，v1-s1-ui的距离又不会变)
		v0-ui 的距离   v1-s2-ui的情况我全遍历了
		
		所以，有人可能会问:v0-ui 的距离也考虑过了，为什么还要更新。答：因为v0-ui的距离每次都可能会被改变啊！！！
	*/
	//for (auto & si : s)//s中存的点  优化    //因为上面论点的支撑
	//{                     //优化
		for (auto & ui : w_matrix[si.first])//与si有连接的点
		{
			if (s.count(ui.first))//已经存在s中了
				continue;
			if (ui.second == INT_MAX) //s1与ui没有连接
				continue;
			if (ui.second + si.second < w_matrix[v_0][ui.first])//更新w_matrix[v_0][ui]
				w_matrix[v_0][ui.first] = ui.second + si.second;
			if (ui.second + si.second < value)//寻找距离离v_0最短的
			{
				value = w_matrix[v_0][ui.first];
				pos = ui.first;
			}
		}
	//}  //优化
	if (value == INT_MAX)
		return pair<int,int>(-1,-1);
	s.insert(S::value_type(pos, w_matrix[v_0][pos]));
	u.erase(find(u.begin(), u.end(), pos));
	return pair<int, int>(pos,value);
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
	map<int,int> m110 = { { 110, INT_MAX }, { 111, INT_MAX }, { 112, 10 }, { 113, INT_MAX }, { 114, 30 }, { 115, 100 } }; 
	w_matrix[110] = m110;
	map<int,int> m111 = { { 110, INT_MAX }, { 111, INT_MAX }, { 112, 5 }, { 113, INT_MAX }, { 114, INT_MAX }, { 115, INT_MAX } };
	w_matrix[111] = m111;
	map<int,int> m112 =  { { 110, INT_MAX }, { 111, INT_MAX }, { 112, INT_MAX }, { 113, 50 }, { 114, INT_MAX }, { 115, INT_MAX } };
	w_matrix[112] = m112;
	map<int,int> m113 = { { 110, INT_MAX }, { 111, INT_MAX }, { 112, INT_MAX }, { 113, INT_MAX }, { 114, INT_MAX }, { 115, 10 } };
	w_matrix[113] = m113;
	map<int,int> m114 = { { 110, INT_MAX }, { 111, INT_MAX }, { 112, INT_MAX }, { 113, 20 }, { 114, INT_MAX }, { 115, 60 } };
	w_matrix[114] = m114;
	map<int,int> m115 =   { { 110, INT_MAX }, { 111, INT_MAX }, { 112, INT_MAX }, { 113, INT_MAX }, { 114, INT_MAX }, { 115, INT_MAX } };
	w_matrix[115] = m115;
	//	假设寻找的是v_0与其他点的最短距离
	v_0 = 110;
	//	s、u初始化
	s.insert(S::value_type(110,0));
	u = { 111, 112, 113, 114, 115 };
	//第一次，查找与v_0有连接的所有的点中最近的点
	int pos = w_matrix[110].begin()->first;
	for (auto & item : w_matrix[110])
	{
		if (item.second == INT_MAX)
			continue;
		if (item.second < w_matrix[110][pos])
			pos = item.first;
	}
	//第一次操作完成后s加入找到的路径最短的元素，u则减去这个最短路径的元素
	s[pos]= w_matrix[110][pos];
	u.erase(find(u.begin(), u.end(), pos));
	//核心代码
	pair<int, int > s1(v_0,0);
	while (!u.empty())
	{
		int pre = u.size();
		//从S中寻找最短的单个节点
		s1 = findShortPos(v_0, w_matrix, u, s,s1);
		if (u.size() == pre)//剩下都是v_0到达不了的节点
		{
			for (U::iterator ui = u.begin(); ui != u.end(); )
			{
				s.insert(S::value_type(*ui,INT_MAX));
				ui=u.erase(ui);
			}
		break;
		}
	}
	//展示结果
	for (auto & si : s)
		cout << " 节点 : " << si.first << "到v_o的最短距离 : " << si.second << endl;
}
int main()
{
	Dijkstra();
	system("pause");
	return 0;
}