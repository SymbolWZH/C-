#pragma once
#include <vector>
//实现一个位图
using namespace std;
namespace BITSET
{
	class bitset
	{
	public:
		bitset(size_t N)
		{
			_bits.resize(N / 32 + 1, 0);
			_num = 0;
		}
		void set(size_t x)
		{
			size_t index = x / 32;//算出x映射的位在第几个
			size_t pos = x % 32;  // 算出x这个整型中第几个位置

			_bits[index] |= (1 << pos);//把这个数置成1
		}
		void reset(size_t x)
		{
			size_t index = x / 32;//算出x映射的位在第几个
			size_t pos = x % 32;  // 算出x这个整型中第几个位置

			_bits[index] &= ~(1 << pos);//把这个数置成0
			--_num;
		}
		bool test(size_t x)
		{
			//判断x在不在(也就是说x映射的位知否为1)
			size_t index = x / 32;//算出x映射的位在第几个
			size_t pos = x % 32;  // 算出x这个整型中第几个位置
			return  _bits[index] & (1 << pos);
		}
	private:
		vector<int> _bits;
		size_t _num;//映射存储多少个数据
	};

	void test_bitset()
	{
		bitset bs(100);
		bs.set(99);
		bs.set(98);
		bs.set(97);
		bs.set(5);
		bs.reset(98);
		for (size_t i = 0; i < 100; i++)
		{
			printf("[%d]:%d\n", i, bs.test(i));
		}
	}
}