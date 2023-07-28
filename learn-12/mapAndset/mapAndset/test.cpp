#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <map>
#include <string>
using namespace std;

//set �ص� ��ɾ�� �ٶȿ� O(logN) ������ɾ��
void test_set()
{
	set<int> st;
	multiset<int> ms;//�������� ���Դ���һ����ֵ
	st.insert(1);
	st.insert(2);
	st.insert(5);
	st.insert(3);
	st.insert(7);
	st.insert(4);
	st.insert(8);
	st.insert(6);
	st.insert(8);
	//�����ȥ��
	set<int>::iterator it = st.begin();
	while (it != st.end())
	{
		cout << *it << ' ';
		++it;
	}
	cout << endl;
	set<int>::iterator pos = st.find(9);//O(logN)
	//set<int>::iterator pos = find(st.begin(),st.end(), 9);//O(N)

	if(pos != st.end())//��Ҫ�����жϲ�Ȼ�ᱨ��
		st.erase(pos);

	for (auto e : st)
	{
		cout << e << " ";
	}
	cout << endl;
}
//map
//1����   insert + operator[]
//2��ɾ   erase
//3����   find
//4����   operator[]
//5������ iterator + ��Χfor
void test_map()
{
	map<int, int> m;
	m.insert(pair<int, int>(1, 1));
	m.insert(pair<int, int>(3, 3));
	m.insert(pair<int, int>(2, 2));//pair ���캯�� һ����������
	m.insert(make_pair<int, int>(2, 2));//make_pair ����ģ�� ����Ҫģ����� �Զ��Ƶ�


	map<int, int>::iterator it = m.begin();
	while (it != m.end())
	{
		//cout << (*it).first<< " :"<< (*it).second << " ";// *���ؽڵ�ֵ������
		cout << it->first << ":" << it->second << " ";//�ڵ���ֵ��ָ��
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
	dict.insert(make_pair(1, "ƻ��"));
	dict.insert(make_pair(3, "�㽶"));
	dict.insert(make_pair(2, "����"));
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
	string strs[] = { "����","ӣ��","����","ƻ��","����","����","����","ƻ��" };
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