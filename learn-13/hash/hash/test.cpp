#define _CRT_SECURE_NO_WARNINGS



#include "HashTable.h"
#include "OPEN_HASH.hpp"
#include "bit_set.h"
#include "BloomFilter.h"
using namespace OPEN_HASH;

//��ϣ(ɢ��) :���洢�����ݸ��洢��λ��ʹ�ù�ϣ����������ӳ���ϵ���������ǽ��и�Ч���ҡ�
//��ϣ��ͻ : ��ͬ��ֵӳ�䵽����ͬ��λ�á�
//�����ϣ��ͻ : 1����ɢ�� - ���Ŷ��Ʒ�(�ҵ�λ�ñ�ռ�ˣ��Ҿ�ȥռ���λ��--���Ƽ�)
//2����ɢ�� - ������(��ͻ��������ʽ�ṹ������)�Ƽ�
int main()
{
	// TestHashTable();
	 //TestHashTable2();
	//BITSET::test_bitset();
	bit::test_bloomfilter();
	return 0;
}