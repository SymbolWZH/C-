#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"
#include "queue.h"
#include "priority_ququ.h"
#include <queue>
#include <functional>

//(����ʽ����)C++ + ���� : ����ʽ����
//����:string / vector / list / deque
//������ : stack / queue / priority_queue
//������ : iterator / const iterator / reverse iterator / const reverse iterator
//�㷨 :sort / find / reverse
//�º��� : less / greater

//���������� ����֧�ֵ�����������ͨ��������һЩ���������
//void test_priority_queue()
//{
//	//priority_queue<int,vector<int>,greater<int>>
//	//����greater<int> Ĭ��С�����ȼ���
//	priority_queue<int> pq;//Ĭ�ϴ�����ȼ��� Ĭ���Ǵ��
//	pq.push(3);
//	pq.push(1);
//	pq.push(9);
//	pq.push(4);
//	pq.push(2);
//
//	while (!pq.empty())
//	{
//		cout << pq.top() << " ";
//		pq.pop();
//	}
//}
using namespace zh;
//�º��� �����Ķ����������һ��ȥʹ��

//int findKthLargest(vector<int>& nums, int k) {
//	priority_queue<int, vector<int>, greater<int>> minheap;
//	size_t i = 0;
//	for (; i < k; ++i)
//		minheap.push(nums[i]);
//
//	for (; i < nums.size(); ++i)
//	{
//		if (nums[i] > minheap.top())
//		{
//			minheap.pop();
//			minheap.push(nums[i]);
//		}
//	}
//	return minheap.top();
//}
int main()
{
	test_priority_queue();


	/*test_stack();
	cout << endl;
	test_queue();
	cout << endl;
	test_priority_queue();*/
	return 0;
}