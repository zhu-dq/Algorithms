#include <iostream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

//定义结构体
struct Node
{
	int data;
	Node * lchild;
	Node * rchild;
};

struct endNode
{
	Node * node;
	bool  isFirst;
};

//========================三种递归遍历=============================

//前序遍历
void preOrder(Node * root)
{
	if (!root)
		return;
	cout << root->data << endl;
	preOrder(root->lchild);
	preOrder(root->rchild);
}

//中序遍历
void midOrder(Node * root)
{
	if (!root)
		return;
	midOrder(root->lchild);
	cout << root->data << endl;
	midOrder(root->rchild);
}

//后序遍历
void endOrder(Node * root)
{
	endOrder(root->lchild);
	endOrder(root->rchild);
	cout << root->data << endl;
}

//=============================end===============================


//========================三种非递归遍历=============================

//前序遍历
void preOrderUnRecursion(Node * root)
{
	stack<Node *> s;
	Node * p = root;
	while (!s.empty() || p!=NULL)
	{
		//case 1   p!=NULL
		while (p!=NULL)//左走入栈  ,此while循环即控制左走也负责输出
		{
			cout << p->data << endl;
			s.push(p);
			p = p->lchild;
		}

		//case 2 !s.empty()
		if (!s.empty())//右走出栈
		{
			p = s.top();
			s.pop();
			p = p->rchild;
		}

	}
}

//中序遍历
void midOrderUnRecursion(Node * root)
{
	stack<Node *> s;
	Node * p = root;
	while (!s.empty() || p!=NULL)
	{
		//case 1  p!=NULL
		while (p!=NULL)//左走入栈
		{
			s.push(p);
			p = p->lchild;
		}

		//case 2 !s.empty()
		if (!s.empty())//右走出栈
		{
			p = s.top();
			cout << p->data << endl;
			s.pop();
			p = p->rchild;
		}
	}
}

//后序遍历
void endOrderUnRecursion(Node * root)
{
	stack<endNode> s;
	Node * p = root;
	while (!s.empty() || p != NULL)
	{
		//case 1 : p!=NULL
		while (p!=NULL)//左走入栈
		{
			endNode temp;
			temp.node = p;
			temp.isFirst = true;
			s.push(temp);
			p = p->lchild;
		}

		//case 2 : !s.empty()
		if (!s.empty())//右走出栈
		{
			endNode temp = s.top();
			s.pop();
			if (temp.isFirst)//第一次出现在栈顶
			{
				temp.isFirst = false;
				s.push(temp);
				p = temp.node->rchild;
			}
			else
			{
				cout << temp.node->data << endl;
				p = NULL;
			}
		}
	}
}
void createTree(Node * root, vector<int> datas)
{
	if (datas.empty())
		return;
	Node * temp = new Node;
	temp->data = datas[0];
	temp->lchild = temp->rchild = NULL;
	root = temp;
	queue<Node *> q;
	q.push(temp);
	for (vector<int>::iterator iter = datas.begin() + 1; iter != datas.end(); ++iter)
	{
		temp = new Node;
		temp->data = *iter;
		temp->lchild = temp->rchild = NULL;
		Node * n = q.front();
		while (n->lchild && n->rchild)
		{
			q.pop();
			n = q.front();
		}
		if (!n->lchild)
			n->lchild = temp;
		else
			n->rchild = temp;
		q.push(temp);
	}
}

void showTree(Node * root)
{
	if (!root)
		return;
	queue<Node *> q;
	q.push(root);
	while (!q.empty())
	{
		Node * temp = q.front();
		q.pop();
		cout << temp->data << endl;
		if (!temp->lchild)
			q.push(temp->lchild);
		if (!temp->rchild)
			q.push(temp->rchild);
	}
}

//============================end=================================
//other ref : http://blog.csdn.net/fansongy/article/details/6798278

int main(int argc,char *argv[])
{
	return 0;
}