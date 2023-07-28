#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stack>
#include <vector>
#include <list>
#include <deque>//Ë«¶Ë¶ÓÁÐ
using namespace std;


namespace zh
{
	template <class T, class Container>
	class queue
	{
	public:
		void push(const T& x)
		{
			con.push_back(x);
		}
		void pop()
		{
			con.pop_front();
		}
		int size()
		{
			return con.size();
		}
		int empty()
		{
			return con.empty();
		}
		T& front() { return con.front(); }
		T& back() { return con.back(); }

	private:
		Container con;
	};

	void test_queue()
	{
		//queue<int, list<int>> sv;
		queue<int, deque<int>> sv;

		sv.push(1);
		sv.push(2);
		sv.push(3);
		sv.push(4);

		while (!sv.empty())
		{
			cout << sv.front() << " ";
			sv.pop();
		}
	}

}