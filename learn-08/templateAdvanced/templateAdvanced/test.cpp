#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
using namespace std;
#if 0
//模板进阶
// #define N 1000
// 类型模板参数
//template<class T>
//template<typename T>
// 
//1. 非类型参数 + int N 就是非类型模板参数
/*  1.浮点数、类对象以及字符串是不允许作为非类型模板参数的。
	2.非类型的模板参数必须在编译期就能确认结果。
*/
template<class T , int N>
class Array
{
public:
private:
	T _a[N];
};

// 2 模板的特化 (特化 : 针对某些类型的特殊化处理)
template<class T>
bool IsEqual(T& left, T& right)
{
	return left == right;
}
//函数模板写法 (特化 : 针对某些类型的特殊化处理)
template<>
bool IsEqual<char*>(char*& left, char*& right)
{
	return strcmp(left,right) == 0;
}
//具体的类
template<class T1,class T2>
class Data
{
public:
	Data() { cout << "原模版Data<T1,T2>" << endl; }
private:
	
};

//1 具体的类 特化(全特化：全部的参数特化)
template<>
class Data<int,char>
{
	public:
	Data() { cout << "全特化 Data<int ,char>" << endl; }
	private:

};
//2 偏特化
template< class T2>
class Data<int,  T2>
{
	public:
	Data() { cout << " 偏特化Data<T1,T2>" << endl; }
	private:

};
//2 偏特化
template<class T1, class T2>
class Data<T1*, T2*>
{
public:
	Data() { cout << " 偏特化Data<T1*,T2*>" << endl; }
private:

};
//2 偏特化 可以是特化部分参数/或者对参数的进一步限制
template<class T1, class T2>
class Data<T1&, T2&>
{
public:
	Data() { cout << " 偏特化Data<T1&, T2&>" << endl; }
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



