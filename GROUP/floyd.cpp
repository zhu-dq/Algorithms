/*
	功能：弗洛伊德算法
	思路：
		http://ahalei.blog.51cto.com/4767671/1383613
*/

#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

#define MATRIX unordered_map<int,unordered_map<int,int>>

 

int main()
{
	MATRIX city_distance;
	set<int> city_items;
	cout << "please input city1 city2 distance (ending: -1 -1 -1)" << endl;
	int city1 = -1;
	int city2 = -1;
	int distance = -1;

	while (cin>>city1>>city2>>distance)
	{
		if (city1 == -1)
			break;
		city_distance[city1][city2] = distance ;
		city_items.insert(city1);
		city_items.insert(city2);
		cout << "please input city1 city2 distance (ending: -1 -1 -1)" << endl;
	}

	for (auto & city_k : city_items)
	{
		for (auto & city_a : city_items)
		{
			for (auto & city_b : city_items)
			{
				int a_0_k_b = city_distance[city_a][city_k] + city_distance[city_k][city_b];
				if (a_0_k_b < city_distance[city_a][city_b])
					city_distance[city_a][city_b] = a_0_k_b;
			}
		}
	}

	//show distance
	for (auto & item : city_items)
		cout << "\t" << item;
	cout << endl;
	for (auto & a : city_items)
	{
		cout << a;
		for (auto & b : city_items)
		{
			cout << "\t" << city_distance[a][b];
		}
		cout << endl;
	}

	system("pause");

	return 0;
}