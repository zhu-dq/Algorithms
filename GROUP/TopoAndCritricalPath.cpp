/*
	�����޻�ͼ֮�ؼ�·��  //Ŀǰ��bug
*/
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <cassert>
#include <algorithm>
using namespace std;

//��
class Edge{
public:
	Edge(int j, int t) :head(j), time(t){}
	int time;
	int head;
};

//����
class VNode{
public:
	VNode(){}
	VNode(int i, int degree = 0) :nodeid(i), indegree(degree),ve(0),vl(0){}
	int nodeid;
	int indegree;
	int ve;//���翪ʼʱ��
	int vl;//����ʼʱ��
};

//��������
vector<int> TopoSort(map<int, VNode>  index_v , map<int, vector<Edge> >  table)
{
	//init s
	stack<int> s;
	vector<int> result;
	for (int i = 0; i < index_v.size(); ++i)
	{
		if (index_v[i].indegree == 0)
		{
			s.push(index_v[i].nodeid);
		}
	}//init complete

	while (!s.empty())
	{
	if (s.empty())
		return result;
	int delete_nameid = s.top();
	for (int i = 0; i < table[delete_nameid].size(); ++i)
	{
		int head_id = table[delete_nameid][i].head;
		if (--index_v[head_id].indegree == 0)
			s.push(head_id);
	}
	result.push_back(delete_nameid);
	index_v.erase(delete_nameid);
	table.erase(delete_nameid);

	}//while

	return result;
}

void buildVE(map<int, VNode> & index_v , map<int, vector<Edge> > & table,const vector<int> & vsort)
{
	for (int i = 0; i < vsort.size(); ++i)//��������
	{
		int nodeid = vsort[i];
		for (int j = 0; j < table[nodeid].size(); ++j)//������nodeidΪβ�ı�
		{
			Edge e = table[nodeid][j]; //��
			int temp_time = e.time + index_v[nodeid].ve;
			if (temp_time > index_v[e.head].ve)
				index_v[e.head].ve = temp_time;
		}
	}
}		

void buildVL(map<int, VNode> & index_v , map<int, vector<Edge> > & table,const vector<int> & vsort)
{
	//init vl
	int init_value = index_v[vsort[vsort.size()]].ve;
	for (int i = 0; i < index_v.size() - 1; ++i)
		index_v[i].vl = init_value;
	for (int i = vsort.size() - 2; i >= 0; --i)//����������
	{
		int nodeid = vsort[i];
		for (int j = 0; j < table[nodeid].size(); ++j)//������nodeidΪβ�ı�
		{
			Edge e = table[nodeid][j]; //��
			int temp_time = index_v[nodeid].vl-e.time;
			if (temp_time < index_v[e.head].vl)
				index_v[nodeid].vl = temp_time;
		}
	}
}

vector<int> getCriticalPath(map<int, VNode> & index_v)
{
	vector<int> result;
	for (auto & e : index_v)
	{
		if (e.second.vl = e.second.ve)
			result.push_back(e.first);
	}
	return result;
}
void dumpResult(const vector<int> & result)
{
	for (int i = 0; i < result.size(); ++i)
	{
		cout << result[i];
		if (1 != result.size() - 1)
			cout << "->";
		else
		{
			cout << "\n";
		}
	}
}
int main()
{
	map<int, VNode> v_temp;//����VNodeInfo
	map<int, vector<Edge> > ljTable;//�ڽӱ�
	//init ljTable
	cout << "����������ߵĸ���" << endl;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cout << "�������" << i + 1 << "���� : i j t" << endl;
		int tail, head, time;
		cin >>tail>>head>>time;
		if (!v_temp.count(tail))
		{
			VNode v(tail);
			v_temp[tail] = v;
		}
		if (!v_temp.count(head))
		{
			VNode v(head,1);
			v_temp[head] = v;
		}
		else
		{
			v_temp[head].indegree++;
		} 
		Edge e(head,time);
		ljTable[tail].push_back(e);
	}//init complete

	vector<int> vsort = TopoSort(v_temp,ljTable);
	assert(vsort.size()==v_temp.size());
	buildVE(v_temp,ljTable,vsort);
	buildVL(v_temp,ljTable,vsort);
	vector<int> result = getCriticalPath(v_temp);
	dumpResult(result);
	return 0;
}