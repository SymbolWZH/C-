#pragma once
//红黑二叉树
//定义  1.根是黑的2.没有连续的红军节点3.每条路径都有相同数量的红黑节点
//最短的路径：全黑O(logN) //最长的路径：2*O(logN)一黑一红 所以最多是2倍
//增删改查时间复杂度是O(logN)
//也就是说理论上而言，红黑树的效率比AVL树略差但是现在呢，硬件的运算速度非常快，他们之间已经基本没有差异了。
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
		//先按搜索树的规则进行插入
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_color = BLACK;
			return true;
		}
		//没有的话就创建一个当前节点和一个父节点
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{//如果小于需要插入到节点就到右边去找
				parent = cur;//parent存入当前节点好找到父亲
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{//如果大于需要插入到节点就到左边去找
				parent = cur;//parent存入当前节点好找到父亲
				cur = cur->_left; 
			}
			else
			{//如果相等表示存在 直接返回
				return false;
			}
		}
		//循环结束表示 插入节点交换位置
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
		//新增红色节点：因为黑的每条路径都会影响
		cur->_color = RED;
		//cur变成红色之后去寻找相对节点的父节点uncle
		while (parent && parent->_color == RED)
		{
			//3、插入红节点，他的父亲是红色的，可以推断他的祖父存在且一定为黑色。关键看叔叔。
			//a、如果叔叔存在且为红， 把父亲和叔叔变黑，祖父变红，继续往上处理。
			//2、插入红节点，他的父亲是黑色的，结束。
			//红黑树的条件关键看叔叔
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_color == RED)
				{//如果叔叔节点为红色且不为空 就让父亲和叔叔变成红色节点
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					//然后cur就等于grandfather向上继续查找
					cur = grandfather;
					parent = cur->_parent;

				}
				//b、如果叔叔存在且为黑，或者不存在。 旋转(单旋 or 双旋) + 变色
				else//叔叔不存在或者是存在且为黑色
				{//旋转加变色  两种方式 先处理双旋的情况 单旋就更加方便
					//1. 如果cur在父亲的左边就是单旋
					if (parent->_right == cur)
					{
						RotateL(parent);
						swap(parent, cur);
					}
					//2. 有可能是上面的情况变过来的
					
					RotateR(grandfather);
					grandfather->_color = RED;
					parent->_color = BLACK;

					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				//存在为红
				if (uncle && uncle->_color == RED)
				{//如果叔叔节点为红色且不为空 就让父亲和叔叔变成红色节点
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					//然后cur就等于grandfather向上继续查找
					cur = grandfather;
					parent = cur->_parent;

				}
				else
				{//存在为黑或不存在
					if (parent->_left == cur)
					{
						RotateR(parent);
						swap(parent, cur);
					}
					//2. 有可能是上面的情况变过来的

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
		//1.原来parent是这棵树的根 现在subR是根
		//2. parent为根的树只是整棵树中的子树，改变链接关系 那么subR要顶替他的位置
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
	//1.检测是否满足二叉树的搜索树 中序遍历是否为有序序列
	bool IsVaildRBTree()
	{
		//空树也是红黑树
		if (nullptr == _root) return true;
		//检测根节点是否满足情况
		if (BLACK != _root->_color)
		{
			cout << " 未返红黑树性质二：根节点必须为黑色" << endl;
			return false;
		}
		//获取任意一条路径中黑色节点的个数
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
	//2.对红黑树进行检查
	bool _IsVaildRBTree(Node* pRoot, size_t k, const size_t blackCount)
	{
		if (nullptr == pRoot)
		{
			if (k != blackCount)
			{
				cout << "违反性质四：每条路径中黑色节点的个数必须相同" << endl;
				return false;
			}
			return true;
		}
		//统计黑色节点的个数
		if (BLACK == pRoot->_color)
			k++;
		//检测当前节点与其双亲是否都为红色
		Node* pParent = pRoot->_parent;
		if (pParent && RED == pParent->_color && RED == pRoot->_color)
		{
			cout << "违反性质三：没有连在一起的红色节点" << endl;
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