#pragma once
//1.虚函数，
//->概念:虚函数重写是多态的条件之一
//->多态原理:虚函数地址放到对象的虚表(虚函数表)中，多态指向谁调用本质是运行到对象
//虚表找要调用的虚函数。
//2.虚继承，
//->概念:解决菱形继承中的数据冗余和二义性
//->原理 : 将虚基类对象放到公共位置(vs是放到整个对象尾部)，虚基表中存偏移量，来计算
//虚基类对象的位置。
//总结 : 记住这里两个地方都用virtual关键字，他们之间没有一点关联，不要联系到一起。

/*
搜索二叉树：使用价值 搜索 最多查找数的高度次
1、二叉树
2、树本身和子树都满足左子树的节点比根小，右子树节点比根节点大
*/

#include <iostream>
using namespace std;

// 搜索二叉树节点
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

// 搜索二叉树模拟实现
template <class K, class V>
class BSTree
{
public:
	typedef BSTreeNode<K, V> node;

	// 构造函数
	BSTree()
		: _root(new node())
	{}

	// 拷贝构造 bs2（bs1）！！！！！！！！！！忘记~~~
	BSTree(const BSTree<K, V>& tree)
	{
		_root = _copyTree(tree._root);
	}

	// 赋值运算符重载（现代写法） bs2 = bs1
	BSTree<K, V>& operator=(const BSTree<K, V> tree)
	{
		std::swap(_root, tree._root);
		return *this;
	}

	// 析构函数
	~BSTree()
	{
		_Destroy(_root);
		_root = nullptr;
	}
	//插入元素
	bool Insert(const K& key, const V& val)
	{
		// 如果树目前为空
		if (nullptr == _root)
		{
			_root = new node(key, val);
			return true;
		}

		// 如果树不为空，从根结点开始找合适的位置（不破环搜索二叉树的结构）
		// 找不到合适的位置，则插入失败
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
				// 不允许插入相同值结点
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
	//查找元素
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
	// 用特殊场景套用才可以写出完整正确+画图！！！！！！！！！！
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
				// 找到待删结点

				//if (nullptr == cur->_left && nullptr != cur->_right) // 叶子结点可以归并为单侧空的情况
				if (nullptr == cur->_left)
				{
					// 待删结点左为空

					// 如果待删结点为根结点，且根结点左为空
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
					// 待删结点右为空

					// 如果待删结点为根结点，且根结点右为空
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
					// 待删节点左右都不为空，使用替换法

					// 1-找待删结点右子树的最小结点（即最左结点）来替换

					// 不能赋值nullptr，因为可能删的是类似下图结构的根结点！！！！！！！！！！！！！
					// 3 
					//2 4
					node* maxpar = cur;
					node* maxcur = cur->_right;
					while (maxcur->_left)
					{
						maxpar = maxcur;
						maxcur = maxcur->_left;
					}

					std::swap(cur->_key, maxcur->_key); // 仅是交换结点的值

					// maxcur的左子树必为空，但是右子树不确定
					// 所以统一处理将maxcur的右子树链接在maxpar和maxcur相对应的一边
					if (maxcur == maxpar->_right)
					{
						maxpar->_right = maxcur->_right;
					}

					if (maxcur == maxpar->_left)
					{
						maxpar->_left = maxcur->_right;
					}

					delete maxcur;

					// 2-找待删结点左子树的最大结点来替换(同理)
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
	// 中序遍历
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	// 中序遍历子函数（权限为private）
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
	// 销毁
	void _Destroy(node* root)
	{
		if (nullptr == root)
		{
			return;
		}

		// 后序销毁
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root; // 调用后置空
	}
	// 拷贝树
	node* _copyTree(node* root)
	{
		if (nullptr == root)
		{
			return nullptr;
		}

		// 深拷贝，否则会出错
		// 前序拷贝
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