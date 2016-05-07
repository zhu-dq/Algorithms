/*
	功能：归并排序
	资料：严蔚敏 《数据结构》 p284
*/
#include <iostream>
#include <vector>
using namespace std;

/*
 *功能：将SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]
 */
void merge(vector<int> SR,vector<int> & TR,int i,int m,int n)
{
    int j=m+1;
    int k=i;
    for(;i<=m&&j<=n;++k)
        (SR[i]<SR[j])?TR[k]=SR[i++]:TR[k]=SR[j++];
    while (i<=m)
        TR[k++]=SR[i++];
    while (j<=n)
        TR[k++]=SR[j++];
}

void showV(vector<int> v)
{
    for(auto & item:v)
        cout<<item<<" ";
    cout << endl;
}

/*
 *功能：将SR[s..m]范围的元素二分归并到TR中
 */

void MSort(vector<int> SR,vector<int> & TR,int s,int t)
{
    if(s==t)
        return;
    int mid = (s+t)/2;//将SR均分成两半
    MSort(SR,TR,s,mid);//SR[s..mid]归并为有序的TR[s..mid]
    MSort(SR,TR,mid+1,t);//SR[mid+1..t]归并为有序的TR[mid+1..t]
    merge(TR,TR,s,mid,t);//将TR[s..m]和TR[mid+1..t]归并到TR[s,t]
}

int main() {
    vector<int> v = {7,2,5,1,9};
    MSort(v,v,0,4);
    showV(v);
    return 0;
}
