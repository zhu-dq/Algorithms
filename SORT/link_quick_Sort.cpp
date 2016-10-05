/*
 * 链表的快排
 */
#include <iostream>
#include <algorithm>
using namespace std;

class Node{
    public:
        int val;
        Node * next;
        Node(int data):val(data){}
};

Node * once_sort(Node * LBegin,Node * LEnd)
{
    int key = LBegin->val;
    Node * p = LBegin;
    Node * q = LBegin->next;
    while(q!=LEnd)
    {
        if(q->val < key)
        {
            p = p->next;
            std::swap(p->val,q->val);
        }
        q = q->next;
    }
    std::swap(p->val,LBegin->val);
    return p;
}

void QuickSort(Node * LBegin,Node * LEnd)
{
    if(LBegin != LEnd)
    {
        Node * mid = once_sort(LBegin,LEnd);
        once_sort(LBegin,mid);
        once_sort(mid->next,LEnd);
    }
}
