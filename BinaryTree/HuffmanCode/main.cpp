
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

template  <class  T>
class node{
public:
    node(T a, float b):data(a),weight(b),lchild(NULL),rchild(NULL),isleaf(true){}
    node(T a, float b,shared_ptr<node<T>> c,shared_ptr<node<T>> d,bool e):data(a),weight(b),lchild(c),rchild(d),isleaf(false){}
    T data;
    vector<int> code;
    float  weight;
    shared_ptr<node<T>> lchild;
    shared_ptr<node<T>> rchild;
    bool  isleaf;
};
bool  sort_func(const shared_ptr<node<int>> a,const shared_ptr<node<int>> b)
{
    return a->weight<b->weight;
}
shared_ptr<node<int>> creatHuffmanTree(vector<shared_ptr<node<int>>> & v)
{
    if(v.size()==1)
        return v[0];

    sort(v.begin(),v.end(),sort_func);

    //auto iter1 = v.begin();
    //auto iter2 = next(iter1+1);
    //v.push_back(shared_ptr<node<int>>(new node<int>(0,(*iter1)->weight+(*iter2)->weight,*iter1,*iter2, false)));
    v.push_back(shared_ptr<node<int>>(new node<int>(0,v[0]->weight+v[1]->weight,v[0],v[1],false)));
    v.erase(v.erase(v.begin()));

    creatHuffmanTree(v);
}
void showcode(const vector<int> & code)
{
    for(auto & item : code)
        cout<<item<<" ";
}
shared_ptr<node<int>> creatHUffmanCode(shared_ptr<node<int>> root,vector<int> v_code)
{
    if(!root)
        return root;
    if(root->isleaf)
    {
        root->code = v_code;
        //root->code.assign(v_code.begin(),v_code.end());
        //root->code.swap(v_code);
        cout<<"data : "<<root->data<<"weight : "<<root->weight<<"code : ";
        showcode(root->code);
        cout<<endl;
        return root;
    }

    vector<int> v_l_code = v_code;
    v_l_code.push_back(0);
    creatHUffmanCode(root->lchild,v_l_code);
    vector<int> v_r_code = v_code;
    v_r_code.push_back(1);
    creatHUffmanCode(root->rchild,v_r_code);

}
int main() {
    cout<<"please input data weight (ending:-1 -1)"<<endl;
    vector<shared_ptr<node<int>>> v;
    while (true)
    {
        int data = 0;
         float weight= 0.0;
        cin>>data>>weight;
        if(data==-1)
            break;
        v.push_back(shared_ptr<node<int>>(new node<int>(data,weight)));
    }
    if(v.empty())
        return 0;
    vector<int> v_code;
    shared_ptr<node<int>> root = creatHuffmanTree(v);
    creatHUffmanCode(v[0],v_code);

    return 0;
}