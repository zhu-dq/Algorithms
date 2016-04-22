/*
	��̬�滮  ��������
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Item{
public:
	Item(int a, int b) :weight(a), value(b){}
	 int weight;
	 int value;
};

int main()
{
	int n = 0;
	int max_pac = 0;
	cout << "��������Ʒ����" << endl;
	cin >> n;
	cout << "�����뱳������" << endl;
	cin >> max_pac;
	vector<Item> v_item;
	for (int i = 0; i < n; ++i)
	{
		int w = 0;
		int v = 0;
		cout << "�������"<<i<<"����Ʒ����Ϣ �� w  v" << endl;
		cin >> w >> v;
		v_item.push_back(Item(w,v));
	}
	//init
	vector<int> v_init(max_pac+1,0);
	vector<vector<int>> dp_table(n+1,v_init);
	//creat dptable
	/*
		d(i,j):ǰi����Ʒװ�����Ϊj�İ�������ֵ��
					 |-- d(i-1,j)                                         ��i����Ʒ��װ��
		d(i,j) = max |
					 |-- d(i-1,j-v_item[i-1].weight)+v_item[i-1].value	  ��i����Ʒװ��
	*/			

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j < max_pac + 1; ++j)
		{
			if ((j - v_item[i - 1].weight) >= 0)
			{
				dp_table[i][j] = max(dp_table[i - 1][j], dp_table[i - 1][j - v_item[i - 1].weight] + v_item[i - 1].value);
			}
			else
			{
				dp_table[i][j] = dp_table[i-1][j];
			}
		}
	}

	//����·��
	vector<bool> opt(n,false);
	int max_now = max_pac;
	for (int i = 1; i < n + 1; ++i)
	{
		if (dp_table[i][max_now] != dp_table[i - 1][max_now])//��i����Ʒװ��
		{
			opt[i - 1] = true;
			max_now = max_now - v_item[i - 1].weight;
		}
	}

	cout << "ѡ�����Ʒ�ǣ�";
	for (int i = 0; i < n; ++i)
	{
		if (opt[i])
			cout << " " << i + 1;
	}
	cout << endl;
	system("pause");
	return 0;
}