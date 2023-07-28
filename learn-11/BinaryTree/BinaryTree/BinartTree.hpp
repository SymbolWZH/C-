#pragma once
//1.�麯����
//->����:�麯����д�Ƕ�̬������֮һ
//->��̬ԭ��:�麯����ַ�ŵ���������(�麯����)�У���ָ̬��˭���ñ��������е�����
//�����Ҫ���õ��麯����
//2.��̳У�
//->����:������μ̳��е���������Ͷ�����
//->ԭ�� : ����������ŵ�����λ��(vs�Ƿŵ���������β��)��������д�ƫ������������
//���������λ�á�
//�ܽ� : ��ס���������ط�����virtual�ؼ��֣�����֮��û��һ���������Ҫ��ϵ��һ��

/*
������������ʹ�ü�ֵ ���� ���������ĸ߶ȴ�
1��������
2��������������������������Ľڵ�ȸ�С���������ڵ�ȸ��ڵ��
*/

#include <iostream>
using namespace std;

// �����������ڵ�
template <class K, class V>
struct BSTreeNode
{
	BSTreeNode<K,V>* _left;
	BSTreeNode<K, V>* _right;
	K _key;
	V _val;

	BSTreeNode(K key = K(), V val = V())
		: _left(nullptr)
		, _right(nullptr)
		, _key(key)
		, _val(val)
	{}

};

// ����������ģ��ʵ��
template <class K, class V>
class BSTree
{
public:
	typedef BSTreeNode<K, V> node;

	// ���캯��
	BSTree()
		: _root(new node())
	{}

	// �������� bs2��bs1��������������������������~~~
	BSTree(const BSTree<K, V>& tree)
	{
		_root = _copyTree(tree._root);
	}

	// ��ֵ��������أ��ִ�д���� bs2 = bs1
	BSTree<K, V>& operator=(const BSTree<K, V> tree)
	{
		std::swap(_root, tree._root);
		return *this;
	}

	// ��������
	~BSTree()
	{
		_Destroy(_root);
		_root = nullptr;
	}
	//����Ԫ��
	bool Insert(const K& key, const V& val)
	{
		// �����ĿǰΪ��
		if (nullptr == _root)
		{
			_root = new node(key, val);
			return true;
		}

		// �������Ϊ�գ��Ӹ���㿪ʼ�Һ��ʵ�λ�ã����ƻ������������Ľṹ��
		// �Ҳ������ʵ�λ�ã������ʧ��
		node* par = nullptr;
		node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				par = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				par = cur;
				cur = cur->_right;
			}
			else
			{
				// �����������ֵͬ���
				return false;
			}
		}

		node* newnode = new node(key);
		if (par->_key > key)
		{
			par->_left = newnode;
			return true;
		}
		else
		{
			par->_right = newnode;
			return true;
		}
	}
	//����Ԫ��
	bool Find(const K& key)
	{
		if (nullptr == _root)
		{
			return false;
		}

		node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else if (cur->_key > key)
			{
				cur = cur->_right;
			}
			else
			{
				return true;
			}
		}

		return false;
	}
	// �����ⳡ�����òſ���д��������ȷ+��ͼ��������������������
	bool Earse(const K& key)
	{
		if (nullptr == _root)
		{
			return false;
		}

		node* par = nullptr;
		node* cur = _root;
		while (cur)
		{
			if (key < cur->_key)
			{
				par = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				par = cur;
				cur = cur->_right;
			}
			else
			{
				// �ҵ���ɾ���

				//if (nullptr == cur->_left && nullptr != cur->_right) // Ҷ�ӽ����Թ鲢Ϊ����յ����
				if (nullptr == cur->_left)
				{
					// ��ɾ�����Ϊ��

					// �����ɾ���Ϊ����㣬�Ҹ������Ϊ��
					if (nullptr == par)
					{
						_root = cur->_right;
					}
					else
					{
						if (cur == par->_left)
						{
							par->_left = cur->_right;
						}
						else
						{
							par->_right = cur->_right;
						}
					}
					delete cur;
				}
				else if (nullptr == cur->_right)
				{
					// ��ɾ�����Ϊ��

					// �����ɾ���Ϊ����㣬�Ҹ������Ϊ��
					if (nullptr == par)
					{
						_root = cur->_left;
					}
					else
					{
						if (cur == par->_left)
						{
							par->_left = cur->_left;
						}
						else
						{
							par->_right = cur->_left;
						}
					}
					delete cur;
				}
				else
				{
					// ��ɾ�ڵ����Ҷ���Ϊ�գ�ʹ���滻��

					// 1-�Ҵ�ɾ�������������С��㣨�������㣩���滻

					// ���ܸ�ֵnullptr����Ϊ����ɾ����������ͼ�ṹ�ĸ���㣡������������������������
					// 3 
					//2 4
					node* maxpar = cur;
					node* maxcur = cur->_right;
					while (maxcur->_left)
					{
						maxpar = maxcur;
						maxcur = maxcur->_left;
					}

					std::swap(cur->_key, maxcur->_key); // ���ǽ�������ֵ

					// maxcur����������Ϊ�գ�������������ȷ��
					// ����ͳһ����maxcur��������������maxpar��maxcur���Ӧ��һ��
					if (maxcur == maxpar->_right)
					{
						maxpar->_right = maxcur->_right;
					}

					if (maxcur == maxpar->_left)
					{
						maxpar->_left = maxcur->_right;
					}

					delete maxcur;

					// 2-�Ҵ�ɾ�������������������滻(ͬ��)
				}

				return true;
			}
		}

		return false;
	}
	void swap(node* left, node* right)
	{
		std::swap(left->_key, right->_key);
		std::swap(left->_val, right->_val);
	}
	// �������
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	// ��������Ӻ�����Ȩ��Ϊprivate��
	void _InOrder(node* root)
	{
		if (nullptr == root)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_key << "::" << root->_val << " ";
		_InOrder(root->_right);
	}
	// ����
	void _Destroy(node* root)
	{
		if (nullptr == root)
		{
			return;
		}

		// ��������
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root; // ���ú��ÿ�
	}
	// ������
	node* _copyTree(node* root)
	{
		if (nullptr == root)
		{
			return nullptr;
		}

		// �������������
		// ǰ�򿽱�
		node* newnode = new node(root->_key, root->_val);
		newnode->_left = _copyTree(root->_left);
		newnode->_right = _copyTree(root->_right);

		return newnode;
	}

private:
	node* _root;
};

void testBSTree()
{
	BSTree<int,int> t;
	int a[] = { 5,3,4,1,7,8,2,6,0,9 };

	for (auto e : a)
	{
		t.Insert(e,e);
	}
	t.InOrder();
	t.Earse(2);
	t.InOrder();
	t.Earse(5);
	t.InOrder();
	t.Earse(1);
	t.InOrder();
	t.Earse(3);
	t.InOrder();
	t.Earse(4);
	t.InOrder();
	t.Earse(6);
	t.InOrder();
	t.Earse(7);
	t.InOrder();
	t.Earse(8);
	t.InOrder();
	t.Earse(9);
	t.InOrder();
	t.Earse(0);
	t.InOrder();
}