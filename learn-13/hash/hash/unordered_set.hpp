#define _CRT_SECURE_NO_WARNINGS
#include "HashTable.h"

namespace zh
{
	template<class K, class hash = Hash<K>>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename LinkHash::HashTable<K, K, SetKeyOfT, hash>::iterator iterator;
		iterator begin()
		{
			return _ht.begin();
		}
		iterator end()
		{
			return _ht.end();
		}
		pair<iterator, bool> insert(const K& key)
		{
			return _ht.Insert(key);
		}

	private:
		LinkHash::HashTable<K, K, SetKeyOfT, hash> _ht;
	};
}