#pragma once
#include <iostream>
#include "bit_set.h"
#include <string>
using namespace std;
namespace bit
{
	//BKDR
	struct HashStr1 {
		size_t operator()(const string& str)
		{
			size_t hash = 0;

			for (size_t i = 0; i < str.size(); i++)
			{
				hash *= 131;
				hash += str[i];
			}
			return hash;

		}
	};
	//SDBMHash
	struct HashStr2 {
		size_t operator()(const string& str)
		{
			size_t hash = 0;

			for (size_t i = 0; i < str.size(); i++)
			{
				hash = 65599 * hash + i;
				
			}
			return hash;

		}
	};
	struct HashStr3 {
		size_t operator()(const string& str)
		{
			size_t hash = 0;
			size_t magic = 63689;

			for (size_t i = 0; i < str.size(); i++)
			{
				hash *= magic;
				hash += str[i];
				magic *= 378551;
			}
			return hash;

		}
	};
	template<class K=string,
	class Hash1 = HashStr1,
	class Hash2 = HashStr2,
	class Hash3 = HashStr3>
	class bloomfilter
	{
	public:
		bloomfilter(size_t num)
			:_bs(5*num), _N(5 * num)
		{}
		void set(const K& key)
		{
			size_t index1 = Hash1()(key) % _N;
			size_t index2 = Hash2()(key) % _N;
			size_t index3 = Hash3()(key) % _N;

			_bs.set(index1);
			_bs.set(index2);
			_bs.set(index3);
		}
		bool test(const K& key)
		{
			size_t index1 = Hash1()(key) % _N;
			if (_bs.test(index1) == false)
				return false;
			size_t index2 = Hash2()(key) % _N;
			if (_bs.test(index2) == false)
				return false;
			size_t index3 = Hash3()(key) % _N;
			if (_bs.test(index3) == false)
				return false;

			return true;// 但是这里也不一定是真的在，还是可能存在误判
			// 判断在，是不准确的，可能存在误判
			//判断不在，是准确
		}
		void reset(const K& key)
		{
			// 将映射的位置给置0就可以?
			// 不支持删除，可能会存在误删。一般布隆过滤器不支持删除
		}
	private:
	BITSET::bitset _bs;//位图
	size_t _N;
	};

	void test_bloomfilter()
	{
		bloomfilter<std::string> bf(100);
		bf.set("abcd");
		bf.set("aadd");
		bf.set("bcad");

		cout << bf.test("abcd") << endl;
		cout << bf.test("aadd") << endl;
		cout << bf.test("bcad") << endl;
	}
}
