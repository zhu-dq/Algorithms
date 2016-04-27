/*
 * 功能：二叉排序树
 * 参考资料：严蔚敏 《数据结构》 p227
 */

#include <iostream>

using namespace std;

#include <queue>
class node{
public:
    int data;
    node * lchild;
    node * rchild;
    node(int a):data(a),lchild(nullptr),rchild(nullptr){}
};

/*
 *  功能：查找指定节点  找到返回 true  找不到 返回 false
 *  root :要查找的树的根节点
 *  key : 要查找的值
 *  f : p所指向元素的双亲节点
 *  p : 遍历的当前节点
 */
bool SearchBST(node *  root,int key,node * & f,node * & p)
{
    if(!root)
    {
        p = f;
        return false;
    }
    if(root->data==key)
    {
        p = root;
        return true;
    }
    if(key<root->data)
    {
        return SearchBST(root->lchild,key,root,p);
    }
    return SearchBST(root->rchild,key,root,p);
}

/*
 * 功能： 插入node节点
 */
bool InsertBST(node *  root,node *  elem)
{
    node *p = nullptr;
    node *f = nullptr;
    if(SearchBST(root,elem->data, f,p))
                return false;
    if(!p)
    {
        root = elem ;
        return true;
    }
    if(elem->data<p->data)
        p->lchild = elem;
    else
        p->rchild = elem;
    return true;
}
/*
 * 功能：删除某个节点
 * 论引用的重要性！！！
 */
bool deleteNode(node * & root,int key)
{
    if(!root)
        return false;

    if(key<root->data)
        return deleteNode(root->lchild,key);

    if(key>root->data)
        return deleteNode(root->rchild,key);

    if(!root->lchild && !root->rchild)//叶子节点
    {
        delete root;
        root = nullptr;
        return true;
    }

    if(!root->lchild || !root->rchild)//只有左子树或只有右子树
    {
        node * p = root;
        if(root->lchild)//只有左子树
            root= root->lchild;
        else            //只有右子树
            root=root->rchild;
        delete p;
        return true;
    }
    //左子树和右子树都存在
    node * parent = root;
    node * prev = root->lchild;
    while (prev->rchild)
    {
        parent = prev;
        prev=prev->rchild;

    }
    root->data = prev->data;
    //prev 没有右孩子
    if(parent==root)//特殊情况：前趋必须是root的左侧
        parent->lchild = prev->lchild;
    else//一般情况：前趋是左子树的最右
        parent->rchild = prev->lchild;
    delete prev;
    return true;
}
/*
 *  功能：层次遍历
 */
void showtree(node * root)
{
    cout<<"====================show::start=================="<<endl;
    queue<node *> q;
    if(!root)
        return ;
    q.push(root);
    int current = 1;
    int next = 0;
    while   (!q.empty())
    {
        node * temp = q.front();
        if(temp->rchild)
        {
            q.push(temp->rchild);
            next++;
        }
        if(temp->lchild)
        {
            q.push(temp->lchild);
            next++;
        }
        current--;
        if(current==0)
        {
            current=next;
            next=0;
            cout<<temp->data<<endl;
        }
        else
            cout<<temp->data<<" ";
        q.pop();
    }
    cout<<"======================show::end===================="<<endl;
}
/*
 * 功能：删除整棵树
 */
void deleteTree(node * & root)
{
    if(!root)
        return;
    queue<node *> q;
    q.push(root);
    root = nullptr;
    while (!q.empty())
    {
        node * temp = q.front();
        if(temp->lchild)
            q.push(temp->lchild);
        if(temp->rchild)
            q.push(temp->rchild);
        q.pop();
        delete temp;
    }
}
int main()
{
    node * n1 = new node(12);
    node * n2 = new node(24);
    node * n3 = new node(45);
    node * n4 = new node(53);
    node * n5 = new node(90);

    n3->lchild = n2;
    n3->rchild = n4;
    n2->lchild = n1;
    n4 ->rchild =n5;

    //=============test SearchBST========================
    node * p= nullptr;
    node * f = nullptr;
    bool result = SearchBST(n3,90, f,p);
    //cout<<result<<endl;
    //cout<<p->data<<endl;
    //==============test end=============================

    //=============test InsertBST========================
    node * n_0 = new node(15);
    bool result1 = SearchBST(n3,n_0->data, f,p);
    bool result2 = InsertBST(n3,n_0);
    bool result3 = SearchBST(n3,n_0->data,f,p);
    //cout<<result1<<endl;
    //cout<<result2<<endl;
    //cout<<result3<<endl;
    //=============test end==============================


    //=============test Delete===========================
    showtree(n3);
    deleteNode(n3,45);
    showtree(n3);
    deleteTree(n3);
    showtree(n3);
    //=============test end==============================
    return 0;
}