#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stack>
#include <vector>
#include <list>
using namespace std;


namespace zh
{
	template <class T,class Container>
	class stack
	{
	public:
		void push(const T& x)
		{
			con.push_back(x);
		}
		void pop()
		{
			con.pop_back();
		}
		int size()
		{
			return con.size();
		}
		int empty()
		{
			return con.empty();
		}
		T& top() { return con.back(); }
	private:
		Container con;
	};

	void test_stack( )
	{
		//stack<int, vector<int>> sv;
		stack<int, deque<int>> sv;

		sv.push(1);
		sv.push(2);
		sv.push(3);
		sv.push(4);

		while (!sv.empty())
		{
			cout << sv.top() << " ";
			sv.pop();
		}
	}

}