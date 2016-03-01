
/*
	内部排序：
	
			插入排序、交换排序、选择排序、归并排序、计数排序

	插入排序：

			直接插入排序：
					
					思想：************[i]@！#%^& （假设 从小到大）
					      条件： 当前位置在i，左边是排好的，右边情况是未知的
						  所以我在i处望向左边，如果左边兄弟比我高：兄弟，咱俩换一下，。。。直到左边兄弟没我高，我就动了。
						  然后【i+1】处的兄弟开始向左望。。

					空间:s[0]的哨兵思想挺好，一个辅助交换空间

					时间：O(n^2)

					特点:左边始终是排好的

			 折半插入排序：

					思想：上述左边，是有序的，所以完全可以利用折半查找来实现。没必要一个一个兄弟往左比，在n比较大的时候，效率要比上面高挺多。

					效率：虽然查的快了，但是还要一步一步移过去。所以时间复杂度依旧是O(n)

			希尔排序：
					
					思想：先将整个待排序列分割成若干子序列，子序列分别进行直接插入排序，待整个序列基本有序时，再对
						  全体记录进行一次直接插入排序

					效率：不一样，反正比直排好点

	快速排序：
		
			冒泡排序：

					思想：f(i..){f(j..) 比较：交换}

					效率：时间见复杂度：O(n^2)

					特点：每一趟冒出来一个“最”

			快速排序：

					思想：通过一趟排序将待排记录分成独立的两部分，其中一部分记录的关键字比另一部分的关键字小，则可分别
					对这两部分记录继续进行排序，以达到整个序列有序。
			
					效率：O(nlogn)
					
					特点：排完一次 就会有一个位置被确定



*/
#include <iostream>
#include <vector>

using namespace std;

/*
	low 就是mid
*/
int one_sort(vector<int>& s,int low,int high)
{
	int mid;
	mid = s[low];
	while (low<high)
	{
		while (low < high && s[high] >= mid)high--;//>=
		s[low] = s[high];
		while (low < high && s[low] <= mid)low++;//<=
		s[high] = s[low];
	}
	s[low] = mid;
	return low;
}

void quik_sort(vector<int> & s,int low,int high)
{
	if (low < high)
	{
		int mid = one_sort(s, low,high);//注意参数 不要写成死参 0 s.size() 。。`	
		quik_sort(s, low, mid - 1);
		quik_sort(s, mid + 1, high);
	}
}

int main()
{
	vector<int> num = {2,1,4,5,3,675,54,21,66666};
	int length = num.size() - 1;
	quik_sort(num,0,length);

	for (auto & elem : num)
	{
		cout << elem;
	}
	system("pause");
	return 0;
}

