#include "list.h"
#include <stack>
#include <queue>
#if 0
void print_list1(const list<int>& lt)
{

	list<int>::const_iterator it = lt.begin();
	for (auto it = std::begin(lt); it != std::end(lt); ++it)
		cout << *it << " ";

	cout<< endl;
}

void test_list1()
{
	list<int> lt1;
	lt1.push_back(1);
	lt1.push_back(2);
	lt1.push_back(3);
	lt1.push_back(4);
	print_list1(lt1);

	list<int>::iterator it = lt1.begin();
	for (auto l : lt1)
	{
		cout << l << " ";
	}
	cout << endl;
	list<int> lt2(lt1);
	print_list1(lt2);

	list<int> lt3;
	lt3.push_back(10);
	lt3.push_back(20);
	lt3.push_back(30);
	lt3.push_back(40);
	lt1 = lt3;
	cout << "lt1��";
	for (auto l : lt1)
	{
		cout << l << " ";
	}
	cout << endl;
//֧�ֵĲ����ӿڵĽǶȷֵ�����������:����(forword_list)��˫��(list)�����(vector)
//��ʹ�õĳ����ĽǶȷֵ����������� : (��������������������)+const����
	//���������reverse ����  reserve ���� 
	cout << "reverse_lt1��";
	list<int>::reverse_iterator rit = lt1.rbegin();
	while (rit != lt1.rend())
	{
		cout << *rit << ' ';
		++rit;
	}
		

}
void test_list2()
{
	list<int> lt1;
	lt1.push_back(1);
	lt1.push_back(2);
	lt1.push_back(3);
	lt1.push_back(4);
	print_list1(lt1);

	lt1.push_front(-1);
	lt1.push_back(5);
	print_list1(lt1);

	lt1.pop_front();
	lt1.pop_back();
	print_list1(lt1);

	list<int>::iterator pos = find(lt1.begin(),lt1.end(),3);
	if (pos != lt1.end())
	{
		lt1.insert(pos, 30);//1 2 30 3 4
		//lt1.erase(pos);
	}
	lt1.sort();//���� 1 2 3 4 30
	lt1.reverse();//��ת 30 4 3 2 1
	print_list1(lt1);

}
void test_list3()//������ʧЧ
{
	list<int> lt1;
	lt1.push_back(3);
	lt1.push_back(2);
	lt1.push_back(1);
	lt1.push_back(4);
	print_list1(lt1);

	//ɾ������ż��
	list<int>::iterator it = lt1.begin();
	while (it != lt1.end())
	{
		if(*it % 2 == 0)	
			it = lt1.erase(it);//����Ҫ��it = ɾ���󷵻صĵ�ַ
		else                   //else�������
			++it;
		
	}
	print_list1(lt1);

}
int main()
{
	test_list3();
	return 0;
}

#endif
using namespace zh;


void test_stack() //LIFO
{
	stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);

	while (!st.empty())
	{
		cout << st.top() << " ";
		st.pop();
	}

}

void test_queue()//FIFO
{
	queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}

}
int main()
{
	cout << 16 / 3 << "";
	return 0;
}