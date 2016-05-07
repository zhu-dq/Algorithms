#include <iostream>
#include <vector>
using namespace std;
/*
 * 相关知识：
 *
 * 完全二叉树性质：
 *   假设元素下标是[1,n]
 *   root  下标是1
 *   parent(i) = [i/2](下限)   (i>1)
 *   lchild(i) = 2i            (2i<=n)
 *   rchild(i) = 2i+1          (2i+1<=n)
 *   深度：[log(2(xia) n(shang))](下限)+1
 *   非叶结点：1----[n/2](下限)
 */
/*
 *功能：调整堆
 */

void heapAdjust(vector<int> & v_heap,int pos,int n)
{
    int data = v_heap[pos];                         //pos  : current parent
    while ( 2*pos <= n )//存在孩子
    {
        int flag = 2*pos;//lchild
        if(flag<n && v_heap[flag]<v_heap[flag+1])   //flag = max(lchild,rchild)
            flag++;
        if(data>=v_heap[flag])//符合大顶堆
            break;
        v_heap[pos] = v_heap[flag];

        pos = flag;//调整以孩子为根节点的大顶堆
    }
    v_heap[pos] = data;
}

/*
 *功能：初始化堆
 */

void heapSort(vector<int> & v_heap)
{
    /*
     *  从 n/2 到 1  调整所有结点
     */

    int n = v_heap.size()-1;        //v_heap[0]弃用
    for(size_t i = n/2;i>0;i--)//最后一个非叶子结点
        heapAdjust(v_heap,i,n);

    for(size_t i = n;i>0;i--)
    {
        cout<<v_heap[1]<<" ";//输出当前最大值
        swap(v_heap[1],v_heap[i]);//删除当前最大值
        heapAdjust(v_heap,1,i-1);//调整大顶堆
    }
}

int main()
{
    vector<int> v = {-1,49,38,65,97,76,13,27,49};
    heapSort(v);
    return 0;
}