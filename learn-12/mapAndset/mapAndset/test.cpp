#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <map>
#include <string>
using namespace std;

//set 特点 增删查 速度快 O(logN) 不允许删除
void test_set()
{
	set<int> st;
	multiset<int> ms;//允许冗余 可以存在一样的值
	st.insert(1);
	st.insert(2);
	st.insert(5);
	st.insert(3);
	st.insert(7);
	st.insert(4);
	st.insert(8);
	st.insert(6);
	st.insert(8);
	//排序加去重
	set<int>::iterator it = st.begin();
	while (it != st.end())
	{
		cout << *it << ' ';
		++it;
	}
	cout << endl;
	set<int>::iterator pos = st.find(9);//O(logN)
	//set<int>::iterator pos = find(st.begin(),st.end(), 9);//O(N)

	if(pos != st.end())//需要加上判断不然会报错
		st.erase(pos);

	for (auto e : st)
	{
		cout << e << " ";
	}
	cout << endl;
}
//map
//1、增   insert + operator[]
//2、删   erase
//3、查   find
//4、改   operator[]
//5、遍历 iterator + 范围for
void test_map()
{
	map<int, int> m;
	m.insert(pair<int, int>(1, 1));
	m.insert(pair<int, int>(3, 3));
	m.insert(pair<int, int>(2, 2));//pair 构造函数 一个匿名对象
	m.insert(make_pair<int, int>(2, 2));//make_pair 函数模板 不需要模板参数 自动推导


	map<int, int>::iterator it = m.begin();
	while (it != m.end())
	{
		//cout << (*it).first<< " :"<< (*it).second << " ";// *返回节点值的引用
		cout << it->first << ":" << it->second << " ";//节点中值的指针
		++it;
	}
	cout << endl;
	for (auto e : m)
	{
		cout << e.first << ":" << e.second << " ";
	}
	cout << endl;

}
void test_map2()
{
	map<int, string> dict;
	dict.insert(make_pair(1, "苹果"));
	dict.insert(make_pair(3, "香蕉"));
	dict.insert(make_pair(2, "菠萝"));
	map<int,string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		cout << it->first << ":" << it->second << " ";
		++it;
	}
	cout << endl;

}

void test_map3()
{
	string strs[] = { "西瓜","樱桃","西瓜","苹果","西瓜","西瓜","西瓜","苹果" };
	map <string, int > countMap;
	for (auto& str : strs)
	{
		map<string, int>::iterator ret = countMap.find(str);
		if (ret != countMap.end())
			//ret->second++;
			countMap[str]++;
		else
			countMap.insert(make_pair(str, 1));
	}
		for (auto& e : countMap)
		{
			cout << e.first << ":" << e.second << endl;
		}
	
}
//int main()
//{
//	//test_set();
//	//test_map();
//	//test_map2();
//	test_map3();
//
//	return 0;
//}