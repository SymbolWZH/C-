#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

namespace OPEN_HASH
{
	template<class K>
	struct SetKeyOfT
	{
		//仿函数
		const K& operator()(const K& key)
		{
			return key;
		}
	};
	template<class T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;
		HashNode(const T& data)
			:_data(data),_next(nullptr)
		{}
	};
	
	template<class K>
	struct Hash//默认的仿函数直接返回key因有些类型的key直接就可以取模
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};
	template<>//特化
	struct Hash<string>//将string转成可以取模的仿函数
	{
		size_t  operator()(const string& key)
		{
			size_t hash = 0;
			for (size_t i = 0; i < key.size(); i++)
			{
				hash *= 131;
				hash += key[i];
			}
			return hash;
		}
	};
	//前置声明
	template<class K, class T, class KeyOfT, class Hash>
	class HashTable;
	//迭代器
	template<class K, class T, class KeyOfT, class Hash = Hash<K>>
	struct __HashTableIterator
	{
		typedef __HashTableIterator<K, T, KeyOfT, Hash> Self;
		typedef HashTable<K, T, KeyOfT, Hash> HT;
		typedef HashNode<T> Node;

		Node* _node;
		HT* _pht;
		__HashTableIterator(Node* node, HT* pht)
			:_node(node), _pht(pht) {}


		T& operator*()
		{
			return _node->_data;
		}
		T& operator->()
		{
			return &_node->_data;

		}
		T& operator != (const Self& s)
		{
			return _node = s._node;

		}
		T& operator++()
		{
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				KeyOfT koft;
				size_t i = _pht->HashFunc(koft(_node->_data)) % _pht->tables.size();
				++i;
				for (; i < _pht->tables.size(); i++)
				{
					Node* cur = _pht->tables[i];
					if (cur)
					{
						_node = cur;
						return *this;
					}
				}
				_node = nullptr;
			}
			return *this;
		}
	};

	template<class K,class T,class KeyOfT,class Hash = Hash<K>>
	class HashTable
	{
		typedef HashNode<T> Node;
	public:
		typedef __HashTableIterator<K, T, KeyOfT,Hash> iterator;


		iterator begin()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				if (_tables[i])
				{
					return iterator(_tables[i],this);
				}
			}
			return end();
		}
		iterator end()
		{
			return iterator(nullptr,this);
		}
		~HashTable()
		{
			clear();
		}
		void clear()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}

		size_t HashFunc(const K & key)
		{
			Hash hash;
			return hash(key);
		}
		bool Insert(const T& data)
		{
			KeyOfT koft;
			// 如果负载因子等于1，则增容，避免大量的哈希冲突
			if (_tables.size() == _num)
			{
				//增容
				// 1.开2倍大小的新表()
				// 2.遍历旧表的数据，重新计算在新表中位置
				// 3.释放旧表
				vector<Node*> newtables;
				size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				newtables.resize(newsize);
				for (size_t i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						// 将旧表中的节点取下来重新计算在新表中的位置，并插入进去
						Node* next = cur->_next;
						size_t index =HashFunc( koft(cur->_data)) % newtables.size();
						cur->_next = newtables[index];
						newtables[index] = cur;

						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newtables);
			}

			size_t index = HashFunc(koft(data)) % _tables.size();//算出表的大小
			Node* cur = _tables[index];//在表中检查有没有这个位置
			while (cur)
			{
				if (koft(cur->_data)== koft(data))//当前表中有没有这个值
					return false;
				else
					cur = cur->_next;//如果没有就往下一个找
			}
			// 2、头插到挂的链表中(尾插也可以)
			Node* newnode = new Node(data);
			newnode->_next = _tables[index];
			_tables[index] = newnode;

			++_num;
			return true;
		}

		Node* Find(const K& key)
		{
			KeyOfT koft;

			size_t index = HashFunc(key) % _tables.size();
			Node* cur = _tables[index];
			while (cur)
			{
				if (koft(cur->_data) == key)
					return cur;
				else
					cur = cur->_next;
			}
			return nullptr;
		}
		bool Erase(const K& key)
		{
			KeyOfT koft;


			size_t index = HashFunc(key) % _tables.size();
			Node* parent = nullptr;
			Node* cur = _tables[index];
			while (cur)
			{
				
				if (koft(cur->_data) == key)
				{
					if (parent == nullptr)
						_tables[index] = cur->_next;
					else
						parent->_next = cur->_next;

					delete cur;
					return true;
				}
				else
				{
					parent = cur;
					cur = cur->_next;
				}
			}

			return false;
		}
	private:
		vector<Node*> _tables;//存节点的指针
		size_t _num = 0;//记录表中存储的个数
	};

	void TestHashTable()
	{
		HashTable<int, int,SetKeyOfT<int>> ht;
		ht.Insert(4);
		ht.Insert(14);
		ht.Insert(24);
		ht.Insert(5);
		ht.Insert(15);
		ht.Insert(25);
		ht.Insert(6);
		ht.Insert(16);
		ht.Insert(26);
		ht.Insert(36);
		ht.Insert(33);
		ht.Insert(44);

		ht.Erase(4);
		ht.Erase(44);
	}

	void TestHashTable2()
	{
		HashTable<string, string, SetKeyOfT<string>,Hash<string>> ht;
		ht.Insert("sort");
		ht.Insert("sort1");
		ht.Insert("sort1asda");
		ht.Insert("asd");
		ht.Insert("soasdasrt1asda");
		ht.Insert("sorasdadt1asda");


	}
}