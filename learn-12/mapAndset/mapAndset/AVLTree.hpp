#pragma once
#include <iostream>
using namespace std;
/*
AVLTree����
1.�������Ĺ�����в���
2.����ƽ������
3.��������˲�ƽ�� ��Ҫ������ת����
*/
template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;
	pair<K, V> _kv;
	AVLTreeNode(const pair<K, V>& kv)
		:left(nullptr),right(nullptr),parent(nullptr),_kv(kv),_bf(0)
	{}
};
template<class K, class V>
class AVTree
{
public:
	typedef AVLTreeNode<K, V> Node;

	//����
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}
		
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_kv.first > kv.first)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_kv.first <= kv.first)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return false;
				}
			}
			cur = new Node(kv);
			if (parent-> _kv.first < kv.first)
			{
				parent->_right = cur;
				cur->_parent = parent;
			}
			else
			{
				parent->_left = cur;
				cur->_parent = parent;
			}
			while (parent)
			{
				if (cur == parent->_right)
				{
					parent->_bf++;
				}
				else
				{
					parent->_bf--;
				}
				if (parent->_bf == 0)
				{
					break;
				}
				else if (parent->_bf == 1 || parent->_bf == -1)
				{
					cur = parent;
					parent = parent->_parent;
				}
				else if (parent->_bf == 2 || parent->_bf == -2)
				{
					//��Ҫ��ת����
					if (parent->_bf == 2)
					{
						if (cur->_bf == 1)
						{
							RotateL(parent);
						}
						else if (cur->_bf == -1)
						{

						}
					}
					else if(parent->_bf == -2)
					{
						if (cur->_bf == -1)
						{
							RotateR(parent);
						}
						else if(cur->_bf == 1)
						{

						}
					}
					break;
				}

			}
			return true;
	}
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->left;

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
		parent->_bf = subR->_bf = 0;
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
		subL->_bf = parent->_bf = 0;
	}
private:
	Node* _root;
};
