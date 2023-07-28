#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

namespace OPEN_HASH
{
	template<class K>
	struct SetKeyOfT
	{
		//�º���
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
	struct Hash//Ĭ�ϵķº���ֱ�ӷ���key����Щ���͵�keyֱ�ӾͿ���ȡģ
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};
	template<>//�ػ�
	struct Hash<string>//��stringת�ɿ���ȡģ�ķº���
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
	//ǰ������
	template<class K, class T, class KeyOfT, class Hash>
	class HashTable;
	//������
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
			// ����������ӵ���1�������ݣ���������Ĺ�ϣ��ͻ
			if (_tables.size() == _num)
			{
				//����
				// 1.��2����С���±�()
				// 2.�����ɱ�����ݣ����¼������±���λ��
				// 3.�ͷžɱ�
				vector<Node*> newtables;
				size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				newtables.resize(newsize);
				for (size_t i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						// ���ɱ��еĽڵ�ȡ�������¼������±��е�λ�ã��������ȥ
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

			size_t index = HashFunc(koft(data)) % _tables.size();//�����Ĵ�С
			Node* cur = _tables[index];//�ڱ��м����û�����λ��
			while (cur)
			{
				if (koft(cur->_data)== koft(data))//��ǰ������û�����ֵ
					return false;
				else
					cur = cur->_next;//���û�о�����һ����
			}
			// 2��ͷ�嵽�ҵ�������(β��Ҳ����)
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
		vector<Node*> _tables;//��ڵ��ָ��
		size_t _num = 0;//��¼���д洢�ĸ���
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