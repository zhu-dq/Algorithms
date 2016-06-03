/*
	功能：kmp字符串匹配算法
	参考资料:
	   严蔚敏 《数据结构》 p82 p83
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
功能：构建next数组
str:模式串
v_next:next数组; next[i] = k,menas pattern's i pos elem not equal source_str elem ,patterns from k pos compare.
*/
void getnext(const string & str, vector<int> & v_next)
{
	//init 
	int i = 0;
	int j = -1;
	v_next[i] = j;
	while (i<v_next.size()-1)
	{
		if (j == -1)//第一个元素匹配就失败;下一个元素从头(0)开始匹配
		{
			i++;
			j++;
			v_next[i] = j;
			continue;
		}
		// next[i] = j,对于j来讲，p1p2..pj-1 = pi-j+1pi-j+2..pi-1;
		// 又 str[i] == str[j]  所以：next[i+1] = j+1;
		if (str[i] == str[j])
		{
			i++;
			j++;
			v_next[i] = j;
			continue;
		}
		//当前前缀不匹配，寻找更小的前缀。
		j = v_next[j];
	}
}

int func_kmp(const string & source_str, const string & patterns)
{
	if (patterns.empty())
		return 0;
	if (source_str.empty() || source_str.size()<patterns.size())
		return -1;
	vector<int> v_next(patterns.size(),-1);
	getnext(patterns, v_next);
	int i = 0, j = 0;
	int s_size = source_str.size();
	int p_size = patterns.size();
	while (j<p_size && i<s_size)
	{
		if (j==-1)
		{
			j++;
			i++;
			continue;
		}
		if (patterns[j] == source_str[i])
		{
			j++;
			i++;
			continue;
		}
		j = v_next[j];

	}
	if (j == patterns.size())
		return i - patterns.size();
	return -1;
}

int main()
{
	string str1("woshishaoling");
	string str2("shao");
	//func_kmp(str1,str2);
	cout << func_kmp(str1, str2) << endl;
	system("pause");
	return 0;
}