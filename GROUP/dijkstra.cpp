/*
ѧϰ�Ͻ�˹�����㷨
INT_MAX ��ʾ������
���������´�Ȩ�ڽӾ���
����ʦ ���ݽṹ  P189

����㷨����һ���۵�֧�ֵģ�����
����S����������·�����յ�ļ��ϣ���
��һ�����·����vi�����������������֮һ��
1. v0-vi
2. v0-S-vi

����Ҫ���ˣ��п��ܴ���һ���� vj��vj������S��  v0-vj-vi ����������ҪС
�𣺲����ܣ�����㷨�ȵľ����ĸ������̣��Ҿ�����˭����Ȼv0-vj ��v0-vj-viҪ�̣��������Ѿ��ڿ���vi�ˣ�˵��vj�Ѿ��������˰�
*/
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
#define WEIGHTMATRIX map<int,map<int,int>>
#define S map<int,int> 
#define U vector<int>

//int findShortPos(int v_0, WEIGHTMATRIX & w_matrix, U & u, S & s)//�Ż�
pair<int, int> findShortPos(int v_0, WEIGHTMATRIX & w_matrix, U & u, S & s, pair< int, int> si)//�Ż�
{
	int pos = 0;
	int value = INT_MAX;
	/*
		Ϊʲô���Բ��ñ�������Ϊ�����ظ��Ͷ�������
		�����ܹ������ڵ㣺s1��s2��s3
		��һ�Σ� s = {s1}
		v0-ui �ľ���  v1-s1-ui�������ȫ������,����֪��v0-s2���
		�ڶ��Σ� s = {s1,s2}
		v0-ui �ľ���  v1-s1-ui�������ȫ������  (������������ظ��Ͷ���,��Ϊv1-s1-ui���Ѿ����ǹ��˰���v1-s1-ui�ľ����ֲ����)
		v0-ui �ľ���   v1-s2-ui�������ȫ������
		
		���ԣ����˿��ܻ���:v0-ui �ľ���Ҳ���ǹ��ˣ�Ϊʲô��Ҫ���¡�����Ϊv0-ui�ľ���ÿ�ζ����ܻᱻ�ı䰡������
	*/
	//for (auto & si : s)//s�д�ĵ�  �Ż�    //��Ϊ�����۵��֧��
	//{                     //�Ż�
		for (auto & ui : w_matrix[si.first])//��si�����ӵĵ�
		{
			if (s.count(ui.first))//�Ѿ�����s����
				continue;
			if (ui.second == INT_MAX) //s1��uiû������
				continue;
			if (ui.second + si.second < w_matrix[v_0][ui.first])//����w_matrix[v_0][ui]
				w_matrix[v_0][ui.first] = ui.second + si.second;
			if (ui.second + si.second < value)//Ѱ�Ҿ�����v_0��̵�
			{
				value = w_matrix[v_0][ui.first];
				pos = ui.first;
			}
		}
	//}  //�Ż�
	if (value == INT_MAX)
		return pair<int,int>(-1,-1);
	s.insert(S::value_type(pos, w_matrix[v_0][pos]));
	u.erase(find(u.begin(), u.end(), pos));
	return pair<int, int>(pos,value);
}

/*
�����㷨
v_0:����v_0�����������̾���
S ���Ѿ��ҵ�����̾���ĵ�ļ���
U ��û�ҵ�����̾���ĵ�ļ���
*/
void Dijkstra()
{
	int v_0;
	S  s;
	U  u;
	//��ʼ�����ݽṹ
	WEIGHTMATRIX w_matrix;
	/*
	��ʼ����Ȩ�ڽӾ���
	���� V0--V5 ��ÿ��idΪ 110-INT_MAX15
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
	//	����Ѱ�ҵ���v_0�����������̾���
	v_0 = 110;
	//	s��u��ʼ��
	s.insert(S::value_type(110,0));
	u = { 111, 112, 113, 114, 115 };
	//��һ�Σ�������v_0�����ӵ����еĵ�������ĵ�
	int pos = w_matrix[110].begin()->first;
	for (auto & item : w_matrix[110])
	{
		if (item.second == INT_MAX)
			continue;
		if (item.second < w_matrix[110][pos])
			pos = item.first;
	}
	//��һ�β�����ɺ�s�����ҵ���·����̵�Ԫ�أ�u���ȥ������·����Ԫ��
	s[pos]= w_matrix[110][pos];
	u.erase(find(u.begin(), u.end(), pos));
	//���Ĵ���
	pair<int, int > s1(v_0,0);
	while (!u.empty())
	{
		int pre = u.size();
		//��S��Ѱ����̵ĵ����ڵ�
		s1 = findShortPos(v_0, w_matrix, u, s,s1);
		if (u.size() == pre)//ʣ�¶���v_0���ﲻ�˵Ľڵ�
		{
			for (U::iterator ui = u.begin(); ui != u.end(); )
			{
				s.insert(S::value_type(*ui,INT_MAX));
				ui=u.erase(ui);
			}
		break;
		}
	}
	//չʾ���
	for (auto & si : s)
		cout << " �ڵ� : " << si.first << "��v_o����̾��� : " << si.second << endl;
}
int main()
{
	Dijkstra();
	system("pause");
	return 0;
}