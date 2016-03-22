/*
	�����⣺
	Ϊһ����СΪN����������  �ҵ���K�����Ĵ�С K��0��ʼ  Ҫ���ÿ���
	����������
		1 0  1λ������  KΪ0
		100
		5 2	  5λ������	KΪ2
		2
		10
		35
		41
		37
		0 0  N=0��ʾ����
*/

#include <iostream>
using namespace std;

int qsort_once(int *array, std::size_t size)
{
	int low = 0;
	int seq_value = array[low];//lowλ�ÿ���

	int high = size - 1;

	while (low < high)
	{
		while (low < high && seq_value < array[high])high--;
		//high seq_value ֻ�����ʹ���� �ʹ�ֻ��lowָ���λ���пգ�so(��Ϊlow�հ����)
		array[low] = array[high];
		while (low<high && seq_value>array[low])low++;
		//����low̫����  ��Ҫ���߳����  �߳�ֻ��highָ���λ���ǿ��ˣ���Ϊhigh�հ���ң�
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
		cout << "����ǣ�"<<result << endl;
		free(array_);
	}

	//system("pause");
	return 0;
}