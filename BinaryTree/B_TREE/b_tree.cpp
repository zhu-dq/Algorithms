/*
 * 功能：实现B-(B)树
 * 资料：严蔚敏 《数据结构》
 */
#include <iostream>
#include <vector>
#include <queue>
#define N 3
using namespace std;

class node
{
public:
    int n;
    node * parent;
    vector<int> keys;
    vector<node *> childs;
    node(int m):n(m),parent(nullptr){}
    node(int m ,node * pare):n(m),parent(pare){}
};

/*
 *功能：分裂结点
 */

void splitNode(node * & root,node * q)
{
    bool finished = false;
    //q 0
    node * node_rth = nullptr;//1
    int node_location;//2
    int node_key;//3
    while (q && !finished)
    {
        int mid = q->keys.size()/2;
        node_key = q->keys[mid];
        //右
        node_rth = new node(q->n,q->parent);                //1
        node_rth->childs.assign(q->childs.begin()+mid+1,q->childs.end());
        node_rth->keys.assign(q->keys.begin()+mid+1,q->keys.end());
        for(auto & item : node_rth->childs)//孩子换双亲啦
        {
            if(item!= nullptr)
                item->parent = node_rth;
        }
        //左
        vector<node *> temp_c(q->childs.begin(),q->childs.begin()+mid+1);
        vector<int> temp_k(q->keys.begin(),q->keys.begin()+mid);
        q->childs= temp_c;
        q->keys = temp_k;
        q = q->parent;                                      //0
        if(q)
        {
            int i =0;
            while(i<q->keys.size() && node_key>q->keys[i])i++;
            node_location = i;                                   //2

            //insert
            q->keys.insert(q->keys.begin()+node_location,node_key);
            q->childs.insert(q->childs.begin()+node_location+1,node_rth);

            if(q->keys.size()<q->n)
                finished = true;
        }
    }

    if(!finished)//添加新的根节点
    {
        node * node_root = new node(N);
        node_root->keys.push_back(node_key);
        root->parent = node_root;
        node_rth->parent = node_root;
        node_root->childs.push_back(root);
        node_root->childs.push_back(node_rth);
        root = node_root;
    }
}

/*
 *  功能：插入新结点
 *  root  根节点
 *  key   要插入的值
 *  q    要插入的结点
 *  i    插入结点位置
 */

void insertEndNode(node * & root,int key,node * q,int i)
{
    //insert
    q->keys.insert(q->keys.begin()+i,key);
    q->childs.insert(q->childs.begin()+i+1, nullptr);

    if(q->keys.size()<q->n)
        return;
    else
        return splitNode(root,q);
}
/*
 * 功能：插入元素
 */
void insertNode(node * & root,node * current_node,int key)//主要作用是查找插入点
{
    if(!root)
    {
        node * n=new node(N);
        n->keys.push_back(key);
        n->childs.push_back(nullptr);
        n->childs.push_back(nullptr);
        return;
    }
    int pos =0;
    while (pos<current_node->keys.size()&&key>current_node->keys[pos])pos++;
    if(pos<current_node->keys.size()&&key==current_node->keys[pos])
        return;
    if(!current_node->childs[pos])//最底层
        return insertEndNode(root,key,current_node,pos);//核心插入函数
    else
        return insertNode(root,current_node->childs[pos],key);
}
/*
 * 功能：打印树
 */

void showBTree(node * root)
{
    if(!root)
        return;
    queue<node*> q;
    q.push(root);
    while (!q.empty())
    {
        node * n = q.front();
        q.pop();
        for(auto & item :n->keys)
            cout<<item<<" ";
        cout<<endl;
        for(auto & item : n->childs)
        {
            if(item!= nullptr)
                q.push(item);
        }
    }
}

/*
 * 功能：找前驱
 * q 当前结点
 * i 当前key值位置
 */

pair<node *,int> findPrev(node * q,int i)
{
    if(q->childs[i-1])
    {
        node * end_node = q->childs[i-1];
        while (*prev(end_node->childs.end()))
            end_node = *prev(end_node->childs.end());
        return pair<node *,int>(end_node,end_node->keys.size()-1);
    }
    return pair<node *,int>(q,i);
}

/*
 * 功能：找后继
 * q  当前结点  指针
 * i  当前key值位置
 */

pair<node *,int> findNext(node * q,int i)
{
    //找后继结点,
    if(q->childs[i+1])
    {
        node * end_node = q->childs[i+1];
        while (end_node->childs[0])
            end_node=end_node->childs[0];
        return pair<node *,int>(end_node,0);
    }
    //q就是最低层
    return pair<node *,int>(q,i);
}

/*
 * 功能：找左右兄弟结点
 */

bool findLandR(node * q,int & pos,node * & lth,node * & rth)
{
    if(!q->parent)
        return false;
    pos=0;
    for(;pos<q->parent->childs.size();++pos)
        if(q==q->parent->childs[pos])
            break;
    if(pos==q->parent->childs.size())
        return false;
    pos>0?lth = q->parent->childs[pos-1]:lth= nullptr;
    pos<(q->parent->childs.size()-1)?rth = q->parent->childs[pos+1]:rth = nullptr;
    return true;
}

/*
 *  合并结点
 *  flag  true:rth  false : lth
 */

 void mergeNode(node * & root,node * q,node * th,int key_pos,int c_pos,int p_c_pos,bool flag)
{
    // 删除相应值
    q->keys.erase(q->keys.begin()+key_pos);
    q->childs.erase(q->childs.begin()+c_pos);

    if(q==root)
    {
        if(q->keys.empty())
            root=q->childs[0];
        return ;
    }

    int mid = (q->n+1)/2;
    if(q->keys.size()>=mid-1)
        return ;

    vector<int> temp_k;
    vector<node *> temp_c;
    int temp_pos;
    if(flag)
    {
        //keys
        temp_k = q->keys;//左
        temp_k.push_back(q->parent->keys[p_c_pos]);//上
        temp_k.insert(temp_k.end(),th->keys.begin(),th->keys.end());//右
        //childs
        temp_c=q->childs;//左
        temp_c.insert(temp_c.end(),th->childs.begin(),th->childs.end());//右
        //pos
        temp_pos = p_c_pos;
        c_pos = p_c_pos;
    }
    else
    {
        //keys
        temp_k = th->keys;//左
        temp_k.push_back(q->parent->keys[p_c_pos-1]);//上
        temp_k.insert(temp_k.end(),q->keys.begin(),q->keys.end());//右
        //childs
        temp_c=th->childs;//左
        temp_c.insert(temp_c.end(),q->childs.begin(),q->childs.end());//右
        //pos
        temp_pos=p_c_pos-1;
        c_pos = p_c_pos;
    }

    th->keys.assign(temp_k.begin(),temp_k.end());
    th->childs.assign(temp_c.begin(),temp_c.end());
    for(auto & item : th->childs)//“过继”
    {
        if(item!= nullptr)
            item->parent = th;
    }

    if(th->keys.size()==th->n)
        splitNode(root,th);
    delete q;
    q = nullptr;

    int pos = -1;
    node * lth = nullptr;
    node * rth = nullptr;
    findLandR(th->parent,pos,lth,rth);
    if(rth)
        return mergeNode(root,th->parent,rth,temp_pos,c_pos,pos,true);
    if(lth)
        return mergeNode(root,th->parent,lth,temp_pos, c_pos,pos,false);
    mergeNode(root,th->parent, nullptr,temp_pos,c_pos,-1, false);//只有root,th->parent,temp_pos,c_pos信息有效
}

/*
 *  功能：删除结点;删除;三种情况
 *  root  根节点
 *  q    要删除的结点
 *  i    删除结点位置
 */

void deleteEndNode(node * & root,node * q,int i)
{
    int mid = (q->n+1)/2;
    if(q->keys.size()>=mid || q->parent == nullptr)//情况1
    {
            q->keys.erase(q->keys.begin()+i);
            q->childs.erase(q->childs.begin()+i);
            if(q->parent== nullptr && q->keys.empty())
                root = *q->childs.begin();
            return;
    }
    int pos =0;
    node * lth = nullptr;
    node * rth = nullptr;
    findLandR(q,pos,lth,rth);
    //找到左右邻居
    if(rth && rth->keys.size()>=mid)//右邻居位置多
    {
            //current node
            q->keys.erase(q->keys.begin()+i);
            q->childs.erase(q->childs.begin()+i);
            q->keys.push_back(q->parent->keys[pos]);
            q->childs.push_back(nullptr);
            //parent node
            q->parent->keys[pos]=rth->keys[0];
            //rth node
            rth->keys.erase(rth->keys.begin());
            rth->childs.erase(rth->childs.begin());
            return ;
    }
    if(lth && lth->keys.size()>=mid)//左邻居位置多
    {
            //current node
            q->keys.erase(q->keys.begin()+i);
            q->childs.erase(q->childs.begin()+i);
            q->keys.push_back(q->parent->keys[pos-1]);
            q->childs.push_back(nullptr);
            //parent node
            q->parent->keys[pos-1]=*prev(lth->keys.end());
            //lth node
            lth->keys.erase(prev(lth->keys.end()));
            lth->childs.erase(prev(lth->childs.end()));
            return ;
    }
    if(rth)//和右邻居合并
       return mergeNode(root,q,rth,i,i,pos,true);

    if(lth)//和左邻居合并
        return mergeNode(root,q,lth,i,i+1,pos,false);

    mergeNode(root,q, nullptr,i,i,-1, false);//只有root,q,i信息有效
}

/*
 *  功能：删除key
 */

void deleteNode(node * & root,int key)
{
    if(!root)
        return;
    node * current_node = root;
    int current_location = 0;
    while (true)
    {
        auto i =0;
        while (i<current_node->keys.size() && key>current_node->keys[i])i++;//找key值位置或与key后继子树
        if(i<current_node->keys.size() && key==current_node->keys[i])////找到啦key值
        {
            current_location = i;
            break;
        }
        current_node = current_node->childs[i];//后继子树
        if(!current_node)//找到底啦 没找到key值
            return;
    }
    pair<node *,int> temp = findNext(current_node,current_location);//找最底层结点
    current_node->keys[current_location] = temp.first->keys[temp.second];//交换值
    deleteEndNode(root,temp.first,temp.second);//删除最底层结点
}

int main()
{
    node * root = new node(N);
    root->keys.push_back(45);
    root->childs.push_back(nullptr);
    root->childs.push_back(nullptr);
    insertNode(root,root,24);
    insertNode(root,root,53);
    insertNode(root,root,90);
    insertNode(root,root,3);
    insertNode(root,root,37);
    insertNode(root,root,50);
    insertNode(root,root,61);
    insertNode(root,root,70);
    insertNode(root,root,100);
    showBTree(root);
    cout<<"delete...."<<endl;
    deleteNode(root,45);
    deleteNode(root,24);
    deleteNode(root,53);
    deleteNode(root,90);
    deleteNode(root,3);
    deleteNode(root,37);
    deleteNode(root,50);
    deleteNode(root,61);
    deleteNode(root,70);
    deleteNode(root,100);
    showBTree(root);
    return 0;
}