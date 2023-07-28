#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <vector>
using namespace std;
namespace zh
{
	template<class T>
	struct less
	{bool operator()(const T& x1, const T& x2){return x1 < x2;}};
	template<class T>
	struct greater
	{bool operator()(const T& x1, const T& x2){return x1 > x2;}};
	//默认是大堆
	template<class T,class Container = vector<T>,class Compare = less<T>>
	class priority_queue
	{
	public:
		void AdjustUp(int child)
		{
			
			int parent = (child - 1) / 2;
			while (child > 0)
			{
				Compare greater;
				//con[child] > con[parent]
				if (greater(con[parent] , con[child]))
				{
					swap(con[child], con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}
		void AdjustDwon(int root)
		{
			int parent = root;
			int child = parent * 2 + 1;
			Compare greater;
			while (child < con.size())
			{
				//选出左右孩子中大的一个
				//child+1 < con.size()&& con[child+1] > con[child]
				if (child+1 < con.size()&& greater(con[child ] , con[child + 1]))
				{
					++child;
				}
				if (greater(con[parent], con[child]))
				{
					swap(con[child], con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
		void push(const T& x)
		{
			//O(logN)
			con.push_back(x);
			AdjustUp(con.size() - 1);
		}
		void pop()
		{
			swap(con[0], con[con.size() - 1]);
			con.pop_back();
			//O(logN)
			AdjustDwon(0);
		}
		T& top(){ return con[0]; }
		int size() { return con.size(); }
		bool empty(){ return con.empty(); }
	private:
		Container con;
	};
	void test_priority_queue()
	{
		priority_queue<int,vector<int>,greater<int>> sv;

		sv.push(3);
		sv.push(1);
		sv.push(9);
		sv.push(4);
		sv.push(2);
		while (!sv.empty())
		{
			cout << sv.top() << " ";
			sv.pop();
		}
	}
}