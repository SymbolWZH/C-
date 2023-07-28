#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
using namespace std;
#if 0
//ģ�����
// #define N 1000
// ����ģ�����
//template<class T>
//template<typename T>
// 
//1. �����Ͳ��� + int N ���Ƿ�����ģ�����
/*  1.��������������Լ��ַ����ǲ�������Ϊ������ģ������ġ�
	2.�����͵�ģ����������ڱ����ھ���ȷ�Ͻ����
*/
template<class T , int N>
class Array
{
public:
private:
	T _a[N];
};

// 2 ģ����ػ� (�ػ� : ���ĳЩ���͵����⻯����)
template<class T>
bool IsEqual(T& left, T& right)
{
	return left == right;
}
//����ģ��д�� (�ػ� : ���ĳЩ���͵����⻯����)
template<>
bool IsEqual<char*>(char*& left, char*& right)
{
	return strcmp(left,right) == 0;
}
//�������
template<class T1,class T2>
class Data
{
public:
	Data() { cout << "ԭģ��Data<T1,T2>" << endl; }
private:
	
};

//1 ������� �ػ�(ȫ�ػ���ȫ���Ĳ����ػ�)
template<>
class Data<int,char>
{
	public:
	Data() { cout << "ȫ�ػ� Data<int ,char>" << endl; }
	private:

};
//2 ƫ�ػ�
template< class T2>
class Data<int,  T2>
{
	public:
	Data() { cout << " ƫ�ػ�Data<T1,T2>" << endl; }
	private:

};
//2 ƫ�ػ�
template<class T1, class T2>
class Data<T1*, T2*>
{
public:
	Data() { cout << " ƫ�ػ�Data<T1*,T2*>" << endl; }
private:

};
//2 ƫ�ػ� �������ػ����ֲ���/���߶Բ����Ľ�һ������
template<class T1, class T2>
class Data<T1&, T2&>
{
public:
	Data() { cout << " ƫ�ػ�Data<T1&, T2&>" << endl; }
private:

};

int main()
{
	//Array<int,100> a1;//100
	//Array<int,1000> a2;//1000

	Data<int, int> d1;
	Data<int, double> d2;
	Data<int, char> d3;
	Data<char, char> d4;
	Data<char*, char*> d5;
	Data<char&, char&> d6;

	return 0;
}

#endif



