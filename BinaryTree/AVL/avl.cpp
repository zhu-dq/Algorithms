
/*
	ƽ�����������
*/

#include <iostream>
#include <queue>
#include <string>
using namespace std;

class node{
public:
	int val;
	int bf;//����ƽ������
	node * lchild;
	node * rchild;
	node(int a) :val(a),bf(0),lchild(nullptr),rchild(nullptr){}
};

/*
	���ܣ�����Ԫ���Ƿ����
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
	���ܣ���������˳ʱת
*/

void L_L_rotate(node * & root)
{
	node * lc = root->lchild;
	root->lchild = lc->rchild;
	lc->rchild = root;
	root = lc;
}

/*
	���ܣ�����;������ʱת
*/

void R_R_rotate(node * & root)
{
	node * rc = root->rchild;
	root->rchild = rc->lchild;
	rc->lchild = root;
	root = rc;
}

/*
	���ܣ����ң���������ʱ��ת������˳ʱ��ת
*/

void L_R_rotate(node * & root)
{
	R_R_rotate(root->lchild);
	L_L_rotate(root);
}

/*
	���ܣ�����������˳ʱ��ת��������ʱ��ת
*/

void R_L_rotate(node * & root)
{
	L_L_rotate(root->rchild);
	R_R_rotate(root);
}

/*
	���ܣ��������������
	���1������
	���2������
*/

void insertLeftBalance(node * & root)
{
	node * lc = root->lchild;
	switch (lc->bf)
	{
	case 1://����
		root->bf = 0;
		lc->bf = 0;
		L_L_rotate(root);
		break;
	case -1://����
		node * rd = lc->rchild;
		//=====================
		switch (rd->bf)//��ͼ�������
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
	���ܣ� �������������
	���1������
	���2������
*/

void insertRightBalance(node * & root)
{
	node * rc = root->rchild;
	switch (rc->bf)
	{
	case 1://����Ҫ�������ӵ�״̬
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
		//====================
		R_L_rotate(root);
	}
		break;
	case 0:
		rc->bf = 1;
		root->bf = -1;
		R_R_rotate(root);
		break;
	case -1://����
		rc->bf = 0;
		root->bf = 0;
		R_R_rotate(root);
		break;
	}
}
/*
	���ܣ� ɾ������������;������̫��
*/
void deleteLeftBalance(node * & root)
{
	node * lc = root->lchild;
	switch (lc->bf)
	{
	case 1:
		lc->bf = 0;
		root->bf = 0;
		L_L_rotate(root);
		break;
	case 0:
		lc->bf = -1;
		root->bf = 1;
		L_L_rotate(root);
		break;
	case -1:
	{
		node * rd = lc->rchild;
		switch (rd->bf)
		{
		case 1:
			rd->bf = 0;
			lc->bf = -1;
			root->bf = -1;
			L_R_rotate(root);
			break;
		case 0:
			rd->bf = 0;
			lc->bf = 0;
			root->bf = 0;
			L_R_rotate(root);
			break;
		case -1:
			rd->bf = 0;
			lc->bf = 1;
			root->bf = 0;
			L_R_rotate(root);
			break;
		}
	}

		break;
	}
}

/*
	���ܣ�ɾ��������������������̫��
*/

void deleteRightBalance(node * & root)
{
	node * rc = root->rchild;
	switch (rc->bf)
	{
	case 1://����
	{
		node * ld = rc->lchild;
		//=============================
		switch (ld->bf)
		{
		case 1:
			ld->bf = 0;
			root->bf = 0;
			rc->bf = -1;
			R_L_rotate(root);
			break;
		case 0:
			ld->bf = 0;
			root->bf = 0;
			rc->bf = 0;
			R_L_rotate(root);
			break;
		case -1:
			ld->bf = 0;
			root->bf = 1;
			rc->bf = 1;
			R_L_rotate(root);
			break;
		}
		//============================
	}

		break;
	case 0://����
		rc->bf = 1;
		root->bf = -1;
		R_R_rotate(root);
		break;
	case -1://����
		rc->bf = 0;
		root->bf = 0;
		R_R_rotate(root);
		break;
	}
}

/*
	����Ԫ��	
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
	if (root->val == elem->val)//Ҫ�����Ԫ���Ѿ�����
	{
		taller = false;
		return false;
	}
	if (elem->val < root->val)//������
	{
		if (!insertNode(root->lchild, elem,taller))//����ʧ��
			return false;
		if (taller)//�������߶�+1
		{
			switch (root->bf)
			{
			case 1 ://������������1������ɹ�����2,��Ҫƽ��������
				//leftBalance(root);
				insertLeftBalance(root);
				taller = false;
				break;
			case 0:       
				root->bf = 1;
				taller = true;//ֻ��0��1ʱ�����������ߣ���ͼ�������
				break;
			case -1:
				root->bf = 0;
				taller = false;
			}
		}
		return true;
	}//������
	else//������
	{
		if (!insertNode(root->rchild, elem, taller))//����ʧ��
			return false;
		if (taller)//�������߶�+1
		{
			switch (root->bf)
			{
			case 1:
				root->bf = 0;
				taller = false;
				break;
			case 0:
				root->bf = -1;
				taller = true;//ֻ����0��-1��ʱ�������������
				break;
			case -1://�����������͸�1�������ָ��ˣ���Ҫ����
				//rightBalance(root);
				insertRightBalance(root);
				taller = false;
				break;
			}
		}
		return true;
	}
}
/*
	���ܣ�ɾ��һ�����
*/
bool deleteNode(node * & root,int key,bool & lesser)
{
	if (!root)
		return false;
	if (key < root->val)//������
	{
		if (!deleteNode(root->lchild, key, lesser))//ɾ��ʧ��
			return false;
		if (lesser)//�������߶ȣ�1
		{
			//do something
			switch (root->bf)
			{
			case 1:
				root->bf = 0;
				lesser = true;
				break;
			case 0:
				root->bf = -1;
				lesser = false;
				break;
			case -1://��Ҫ����
				//rightBalance(root);//���������ĸ߶ȿ϶����
				deleteRightBalance(root);
				lesser = true;
				break;
			}
		}
		return true;
	}
	if(key > root->val)//������
	{
		if (!deleteNode(root->rchild, key, lesser))//ɾ��ʧ��
			return false;
		if (lesser)//�������߶�-1
		{
			//do something
			switch (root->bf)
			{
			case 1:
				//leftBalance(root);
				deleteLeftBalance(root);
				lesser = true;
				break;
			case 0:
				root->bf = 1;
				lesser = false;
				break;
			case -1:
				root->bf = 0;
				lesser = true;
				break;
			}
		}
		return true;
	}

	//ɾ������
	if (!root->lchild && !root->rchild)//Ҷ�ӽ��
	{
		delete root;
		root = nullptr;
		lesser = true;
		return true;
	}
	if (!root->lchild || !root->rchild)//ֻ����������������
	{
		node * p = root;
		if (root->lchild)
			root = root->lchild;
		else
			root = root->rchild;
		delete p;
		lesser = true;
		return true;
	}
	//��������������������
	node * parent = root;
	node * prev = root->lchild;
	while (prev->rchild)
	{
		parent = prev;
		prev = prev->rchild;
	}
	//prev û��������
	root->val = prev->val;
	if (parent == root)//�������
		parent->lchild = prev->lchild;
	else
		parent->rchild = prev->lchild;
	delete prev;
	lesser = true;
	return true;
}
/*
*  ���ܣ���α���
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
		if (temp->lchild)
		{
			q.push(temp->lchild);
			next++;
		}
		if (temp->rchild)
		{
			q.push(temp->rchild);
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

//==========================================================================
void output_impl(node* n, bool left, string const& indent)
{
	if (n->rchild)
	{
		output_impl(n->rchild, false, indent + (left ? "|     " : "      "));
	}
	cout << indent;
	cout << (left ? "\\" : "/");
	cout << "-----";
	cout << n->val << "("<<n->bf<<")"<<endl;
	if (n->lchild)
	{
		output_impl(n->lchild, true, indent + (left ? "      " : "|     "));
	}
}

void output(node* root)
{
	if (!root)
		return;
	if (root->rchild)
	{
		output_impl(root->rchild, false, "");
	}
	cout << root->val <<"("<<root->bf<<")"<< endl;
	if (root->lchild)
	{
		output_impl(root->lchild, true, "");
	}
}
//=============================================================================

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
	//showtree(root);
	bool lesser = false;
	deleteNode(root,13,lesser);
	deleteNode(root,24,lesser);
	deleteNode(root,37,lesser);
	//deleteNode(root,53,lesser);
	//deleteNode(root,90,lesser);
	output(root);
	system("pause");
	return 0;
}