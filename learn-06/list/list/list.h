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
//const T& val == 0 --> �����string���� --> const T& val = T() --> T()�������͵�Ĭ�Ϲ���(int(), string(), char()...)
			:_prev(nullptr)
			, _next(nullptr)
			, _val(val)
		{}

	};

	//class list_node //ʹ��class�����������װ�ڵ��Ա����������������
	//{
	//	list_node<T>* _prev;
	//	list_node<T>* _next;
	//	T _val;

	//	list_node(const T& val) //T()����Զ�������(��:string)
	//		:_prev(nullptr)
	//		, _next(nullptr)
	//		, _val(val)
	//	{}
	//};

	template <class T, class reference, class pointer>
	struct list_iterator //ָ����Ϊ(������ָ��) --> ͨ���ڲ���Ա����_node��������Ӧ�Ĳ���
	{
		typedef list_node<T> node;
		typedef list_iterator<T, reference, pointer> self;

		node* _node; //��Ա����

		list_iterator(node* node) //Ϊʲô��Ҫ? --> begin()��end()����Ҫ���ؽڵ� --> ��Ҫ���췵��
			:_node(node) 
//Ϊʲôlist_node����û��д��������(���)?
//ͬ��string����ʵ�־���Ҫ����أ�
//--> node->_prev��node->_next����ָ���32����λ��ֵ,ֻ�����ǳ�������� 
		{}

		reference operator*()
		{
			return _node->_val; //const�Ƿ�����
		}

		pointer operator->()
		{
			return &_node->_val; //const�Ƿ�����
		}

		//++it --> it:list_iterator<T>* --> self
		self& operator++() //ǰ��++
		{
			_node = _node->_next;
			return *this; //return list_iterator<T>(_guard->_next); --> node* --> list_node<T>* | *this --> list_iterator<T>
		}

		self operator++(int) //����ֵ����ʹ�����÷��� --> �ֲ�����tmp���������������
		{
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		self& operator--() //ǰ��--
		{
			_node = _node->_prev;
			return *this;
		}

		self operator--(int) //����--������ֵ����ʹ�����÷��� --> �ֲ�����tmp���������������
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
		//typedef node* iterator; //err --> ����:typedef char* iterator --> ���������ռ�洢 --> list����ʽ�ṹ���������ռ� --> err
		//iterator begin()
		//	return _guard->_next;
		//iterator end()
		//	return _guard;
		typedef list_iterator<T, T&, T*> iterator;
		//����const_iteratorֱ�Ӹ���iterator������?���ԣ����Ǵ�������, ��Ϊֻ�ǶԽڵ�val�Ƿ���ĵľ��ߣ� --> �������:��ģ���һ������reference����ʾ�Ƿ���const����
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

		list()//���캯����ʼ��
		{
			_guard = new node;
			_guard->_next = _guard;
			_guard->_prev = _guard;
		}

		template <class Iterator>
		list(Iterator first, Iterator last) //������ʵ�ֹ���
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
			delete pos._node; //������ʧЧ
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

		list<T>& operator=(list<T> lt) //�������Ǵ�������Ŀ�������
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
				//erase(it++); //����++
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
		node* _guard; //�ڱ�λͷ�ڵ�

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
