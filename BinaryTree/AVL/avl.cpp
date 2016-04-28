
/*
	平衡二叉排序树
	资料：严蔚敏 《数据结构》 p233
*/

#include <iostream>
#include <queue>
using namespace std;

class node{
public:
	int val;
	int bf;//结点的平衡因子
	node * lchild;
	node * rchild;
	node(int a) :val(a),bf(0),lchild(nullptr),rchild(nullptr){}
};

/*
	功能：查找元素是否存在
*/

bool searchNode(node * root, int key)
{
	if (!root)
		return false;
	if (root->val == key)
		return true;
	if (root->val < key)
		return searchNode(root->lchild,key);
	return searchNode(root->rchild,key);
}

/*
	功能：左左；向右顺时转
*/

void L_L_rotate(node * & root)
{
	node * lc = root->lchild;
	root->lchild = lc->rchild;
	lc->rchild = root;
	root = lc;
}

/*
	功能：右右;向左逆时转
*/

void R_R_rotate(node * & root)
{
	node * rc = root->rchild;
	root->rchild = rc->lchild;
	rc->lchild = root;
	root = rc;
}

/*
	功能：左右；左子树逆时针转；整体顺时针转
*/

void L_R_rotate(node * & root)
{
	R_R_rotate(root->lchild);
	L_L_rotate(root);
}

/*
	功能：右左；右子树顺时针转；整体逆时针转
*/

void R_L_rotate(node * & root)
{
	L_L_rotate(root->rchild);
	R_R_rotate(root);
}

/*
	功能：调整左子树
	情况1：左左
	情况2：左右
*/

void leftBalance(node * & root)
{
	node * lc = root->lchild;
	switch (lc->bf)
	{
	case 1://左左
		root->bf = 0;
		lc->bf = 0;
		L_L_rotate(root);
		break;
	case -1://左右
		node * rd = lc->rchild;
		//=====================
		switch (rd->bf)//画图容易理解
		{
		case 1:
			root->bf = -1;
			lc->bf = 0;
			rd->bf = 0;
			break;
		case 0:
			root->bf = 0;
			lc->bf = 0;
			rd->bf = 0;
			break;
		case -1:
			root->bf = 0;
			lc->bf = 1;
			rd->bf = 0;
			break;
		}//====================
		L_R_rotate(root);
		break;
	}
}

/*
	功能： 调整右子树
	情况1：右右
	情况2：右左
*/

void rightBalance(node * & root)
{
	node * rc = root->rchild;
	switch (rc->bf)
	{
	case 1://右左；要考虑孙子的状态
	{
		//=====================
		node * ld = rc->lchild;
		switch (ld->bf)
		{
		case 1:
			root->bf = 0;
			ld->bf = 0;
			rc->bf = -1;
			break;
		case 0:
			root->bf = 0;
			ld->bf = 0;
			rc->bf = 0;
			break;
		case -1:
			root->bf = 1;
			ld->bf = 0;
			rc->bf = 0;
			break;
		}
		//=============
		R_L_rotate(root);
	}
		break;
	case -1://右右
		rc->bf = 0;
		root->bf = 0;
		R_R_rotate(root);
		break;
	}
}

/*
	插入元素	
*/

bool insertNode(node * & root, node * elem,bool & taller)
{
	if (!elem)
		return false;
	if (!root)
	{
		root = elem;
		taller = true;
		return true;
	}
	if (root->val == elem->val)//要插入的元素已经存在
	{
		taller = false;
		return false;
	}
	if (elem->val < root->val)//左子树
	{
		if (!insertNode(root->lchild, elem,taller))//插入失败
			return false;
		if (taller)//左子树高度+1
		{
			switch (root->bf)
			{
			case 1 ://左子树本身是1，插入成功后变成2,需要平衡左子树
				leftBalance(root);
				taller = false;
				break;
			case 0:       
				root->bf = 1;
				taller = true;//只有0变1时才是真正增高，画图容易理解
				break;
			case -1:
				root->bf = 0;
				taller = false;
			}
		}
		return true;
	}//左子树
	else//右子树
	{
		if (!insertNode(root->rchild, elem, taller))//插入失败
			return false;
		if (taller)//右子树高度+1
		{
			switch (root->bf)
			{
			case 1:
				root->bf = 0;
				taller = false;
				break;
			case 0:
				root->bf = -1;
				taller = true;//只有在0变-1的时候才是真正增高
				break;
			case -1://本身右子树就高1，现在又高了，需要调整
				rightBalance(root);
				taller = false;
				break;
			}
		}
		return true;
	}
}
/*
*  功能：层次遍历
*/
void showtree(node * root)
{
	cout << "====================show::start==================" << endl;
	queue<node *> q;
	if (!root)
		return;
	q.push(root);
	int current = 1;
	int next = 0;
	while (!q.empty())
	{
		node * temp = q.front();
		if (temp->rchild)
		{
			q.push(temp->rchild);
			next++;
		}
		if (temp->lchild)
		{
			q.push(temp->lchild);
			next++;
		}
		current--;
		if (current == 0)
		{
			current = next;
			next = 0;
			cout << temp->val <<"("<<temp->bf<<")"<< endl;
		}
		else
			cout << temp->val <<"("<<temp->bf<<")"<< " ";
		q.pop();
	}
	cout << "======================show::end====================" << endl;
}
int main()
{
	node * n1 = new node(24);
	node * n2 = new node(13);
	node * n3 = new node(37);
	node * n4 = new node(53);
	node * n5 = new node(90);
	node * root = nullptr;
	bool taller = false;
	insertNode(root,n1,taller);
	insertNode(root,n2,taller);
	insertNode(root,n3,taller);
	insertNode(root,n4,taller);
	insertNode(root,n5,taller);
	showtree(root);
	system("pause");
	return 0;
}