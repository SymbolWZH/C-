#pragma once
#include <iostream>
using namespace std;


void F1()
{
	cout << " F1" << endl;
}
//ͬ���Ƿ�����룬��ͨ�������ԣ�����ģ��/��ģ��Ϊʲô����?
// Ԥ����-> չ��ͷ�ļ� �滻�� �������� ɾ��ע�� .i
// ���� ����﷨ ���ɻ�����  .s
// ��� ��������ת�ɶ����ƵĻ����� .o
// ���� ��Ŀ���ļ��ϵ�һ�𣬱���ʱ����������������ʱȥ�Һ����ĵ�ַ  a.out
template<class T>
void F2(const T& x)
{
	cout << "void f2 const T"<<x << endl;
}
// 1 ��ʽʵ����  ������ ��Ϊ������
// 2 ��Ҫ�������
//template
//void F2<int>(const int& x);