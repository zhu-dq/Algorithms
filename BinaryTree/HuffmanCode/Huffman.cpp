/*
 * 功能：huffman编码
 * 参考资料：严蔚敏 《数据结构》 p145
 */
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
using namespace std;
/*
 * 元素的结构体
 */
template  <class  T>
class node{
public:
    node(T a, float b):data(a),weight(b),lchild(NULL),rchild(NULL),isleaf(true){}
    node(T a, float b,shared_ptr<node<T>> c,shared_ptr<node<T>> d,bool e):data(a),weight(b),lchild(c),rchild(d),isleaf(false){}
    T data;
    string code;
    float  weight;
    shared_ptr<node<T>> lchild;
    shared_ptr<node<T>> rchild;
    bool  isleaf;
};
/*
 *辅助排序函数
 */
bool  sort_func(const shared_ptr<node<int>> a,const shared_ptr<node<int>> b)
{
    return a->weight<b->weight;
}
/*
 *创建huffman树
 */
shared_ptr<node<int>>  creatHuffmanTree(vector<shared_ptr<node<int>>> & v,int pos)
{
    //将权重最低的两个元素作为新元素的左右孩子节点，并将新元素插入到的正确位置（从低到高）
    while (v.size()-pos !=1)
    {
        shared_ptr<node<int>> unleaf_node(new node<int>(0,v[0+pos]->weight+v[1+pos]->weight,v[0+pos],v[1+pos],false));
        auto iter = v.begin()+pos;
        for(;iter!=v.end();++iter)
        {
            if(unleaf_node->weight>(*iter)->weight)
                continue;
            v.insert(iter,unleaf_node);
            break;
        }
        if(iter ==v.end())
            v.insert(v.end(),unleaf_node);
        pos+=2;
    }
    return *prev(v.end());
}
/*
 *编码展示的辅助函数
 */
void showcode(string & code)
{
    for(auto & item : code)
        cout<<item<<" ";
}
/*
 *创建huffman编码
 */
void creatHUffmanCode(shared_ptr<node<int>> root,string v_code)
{
    if(!root)
        return;
    if(root->isleaf)
    {
        root->code = v_code;
        cout<<" data : "<<root->data<<" weight : "<<root->weight<<" code : ";
        showcode(root->code);
        cout<<endl;
        return;
    }

    creatHUffmanCode(root->lchild,v_code+"0");
    creatHUffmanCode(root->rchild,v_code+"1");

}
int main() {
    vector<shared_ptr<node<int>>> v;
    while (true)
    {
        int data = 0;
         float weight= 0.0;
        cout<<"please input data weight (ending:-1 -1)"<<endl;
        cin>>data>>weight;
        if(data==-1)
            break;
        v.push_back(shared_ptr<node<int>>(new node<int>(data,weight)));
    }
    if(v.empty())
        return 0;
    sort(v.begin(),v.end(),sort_func);
    shared_ptr<node<int>> root  = creatHuffmanTree(v,0);
    string v_code;
    creatHUffmanCode(root,v_code);
    return 0;
}