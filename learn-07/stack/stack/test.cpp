#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"
#include "queue.h"
#include "priority_ququ.h"
#include <queue>
#include <functional>

//(序列式容器)C++ + 进阶 : 关联式容器
//容器:string / vector / list / deque
//适配器 : stack / queue / priority_queue
//跌代器 : iterator / const iterator / reverse iterator / const reverse iterator
//算法 :sort / find / reverse
//仿函数 : less / greater

//容器适配器 都不支持迭代器遍历，通常都包含一些特殊的性质
//void test_priority_queue()
//{
//	//priority_queue<int,vector<int>,greater<int>>
//	//加上greater<int> 默认小的优先级高
//	priority_queue<int> pq;//默认大的优先级高 默认是大堆
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
//仿函数 ，他的对象可以像函数一样去使用

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