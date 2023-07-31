#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

// 什么是异常:异常是面向对象语法处理错误一种方式
//C语言传统的处理错误的方式有哪些呢?
//1、返回错误码有些API接口都是把错误码放到errno中
//2、终止程序比如发生越界等严重问题时，我们也可以主动调用exit(xx):
// 传统的处理错误的缺陷:
// 如果一个函数是用过返回值拿数据，发生错误时很难处理

int Div(int& a ,  int& b)
{
	if (b == 0)
		throw "发生除0错误";
	if(a == 0)
		throw -1;
	if (a == 1 && b == 1)
		throw string("发生除0错误");

	return a % b;

}
int m1()
{
	try
	{
		int n, m;
		cin >> n >> m;
		cout << Div(n, m) << endl;
	}
	catch (int err)
	{
		cout << err << endl;
	}
	catch (const string& err)
	{
		cout << err << endl;
	}
	catch (...)
	{
		cout << "未知异常" << endl;
	}
	return 0;
}

// 公司会给一个基类
//要求你可以自己抛自己定义的异常，但是必须继承这个基类
//这样的话，外层捕获就只需要捕获基类就可以
class Exception
{
public:
	Exception(const char*  str, int errid)
		:_errmsg(str),_errid(errid)
	{}
	virtual string what() = 0;
protected:
	int _errid; //错误码
	string _errmsg;//错误描述
	// stack<string> _st;
};
class SqlException : public  Exception
{

public:
	SqlException(const char* str, int errid)
		:Exception(str,errid)
	{}

	virtual string what() 
	{
		return "网络错误：" + _errmsg;
	}
};

void ServerStart()
{
	//模拟一下出现问题跑一次
	if (rand() % 11 == 0)
		throw SqlException("数据库启动失败", 1);
	if (rand() % 7 == 0)
		throw SqlException("网络链接失败",3);
	cout << "正常运行" << endl;
}
int main()
{
	for (size_t i = 0; i < 100; i++)
	{
		try
		{
			for (size_t i = 0; i < 100; i++)
			{
				ServerStart();
			}
		}
		catch (Exception& e)
		{
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "未知异常" << endl;
		}
	}
	return 0;
}

// 异常的优缺点总结:
// 优点:
// 1、清晰的包含错误信息
// 2、面对T operator[](int i)这样函数越界错误，异常可以很好的解决
// 3、多层调用时，里面发生错误，不再需要层层处理，最外层直接捕获即可
// 4、很多第三方库都是用异常，我们也使用异常可以更好的使用他们。比如:boost、gtest、gmock
// 缺点:
// 1、异常会导致执行流乱跳。会给我调试分析程序bug带来一些困难。
// 2、c++没有GC,异常可能到导致资源泄露等异常安全问题。 需要学会使用RAII来解决。
// 3、C++的库里面的异常体系定义不太好用，很多公司都会选择自己定义。
// 4、C++的异常语言可以抛任意类型的异常，如果项目中没有做很好规范管理，那么会非常的混
//乱，所以一般需要定义出继承体系的异常规范。

// 异常整体而言还是一个利大于弊的东西，所以实际日常练习或者小项目，不太使用
// 公司一般还是会选择异常来处理错误