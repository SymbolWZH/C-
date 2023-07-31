#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <initializer_list>
using namespace std;

#if 0 
//列表初始化，不过我们要能看懂。实际中这个用得也不多。
class Point
{
public:
	Point(int x = 0, int y = 0) :_x(x), _y(y) {}
private:
	int _x;
	int _y;
};
int main()
{
	//c++ 11
	int y{ 2 };
	vector<int> v1{ 1,2,3,4,5 };
	vector<int> v2 = { 1,2,3,4,5 };

	list<int> l1{ 1,2,3,4,5 };
	list<int> l2 = { 1,2,3,4,5 };

	map<string, int> m1{ {"苹果",1},{"西瓜",2},{"香蕉",3}};
	map<string, int> m2 = { {"苹果",1},{"西瓜",2},{"香蕉",3} };

	Point p1(1, 2);
	Point p2{ 1, 2 };
	Point p3 = { 1, 2 };

	auto il1 = { 1,2,3 };
	initializer_list<int> il2 = { 1,2,3 };

	return 0;
}
#endif
#if 0
// 类型推导  属于RTTI  run time type Identification
int main()
{
	int a = 10;
	int  b = 20;//如果b是double typeid c 就是double 不同的类型会向更高的类型转换
	auto c = a + b;
	cout << typeid(c).name() << endl;//获得推导的类型名称 int

	string s;
	cout << typeid(s).name() << endl;//获得推导的类型名称 int
	decltype(s) e; //关键字decltype将变量的类型声明为表达式指定的类型。
	cout << typeid(e).name() << endl;//获得推导的类型名称 int

}
#endif
//final与override(了解)
//回忆一下这两个关键字分别的作用是什么?
//final修饰类，类就变成了最终类，不能被继承
//final还可以修饰虚函数，这个虚函数不能被重写
//override是子类重写虚函数，检查是否完成重写。不满足重写的条件，则报错。

//容器
// C++98容器
//string/vector/list/deque/map/set/bitset + stack/queue/priority_queue
//C++11新容器
//array(定长数组) : 实际中用的很少，缺点; 定长 + 存储数据的空间在栈上, 栈的空间本来就不大。
//forword list(单链表) :实际中用得少，缺点:不支持尾插尾删 + insert数据也是在当前位置的后面
//unordered map / unordered set : 推荐使用，因为他们的效率高于map / set

//默认成员函数控制
class A
{
public:
	A() = default;//指定显示去生成默认的构造函数

	A(const A& a) = delete;//对象防拷贝
	A& operator = (const A& a) = delete;

	

private:
	int _a = 10;
};


//右值引用和移动语义（重点）
// C++98就提出了引用的概念，引用就给一个对象取别名。
// C++98 左值引用
// C++11 右值引用
//不管是左值引用，还是右值引用，他们都是给对象取别名，
//不过左值引用主要是给左值取别名，右值引用主要是给右值取别名。


//左边就是左值?右边的就是右值? 注意这个是一个C语法就留下的坑，就像左移和右移一样，
//这里左右不是方向。左边的值也不一定左值，右边的值不一定是右值
//int x1 = 10; int x2 = x1:int x3 = x1+x2;这里xl是左值，10是右值，x2是左值  x1+x2是表达式返回值
//可以修改就可以认为是左值，左值通常是变量
// 右值通常是常量，表达式或者函数返回值(临时对象)
//int main()
//{
//	// 左值引用的定义
//	int a = 0;
//	int& b = a;
//	int x = 1, y = 2;
//	// 左值引用不能因引用右值，const左值引用可以
//	//int& e = 10;
//	//int& f=x+ y;
//	const int& e = 10;
//	const int& f = x + y;
//	//右值引用不能引用左值，但是可以引用move后左值
//	//int&& m = a;
//
//	//左值和右值作为函数参数构成重载
//	int&& m = move(a);
//	
//	return 0;
//}
//C++11又将右值区分为:纯右值和将亡值
// 纯右值:基本类型的常量或者临时对象  本质是提高效率 减少拷贝
//将亡值:自定义类型的临时对象
//结论:所有深拷贝类(vector / list / map / set...)，都可以加两个右值引用做参数的移动拷贝和移动赋值
#if 0
class String
{
public:
	String(const char* str = "")
	{
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}
	//s2(s1)
	String(const String& s)
	{
		 cout << "String(const String& s)-深拷贝" << endl;
		_str = new char[strlen(s._str) + 1];
		strcpy(_str, s._str);
	}
	//s3右值-将亡值
	String( String&& s)
		:_str(nullptr)
	{
		//传过来的是一个将亡值，反正你都要亡了，我的目的是跟你有一样大的空间，一样的值
		//不如把你的控制和只给我
		cout << "String( String&& s)移动拷贝--效率高" << endl;
		swap(_str, s._str);
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* newchar = new char[strlen(s._str) + 1];
			strcpy(newchar, _str);
			delete _str;
			_str = newchar;
		}
		return *this;

	}//右值
	String& operator=(String&& s)
	{
		swap(_str, s._str);
		return *this;
	}
	~String()
	{
		delete _str;
	}
private:
	char* _str;
};

String f(const char* str)
{
	String tmp(str);
	return tmp;//这里返回实际是tmp拷贝的临时对象
}
//现实中不可避免存在传值返回的场景，传值返回的拷贝返回对象的临时对象。
//如果vector只实现参数为const左值引用深拷贝，那么下面的代价就很大
//
//vector(const vector<T>& v)->深拷贝
// 但是如果vector实现了参数右值引用的移动拷贝，那么这里效率就会很高
// vector(vector<T>&& v)->移动拷贝
// 结论:右值引用本身没太多意义，右值引用的实现了移动构造和移动赋值
// 那么面对接收函数传值返回对象(右值)等等场景，可以提高效率
int main()
{
	String s1("hello world");
	String s2(s1); //参数是左值
	//String s3(String("临时对象-右值")); 
	String s3(f("临时对象-右值"));//参数是右值	- 将亡值(传递值给你，用完我就析构了)
	String s4(move(s1));
	return 0;
}
#endif
// 总结
// 右值引用做参数和作返回值减少拷贝的本质是利用了移动构造和移动赋值
// 左值引用和右值引用本质的作用都是减少拷贝，右值引用本质可以认为是弥补左值引用不足的地方,他们相辅相成
// 左值引用:解决的是传参过程中和返回值过程中的拷贝
// 做参数: void push(T x) -> void push(const T& x)解决的是传参过程中减少拷贝
// 做返回值:T f2() -> T& f2()解决的返回值过程中的拷贝
// ps:但是要注意这里有限制，如果返回对象出了作用域不在了就不能用传引用，这个左值引用无法解决，等待C++11右值引用解决
//右值引用:解决的是传参后，push/insert函数内部将对象移动到容器空间上的问题.
//+ 传值返回接收返回值的拷贝
// 做参数: void push(T&& x) 解决的push内部不再使用拷贝构造x到容器空间上，而是移动构造过去
//做返回值 : T f2() : 解决的外面调用接收f2()返回对象的拷贝，T ret = f2(), 这里就是右值引用的移动构造，减少了拷贝


#if 0
//完美转发
void Fun(int& x) { cout << "左值引用" << endl; }
void Fun(const int& x) { cout << "const 左值引用" << endl; }
void Fun(int&& x) { cout << "右值引用" << endl; }
void Fun(const int&& x) { cout << "const 右值引用" << endl; }
// 模板中的&&不代表右值引用，而是万能引用，其既能接收左值又能接收右值。
// 模板的万能引用只是提供了能够接收同时接收左值引用和右值引用的能力，
// 但是引用类型的唯一作用就是限制了接收的类型，后续使用中都退化成了左值，
// 我们希望能够在传递过程中保持它的左值或者右值的属性, 就需要用我们下面学习的完美转发
template<typename T>
void PerfectForward(T&& t)
{
	//Fun(t);//右值引用会第二次之后的参数传递过程中属性丢失
	//完美转发
	Fun(std::forward<T>(t));
}
int main()
{
	PerfectForward(10);// 右值
	int a;
	PerfectForward(a);// 左值
	PerfectForward(std::move(a)); // 右值
	const int b = 8;
	PerfectForward(b);// const 左值
	PerfectForward(std::move(b)); // const 右值
	return 0;
}
#endif

//lambda表达式语法
//lambda表达式书写格式：[capture - list](parameters) mutable -> return-type{ statement
//}
//1. lambda表达式各部分说明
//[capture - list] : 捕捉列表，该列表总是出现在lambda函数的开始位置，编译器根据[]来
//判断接下来的代码是否为lambda函数，捕捉列表能够捕捉上下文中的变量供lambda
//函数使用。
//(parameters)：参数列表。与普通函数的参数列表一致，如果不需要参数传递，则可以
//连同()一起省略
//mutable：默认情况下，lambda函数总是一个const函数，mutable可以取消其常量
//性。使用该修饰符时，参数列表不可省略(即使参数为空)。
//->returntype：返回值类型。用追踪返回类型形式声明函数的返回值类型，没有返回
//值时此部分可省略。返回值类型明确情况下，也可省略，由编译器对返回类型进行推
//导。
//{
//	statement
//}：函数体。在该函数体内，除了可以使用其参数外，还可以使用所有捕获
//到的变量。
//注意：
//在lambda函数定义中，参数列表和返回值类型都是可选部分，而捕捉列表和函数体可以为
//空。因此C++11中最简单的lambda函数为：[]{}; 该lambda函数不能做任何事情。


//lamber表达式其实定义函数内存的匿名函数
int v()
{
	//最简单的lambda表达式，该lambda表达式没有任何意义
	//没有参数，没有返回值
	[] {};

	// 省略参数列表和返回值类型，返回值类型由编译器推导为int
	int a = 3, b = 4;
	//[捕捉列表](参数)->返回值类型{函数体}
	//auto add = [](int x1, int x2)->int {return x1 + x2; };
	//auto add = [a, b]()->int {return a + b; };
	// 省略了返回值类型，无返回值类型
	//auto fun1 = [&](int c) {b = a + c; };
	//fun1(10);
		cout << a << " " << b << endl;
		auto swap = [](int&a, int &b) {
			int c = a;
			a = b,
			b = c;
		};
		swap(a, b);
	//捕捉列表就是捕捉跟我一个作用域的对象
	// 传值捕捉[a]捕捉a[a,b]捕捉a，b[=]捕捉同一作用域中的所有对象
	// 传引用捕捉[&a]捕捉a [&a,&b]捕捉a，b[&]捕捉同一作用域中的所有对象
	// 各部分都很完善的lambda函数
	//auto fun2 = [=, &b](int c)->int {return b += a + c; };
	//cout << fun2(10) << endl;

	//// 复制捕捉x
	//int x = 10;
	//auto add_x = [x](int a) mutable { x *= 2; return a + x; };
	//cout << add_x(10) << endl;
	return 0;

}