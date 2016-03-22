/*
	笔试题：
	为一个大小为N的数组排序  找到第K个数的大小 K从0开始  要求用快排
	测试用例：
		1 0  1位的数组  K为0
		100
		5 2	  5位的数组	K为2
		2
		10
		35
		41
		37
		0 0  N=0表示结束
*/

#include <iostream>
using namespace std;

int qsort_once(int *array, std::size_t size)
{
	int low = 0;
	int seq_value = array[low];//low位置空了

	int high = size - 1;

	while (low < high)
	{
		while (low < high && seq_value < array[high])high--;
		//high seq_value 只能忘低处搬家 低处只有low指向的位置有空，so(因为low刚搬过家)
		array[low] = array[high];
		while (low<high && seq_value>array[low])low++;
		//尼玛low太高了  需要往高出搬家  高出只有high指向的位置是空了（因为high刚搬过家）
		array[high] = array[low];
	}
	array[low] = seq_value;
	return low;
}


// 01234
int kth(int *array, std::size_t size_t1, int k)
{
	if (k>size_t1 - 1)
		k = size_t1 - 1;
	int re = qsort_once(array, size_t1);
	if (re == (k))
	{
		return array[k];
	}
	else if ((k)<re)
	{
		return kth(array, re, k);
	}
	else
	{
		return kth(array + re + 1, size_t1 - re - 1, k - re - 1);
	}
}

int main()
{
	int K = 0, N = 0;
	while (cin>>N>>K)
	{
		if (N == 0)
			break;
		int * array_ = (int*)malloc(sizeof(int)*N);
		int i = 0;
		int v = 0;
		while (cin>>v)
		{
			array_[i] = v;
			i++;
			if (i == N)
				break;
		}
		int result = kth(array_,N,K);
		cout << "结果是："<<result << endl;
		free(array_);
	}

	//system("pause");
	return 0;
}