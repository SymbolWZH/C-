#define _CRT_SECURE_NO_WARNINGS



#include "HashTable.h"
#include "OPEN_HASH.hpp"
#include "bit_set.h"
#include "BloomFilter.h"
using namespace OPEN_HASH;

//哈希(散列) :将存储的数据跟存储的位置使用哈希函数建立出映射关系，方便我们进行高效查找。
//哈希冲突 : 不同的值映射到了相同的位置。
//解决哈希冲突 : 1、闭散列 - 开放定制法(我的位置被占了，我就去占别的位置--不推荐)
//2、开散列 - 拉链法(冲突的数据链式结构挂起来)推荐
int main()
{
	// TestHashTable();
	 //TestHashTable2();
	//BITSET::test_bitset();
	bit::test_bloomfilter();
	return 0;
}