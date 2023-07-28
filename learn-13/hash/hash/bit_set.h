#pragma once
#include <vector>
//ʵ��һ��λͼ
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
			size_t index = x / 32;//���xӳ���λ�ڵڼ���
			size_t pos = x % 32;  // ���x��������еڼ���λ��

			_bits[index] |= (1 << pos);//��������ó�1
		}
		void reset(size_t x)
		{
			size_t index = x / 32;//���xӳ���λ�ڵڼ���
			size_t pos = x % 32;  // ���x��������еڼ���λ��

			_bits[index] &= ~(1 << pos);//��������ó�0
			--_num;
		}
		bool test(size_t x)
		{
			//�ж�x�ڲ���(Ҳ����˵xӳ���λ֪��Ϊ1)
			size_t index = x / 32;//���xӳ���λ�ڵڼ���
			size_t pos = x % 32;  // ���x��������еڼ���λ��
			return  _bits[index] & (1 << pos);
		}
	private:
		vector<int> _bits;
		size_t _num;//ӳ��洢���ٸ�����
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