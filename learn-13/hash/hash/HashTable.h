#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<class K>
struct Hash//默认的仿函数直接返回key因有些类型的key直接就可以取模
{
	//仿函数
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>//特化
struct Hash<string>
{
	//BKDR哈希
	size_t operator()(const string& s)
	{
		size_t value = 0;
		for (auto ch : s)
		{
			value *= 31;
			value += ch;
		}
		return value;
	}
};
namespace LinkHash
{

	template<class T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;
		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{}
	};

	template<class K, class T, class KeyOfT, class HashFunc>
	class HashTable;

	template<class K, class T, class Ref, class Ptr, class KeyOfT, class HashFunc>
	struct __HTIterator
	{
		typedef HashNode<T> Node;
		typedef __HTIterator<K, T, Ref, Ptr, KeyOfT, HashFunc> Self;
		Node* _node;
		HashTable<K, T, KeyOfT, HashFunc>* _pht;

		__HTIterator(Node* node, HashTable<K, T, KeyOfT, HashFunc>* pht)
			:_node(node)
			, _pht(pht)
		{}
		Ref operator*()
		{
			return _node->_data;
		}
		Ptr operator->()
		{
			return &_node->_data;
		}
		//前置++
		Self& operator++()
		{
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				KeyOfT kot;
				HashFunc hf;
				size_t index = hf(kot(_node->_data)) % _pht->_tables.size();
				++index;
				//找下一个不为空的桶
				while (index < _pht->_tables.size())
				{
					if (_pht->_tables[index] != nullptr)
						break;
					else
						++index;
				}
				//表走完了都没有找到下一个桶
				if (index == _pht->_tables.size())
				{
					_node = nullptr;
				}
				else
				{
					_node = _pht->_tables[index];
				}
			}
			return *this;
		}

		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}
		bool operator==(const Self& s)
		{
			return _node == s._node;
		}

	};

	template<class K, class T, class KeyOfT, class HashFunc>
	class HashTable
	{
		typedef HashNode<T> Node;
		template<class K, class T, class Ref, class Ptr, class KeyOfT, class HashFunc>
		friend struct __HTIterator;
		typedef HashTable<K, T, KeyOfT, HashFunc>& Self;
	public:
		typedef __HTIterator<K, T, T&, T*, KeyOfT, HashFunc> iterator;
		//HashTable(){}
		HashTable() = default;//显示指定编译器去生产默认构造函数
		HashTable(const Self& ht)
		{
			_tables.resize(ht._tables.size());
			for (int i = 0; i < ht._tables.size(); i++)
			{
				Node* cur = ht._tables[i];
				while (cur)
				{
					Node* copy = new Node(cur->_data);
					copy->_next = _tables[i];
					_tables[i] = copy;
					cur = cur->_next;
				}
			}
		}
		//ht1 = ht2
		Self& operator=(Self copy)
		{
			swap(_n, copy._n);
			_tables.swap(copy._tables);
			return *this;
		}
		~HashTable()
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
			}
		}
		iterator begin()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				if (_tables[i])
				{
					return iterator(_tables[i], this);
				}
			}
			return end();
		}
		iterator end()
		{
			return iterator(nullptr, this);
		}
		bool Erase(const K& key)
		{
			if (_tables.empty())
			{
				return false;
			}
			HashFunc hf;
			size_t index = hf(key) % _tables.size();
			Node* cur = _tables[index];
			Node* prev = nullptr;
			KeyOfT kot;
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					if (prev == nullptr)//头删
					{
						_tables[index] = cur->_next;
					}
					else//中间删除
					{
						prev->_next = cur->_next;
					}
					--_n;
					delete cur;
					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}
			return false;
		}
		iterator Find(const K& key)
		{
			if (_tables.empty())
			{
				return end();
			}
			HashFunc hf;
			size_t index = hf(key) % _tables.size();
			Node* cur = _tables[index];
			KeyOfT kot;
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					return iterator(cur, this);
				}
				else
				{
					cur = cur->_next;
				}
			}
			return end();
		}

		size_t GetNextPrime(size_t num)
		{
			static const unsigned long __stl_prime_list[28] =
			{
				53,        97,         193,        389,
				769,       1543,       3079,       6151,
				12289,     24593,      49157,      98317,
				196613,    393241,     786433,     1572869,
				3145739,   6291469,    12582917,   25165843,
				50331653,  100663319,  201326611,  402653189,
				805306457, 1610612741, 3221225473, 4294967291
			};
			for (size_t i = 0; i < 28; i++)
			{
				if (__stl_prime_list[i] > num)
				{
					return __stl_prime_list[i];
				}
			}
			return __stl_prime_list[27];
		}

		pair<iterator, bool> Insert(const T& data)
		{
			HashFunc hf;
			KeyOfT kot;
			iterator ret = Find(kot(data));
			if (ret != end())
			{
				return make_pair(ret, false);
			}
			//负载因子 == 1时就扩容
			if (_n == _tables.size())
			{
				//size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				size_t newSize = GetNextPrime(_tables.size());
				vector<Node*> newTables;
				newTables.resize(newSize);
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;
						size_t index = hf(kot(cur->_data)) % newTables.size();
						//头插
						cur->_next = newTables[index];
						newTables[index] = cur;
						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newTables);
			}
			size_t index = hf(kot(data)) % _tables.size();
			Node* newnode = new Node(data);
			newnode->_next = _tables[index];
			_tables[index] = newnode;
			++_n;
			//return true;
			return make_pair(iterator(newnode, this), false);
		}
	private:
		vector<Node*> _tables;
		size_t _n = 0;//有效的数据个数
	};
	void TestHashTable()
	{

	}
}