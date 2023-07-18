#define _CRT_SECURE_NO_WARNINGS
#include "vector.h"
#if 0
void test_vector()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);

	vector<int>::iterator it = v1.begin();
	while (it != v1.end())
	{
		cout << *it << " ";
		++it;
	}
	vector<int>::reverse_iterator rit = v1.rbegin();
	while (rit != v1.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
	for (auto v : v1)
	{
		cout << v << " ";
	}
}
void print(const vector<int>& v)
{
	vector<int>::const_reverse_iterator rit = v.rbegin();
	while (rit != v.rend())
	{
		cout << *rit << " ";
		++rit;
	}
}
void test_vector1()
{
	//迭代器失效
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);
	v.push_back(9);
	v.push_back(8);
	vector<int>::iterator it = v.begin();
	v.push_back(9);
	v.push_back(10);
	v.push_back(11);
	print(v);
}
int main()
{
	//vector<int> v;
	//v.push_back(1);
	//v.push_back(2);
	//v.push_back(3);
	//v.push_back(4);
	//v.push_back(5);
	//v.push_back(6);
	//v.push_back(7);
	//v.push_back(8);
	//v.push_back(9);
	//v.push_back(8);


	////删除 
	//vector<int>::iterator pos = find(v.begin(), v.end(), 8);
	//if (pos != v.end())
	//{
	//	v.erase(pos);
	//}
	//print(v);
	//cout << v.size() << endl;
	//cout << v.capacity() << endl;
	//print(v);
	//test_vector();

	//迭代器失效
	test_vector1();
	return 0;
}
#endif 

//vector 深度剖析和模拟实现
using namespace zh;
using zh::vector;
int main()
{
	//test_iterator();
	::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);

	v.insert(v.begin(), 0);
	print_vector(v);
	::vector<int> v2;
	v2 = v;
	::vector<int> v3(v2);
	print_vector(v2);
	print_vector(v3);
}