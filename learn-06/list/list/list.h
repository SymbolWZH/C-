#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

namespace zh
{
	template <class T>
	struct list_node
	{
		list_node<T>* _prev;
		list_node<T>* _next;
		T _val;

		list_node(const T& val = T()) 
//const T& val == 0 --> 如果是string类型 --> const T& val = T() --> T()任意类型的默认构造(int(), string(), char()...)
			:_prev(nullptr)
			, _next(nullptr)
			, _val(val)
		{}

	};

	//class list_node //使用class修饰类名会封装节点成员变量，不允许被访问
	//{
	//	list_node<T>* _prev;
	//	list_node<T>* _next;
	//	T _val;

	//	list_node(const T& val) //T()针对自定义类型(如:string)
	//		:_prev(nullptr)
	//		, _next(nullptr)
	//		, _val(val)
	//	{}
	//};

	template <class T, class reference, class pointer>
	struct list_iterator //指针行为(并不是指针) --> 通过内部成员变量_node来完成相对应的操作
	{
		typedef list_node<T> node;
		typedef list_iterator<T, reference, pointer> self;

		node* _node; //成员变量

		list_iterator(node* node) //为什么需要? --> begin()和end()中需要返回节点 --> 需要构造返回
			:_node(node) 
//为什么list_node类中没有写拷贝构造(深拷贝)?
//同样string类中实现就需要深拷贝呢？
//--> node->_prev和node->_next都是指向的32比特位的值,只需进行浅拷贝即可 
		{}

		reference operator*()
		{
			return _node->_val; //const是否修饰
		}

		pointer operator->()
		{
			return &_node->_val; //const是否修饰
		}

		//++it --> it:list_iterator<T>* --> self
		self& operator++() //前置++
		{
			_node = _node->_next;
			return *this; //return list_iterator<T>(_guard->_next); --> node* --> list_node<T>* | *this --> list_iterator<T>
		}

		self operator++(int) //返回值不能使用引用返回 --> 局部变量tmp出了作用域会销毁
		{
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		self& operator--() //前置--
		{
			_node = _node->_prev;
			return *this;
		}

		self operator--(int) //后置--：返回值不能使用引用返回 --> 局部变量tmp出了作用域会销毁
		{
			self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}

		bool operator!=(const self& s)
		{
			return _node != s._node;
		}

		bool operator==(const self& s)
		{
			return _node == s._node;
		}

	};


	template <class T>
	class list
	{
		typedef list_node<T> node;

	public:
		//typedef node* iterator; //err --> 常见:typedef char* iterator --> 对于连续空间存储 --> list是链式结构不是连续空间 --> err
		//iterator begin()
		//	return _guard->_next;
		//iterator end()
		//	return _guard;
		typedef list_iterator<T, T&, T*> iterator;
		//这里const_iterator直接复用iterator可以吗?可以，但是代码冗余, 因为只是对节点val是否更改的决策？ --> 解决方法:类模板多一个参数reference来表示是否是const类型
		typedef list_iterator<T, const T&, const T*> const_iterator;


		iterator begin()
		{
			return iterator(_guard->_next);
		}

		iterator end()
		{
			return iterator(_guard);
		}

		const_iterator begin() const
		{
			return const_iterator(_guard->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_guard);
		}

		list()//构造函数初始化
		{
			_guard = new node;
			_guard->_next = _guard;
			_guard->_prev = _guard;
		}

		template <class Iterator>
		list(Iterator first, Iterator last) //迭代器实现构造
		{
			_guard = new node;
			_guard->_next = _guard;
			_guard->_prev = _guard;
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		list(const list<T>& lt)
		{
			_guard = new node;
			_guard->_next = _guard;
			_guard->_prev = _guard;
			list<T> tmp(lt.begin(), lt.end());
			swap(tmp);
		}

		//void push_back(const T& val)
		//{
		//	node* tail = _guard->_prev;
		//	node* new_node = new node(val);
		//	tail->_next = new_node;
		//	new_node->_prev = tail;
		//	new_node->_next = _guard;
		//	_guard->_prev = new_node;
		//}

		void insert(iterator pos, const T& val)
		{
			node* cur = pos._node;
			node* prev = pos._node->_prev;
			node* new_node = new node(val);

			prev->_next = new_node;
			new_node->_prev = prev;
			new_node->_next = cur;
			cur->_prev = new_node;
		}

		iterator erase(iterator pos)
		{
			assert(pos != end());

			node* prev = pos._node->_prev;
			node* next = pos._node->_next;
			prev->_next = next;
			next->_prev = prev;
			delete pos._node; //迭代器失效
			return iterator(next);
		}

		void push_back(const T& val)
		{
			insert(end(), val);
		}

		void push_front(const T& val)
		{
			insert(begin(), val);
		}

		void pop_back()
		{
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}

		void swap(list<T>& tmp)
		{
			std::swap(_guard, tmp._guard);
		}

		list<T>& operator=(list<T> lt) //交换的是传入参数的拷贝构造
		{
			swap(lt);
			return *this;
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
				//erase(it++); //后置++
			}
		}

		size_t size() const
		{
			size_t cnt = 0;
			const_iterator it = begin();
			while (it != end())
			{
				++cnt;
				++it;
			}
			return cnt;
		}

		//lt.front()
		T& front()
		{
			return begin()._node->_val;
		}

		const T& front() const
		{
			return begin()._node->_val;
		}

		T& back()
		{
			return end()._node->_val;
		}

		const T& back() const
		{
			return end()._node->val;
		}

		~list()
		{
			clear();
			delete _guard;
			_guard = nullptr;
		}

	private:
		node* _guard; //哨兵位头节点

	};

	void test_list1()
	{
		list<int> ll;
		ll.push_back(1);
		ll.push_back(2);
		ll.push_back(4);
		ll.push_back(3);

		list<int>::iterator it = ll.begin();
		while (it != ll.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}
}
