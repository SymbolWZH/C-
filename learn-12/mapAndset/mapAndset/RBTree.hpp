#pragma once
//��ڶ�����
//����  1.���Ǻڵ�2.û�������ĺ���ڵ�3.ÿ��·��������ͬ�����ĺ�ڽڵ�
//��̵�·����ȫ��O(logN) //���·����2*O(logN)һ��һ�� ���������2��
//��ɾ�Ĳ�ʱ�临�Ӷ���O(logN)
//Ҳ����˵�����϶��ԣ��������Ч�ʱ�AVL���Բ�������أ�Ӳ���������ٶȷǳ��죬����֮���Ѿ�����û�в����ˡ�
#include <iostream>
using namespace std;

enum Colour
{
	BLACK,
	RED,
};

template<class K, class V>
class RBTreeNode {
public:
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	pair<K, V> _kv;
	Colour _color;
	RBTreeNode(const pair<K, V>& kv)
		:_left(nullptr), _right(nullptr), _parent(nullptr), _kv(kv), _color(RED)
	{}
};
template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K,V> Node;

public:
	bool Insert(const pair< K, V>& kv)
	{
		//�Ȱ��������Ĺ�����в���
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_color = BLACK;
			return true;
		}
		//û�еĻ��ʹ���һ����ǰ�ڵ��һ�����ڵ�
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{//���С����Ҫ���뵽�ڵ�͵��ұ�ȥ��
				parent = cur;//parent���뵱ǰ�ڵ���ҵ�����
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{//���������Ҫ���뵽�ڵ�͵����ȥ��
				parent = cur;//parent���뵱ǰ�ڵ���ҵ�����
				cur = cur->_left; 
			}
			else
			{//�����ȱ�ʾ���� ֱ�ӷ���
				return false;
			}
		}
		//ѭ��������ʾ ����ڵ㽻��λ��
		cur = new Node(kv);
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		//������ɫ�ڵ㣺��Ϊ�ڵ�ÿ��·������Ӱ��
		cur->_color = RED;
		//cur��ɺ�ɫ֮��ȥѰ����Խڵ�ĸ��ڵ�uncle
		while (parent && parent->_color == RED)
		{
			//3�������ڵ㣬���ĸ����Ǻ�ɫ�ģ������ƶ������游������һ��Ϊ��ɫ���ؼ������塣
			//a��������������Ϊ�죬 �Ѹ��׺������ڣ��游��죬�������ϴ���
			//2�������ڵ㣬���ĸ����Ǻ�ɫ�ģ�������
			//������������ؼ�������
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_color == RED)
				{//�������ڵ�Ϊ��ɫ�Ҳ�Ϊ�� ���ø��׺������ɺ�ɫ�ڵ�
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					//Ȼ��cur�͵���grandfather���ϼ�������
					cur = grandfather;
					parent = cur->_parent;

				}
				//b��������������Ϊ�ڣ����߲����ڡ� ��ת(���� or ˫��) + ��ɫ
				else//���岻���ڻ����Ǵ�����Ϊ��ɫ
				{//��ת�ӱ�ɫ  ���ַ�ʽ �ȴ���˫������� �����͸��ӷ���
					//1. ���cur�ڸ��׵���߾��ǵ���
					if (parent->_right == cur)
					{
						RotateL(parent);
						swap(parent, cur);
					}
					//2. �п��������������������
					
					RotateR(grandfather);
					grandfather->_color = RED;
					parent->_color = BLACK;

					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				//����Ϊ��
				if (uncle && uncle->_color == RED)
				{//�������ڵ�Ϊ��ɫ�Ҳ�Ϊ�� ���ø��׺������ɺ�ɫ�ڵ�
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					//Ȼ��cur�͵���grandfather���ϼ�������
					cur = grandfather;
					parent = cur->_parent;

				}
				else
				{//����Ϊ�ڻ򲻴���
					if (parent->_left == cur)
					{
						RotateR(parent);
						swap(parent, cur);
					}
					//2. �п��������������������

					RotateL(grandfather);
					grandfather->_color = RED;
					parent->_color = BLACK;

					break;
				}
			}
		}
		_root->_color = BLACK;
		return true;
	}
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;
		//1.ԭ��parent��������ĸ� ����subR�Ǹ�
		//2. parentΪ������ֻ���������е��������ı����ӹ�ϵ ��ôsubRҪ��������λ��
		if (_root = parent)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;

			subR->_parent = ppNode;
		}
	}
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		if (_root == parent)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
			subL->_parent = ppNode;
		}
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}
	void InOrder()
	{
		_InOrder(_root);
	}
	//1.����Ƿ������������������ ��������Ƿ�Ϊ��������
	bool IsVaildRBTree()
	{
		//����Ҳ�Ǻ����
		if (nullptr == _root) return true;
		//�����ڵ��Ƿ��������
		if (BLACK != _root->_color)
		{
			cout << " δ����������ʶ������ڵ����Ϊ��ɫ" << endl;
			return false;
		}
		//��ȡ����һ��·���к�ɫ�ڵ�ĸ���
		size_t blackCount = 0;
		Node* cur = _root;
		while (cur)
		{
			if (BLACK == cur->_color) blackCount++;

			cur = cur->_left;
		}
		size_t k = 0;
		return _IsVaildRBTree(_root, k, blackCount);
	}
	//2.�Ժ�������м��
	bool _IsVaildRBTree(Node* pRoot, size_t k, const size_t blackCount)
	{
		if (nullptr == pRoot)
		{
			if (k != blackCount)
			{
				cout << "Υ�������ģ�ÿ��·���к�ɫ�ڵ�ĸ���������ͬ" << endl;
				return false;
			}
			return true;
		}
		//ͳ�ƺ�ɫ�ڵ�ĸ���
		if (BLACK == pRoot->_color)
			k++;
		//��⵱ǰ�ڵ�����˫���Ƿ�Ϊ��ɫ
		Node* pParent = pRoot->_parent;
		if (pParent && RED == pParent->_color && RED == pRoot->_color)
		{
			cout << "Υ����������û������һ��ĺ�ɫ�ڵ�" << endl;
			return false;
		}

		return _IsVaildRBTree(pRoot->_left, k, blackCount)
			&& _IsVaildRBTree(pRoot->_right, k, blackCount);
	}
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < key)
				cur = cur->_right;
			else if(cur->_kv.first > key)
				cur = cur->_left;
			else
				return cur;
		}
		return nullptr;
	}
private:
	Node* _root = nullptr;
};

void test_RBTree()
{
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7,16,14 };
	RBTree<int, int> t;
	for (auto e : a)
		t.Insert(make_pair(e, e));
	
		t.InOrder();

		cout << t.IsVaildRBTree() << endl;
}