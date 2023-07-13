#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <string>
using namespace std;

// 1、引用做参数 场景一
void swap_c(int* pl, int* p2)
{
	int tmp = *pl;
	*pl = *p2;
	*p2 = tmp;
}
void swap_cpp(int& ra, int& rb)//这里是&引用  int &ra = a;
{
	int tmp = ra;
	ra = rb;
	rb = tmp;
}
//场景二   引用做返回值
int Count1()
/*意思就是不引用返回就是多申请可一块空间，存放n值，返回的是新申请的这个空间
的值吗*/
{
	static int n = 0;
	n++;
	return n;
}
int& Count2()

{
	static int n = 0;
	n++;
	return n;
}

//如果返回变量是一个局部变量时候引用返回是不安全的
int& Add2(int a ,int b)
{
			static/*如何解决，加上static*/ int c = a + b;
			return c;
}
/*总结:一个函数要使用引用返回，返回变量出了这个函数的作用域还存在，就可以
使用引用返回，否则就不安全 （全局变量 静态变量）
引用返回好处 那么函数使用引用返回好处是什么呢?-》少创建拷贝一个临时对象，提高效率
引用用的比较多的方式  1 输出型参数（提高效率） 2引用做返回值（提高效率）

int main()
{
	int& ret = Add2(1, 2);//首次调用的时候ret 为c的别名
	//所以再次调用的时候上一个已经销毁了
	Add2(3, 4); 
	//但是ret没有 ret依然可以接收到函数的返回值
	cout << "Add2(1, 2) is :" << ret << endl;//所以打印的结果就为： 7
	return 0;
}
*/

# if 0
int main()
{
#if 0
	//引用部分的问题
	// 权限缩小和放大的规则：适用于引用和指针间
	//权限放大不能把const给非const
	const int a = 10;
	//int& b =a;
	const int& b = a;
	// 权限的缩小非const既可以给非const，也可以给const
	int c = 20;
	int& d = c;
	const int e = c;
# if 0
引用和指针的不同点:
1.引用概念上定义一个变量的别名，指针存储一个变量地址。 
2.引用在定义时必须初始化，指针没有要求
3.引用在初始化时引用一个实体后，就不能再引用其他实体，而指针可以在任何时候指向任何一个同类型实
体
4.没有NULL引用，但有NULL指针
5.在sizeof中含义不同:引用结果为引用类型的大小，但指针始终是地址空间所占字节个数(32位平台下占4
个字节)
6.引用自加即引用的实体增加1，指针自加即指针向后偏移一个类型的大小
7.有多级指针，但是没有多级引用
8.访问实体方式不同，指针需要显式解引用，引用编译器自己处理
9.引用比指针使用起来相对更安全
#endif
#endif
	int a = 0, b = 1;
	swap_c(&a, &b);//这里是取a b 的地址
	swap_cpp(a, b);

	cout << a << b << endl;

	const int& c1 = Count1(); //加const
	int& c2 = Count2();
	return 0;
}
#endif


#if 0 
//7.2 特性
//1.inline是一种以空间换时间的做法，省去调用函数额开销。所以代码很长或者有代码比较长 / 递归的函数适宜使用作为内联函数。
//2.inline对于编译器而言只是一个建议，编译器会自动优化，如果定义为inline的函数体代码比较长 / 递归等等，编译器优化时会忽略掉内联。
//3.inline不建议声明和定义分离，分离会导致链接错误。因为inline被展开，就没有函数地址了，链接就会找不到。
//频繁调用Swap，调用函数需要建立栈帧，是有消耗的
//如何解决 : 1、C言使用宏函数 2、C + 使用内联函数
void swap_c(int& pl, int& p2)
{
	int tmp = pl;
	pl = p2;
	p2 = tmp;
}
//一般内联适用于小函数，小于20-30行
inline/*空间换时间的方法*/ void swap_c(int pl, int p2)
{
	int tmp = pl;
	pl = p2;
	p2 = tmp;
}
#endif

#if 0
//auto键字(C+11)
//auto简介
//在早期C/C++中auto的含义是:使用auto修饰的变量，是具有自动存储器的局部变量，但遗憾的是一直没有人去使用它，大家可思考下为什么?
//C++11中，标准委员会赋予了auto全新的含义即:auto不再是一个存储类型指示符，而是作为一个新的类型
//指示符来指示编译器，auto明的变量必须由编译器在编译时期推导而得。

/*.在同一行定义多个变量
当在同一行声明多个变量时，这些变量必须是相同的类型，否则编译器将会报错，因为编译器实际只对第
一个类型进行推导，然后用推导出来的类型定义其他变量。*/
int TestAuto(auto a)
{// 此处代码编译失败，auto不能作为形参类型，因为编译器无法对a实际类型进行推导
	auto a = 1, b = 2;
	//auto c = 3, d = 4.0;// 该行代码会编译失败，因为cd初始化表达式类型不同

	int a[] = { 1,2,3 };
	auto b[] = { 4,5,6 };//auto不能直接用来声明数组
}

int main()
{
	int a = 10;//int
	auto b = a; //b的类似是根据a的类型推导出来的
	int& c = a;//int

	auto& d = a;//int
	auto* e = &a;//int *
	auto f = &a;//int *


	cout << typeid(a).name() << endl;
	cout << typeid(b).name() << endl;
	cout << typeid(c).name() << endl;

	cout << typeid(d).name() << endl;
	cout << typeid(e).name() << endl;
	cout << typeid(f).name() << endl;

	
	//演示一下auto在实际中的作用，但是下面代码大家大概看一下就可以
	std::map<std::string, std::string> dict;
	std::map<std::string, std::string>::iterator itl = dict.begin();
	auto it2 = dict.begin();// 使用auto进行优化,可以简化代码的写法

	// auto e ; 无法通过编译，使用auto定义变量时，必须对其初始化
	return 0;
	cout << typeid(b).name() << endl;


}

#endif
#if 0
int main()
{
	int array[] = { 1,2,3,4,5 };

	//C语言中的做法
	for (int i = 0; i < sizeof(array) / sizeof(int); i++)
	{
		array[i] *= 2;
	}
	for (int i = 0; i < sizeof(array) / sizeof(int); i++)
	{
		cout << array[i] << " ";
	}
	cout << "C语言"<<endl;


	//C++11 -> 范围for
	for (auto& e : array)//引用
	{
		e *= 2;
	}
	for (auto e : array)
	{
		cout << e << " ";
	}
	cout <<"C++ 11" << endl;
}
#endif




#if 0
/*
NULL际是一个宏，在传统的C文件(stddefh中，可以看到如下代码:
#ifndef NULL
#ifdef___cplusplus
#define NULL   0
#else
#define NULL ((void *)0)
#endif
#endif
程序本意是想通过f(NULL)调用指针版本的f(int*)函数，但是由于NULL定义成0，因此与程序的初衷相悖。
在C++98中，字面常量0既可以是一个整形数字，也可以是无类型的指针(void*)常量，但是编译器默认情况下
将且看成是一个整形常量，如里要将其按照指针方式来使用，必须对其进行强转(void)0。
注意:
1.在使用nullptr表示指针空值时，不需要包含头文件，因为nullptr是C++11作为新关键字引入的。
2.在C++11中，sizeof(nullptr)与sizeof((void*)0)所占的字节数相同。
3.为了提高代码的健壮性，在后续表示指针空值时建议最好使用nullptr*/
void fun(int n)
{
	cout << "整型" << endl;
}
void fun(int* p)
{
	cout << "整型指针" << endl;
}
int main()
{
	//C
	int* p = NULL;

	//C++ 11 中，推荐像下面这样去用
	int* p2 = nullptr;

	fun(0);
	fun(NULL);		//预处理后的fun(0);
	fun(nullptr);	//fun((void*)0);
	return 0;
}
#endif


/*
面向过程和面向对象初步认识
C语言是面向过程的，关注的是过程，分析出求解问题的步骤，通过函数调用逐步解决问题。
C++是基于面向对象的，关注的是对象，将一件事情拆分成不同的对象，靠对象之间的交互完成。

类的引入
C语言中，结构体中只能定义变量，在C++中，结构体内不仅可以定义变量，也可以定义函数。
类的定义
class className
 {

	// 类体:由成员函数和成员变量组成

}; // 一定要注意后面的分号
class为定义类的关键字，ClassName为类的名字，{}中为类的主体，注意类定义结束时后面分号。
类中的元素称为类的成员:类中的数据称为**类的属性**或者成员变量:类中的函数称为类的方法或者成员
函数。

*/

//类的两种定义方式:
//类里面可以定义:1、成员变量:2、成员方法
//1.声明和定义全部放在类体中，需要注意:成员函数如果在类中定义，编译器可能会将其当成内联函数处理。
/*
class Person
{
	//显示基本信息 如果不在public 里面默认是私有的
	//如果class 改成 struct默认是公有的
	void showinfo()
	{
		cout << name << "-" << sex << "-" << age << endl;
	}
	public:
		
	public:
		char* name;
		char* sex;
		int age;
	private://私有的

};
*/

/*
类的作用域
类定义了一个新的作用域，类的所有成员都在类的作用域中。在类体外定义成员，需要使用:作用域解析符
指明成员属于哪个类域。
class Person
{
	public:
		void PrintPersonInfo();
	private:
		char name[20];
		char gender[3];
		int age;
};
//使用的时候需要指定PrintPersonInfo是属于person这个类域
void Person ::PrintPersonInfo()
{
	cout << name << gender << age << endl;
}
*/

//定义一个数据结构栈的类
class Stack
{
public:
		void Init(size_t n)
		{

		}
		void Destroy()
		{

		}
		void Pop()
		{

		}
private:
	int* a;
	size_t top;
	size_t capacity;
};



int main()
{

	return 0;
}
/*
【面试题】
面向对象的三大特性:封装、继承、多态。
在类和对象阶段，我们只研究类的封装特性，那什么是封装呢?
封装:将数据和操作数据的方法进行有机结合，隐藏对象的属性和实现细节，仅对外公开接口来和对象进行交互。
封装本质上是一种管理:我们如何管理兵马俑呢?比如如果什么都不管，兵马俑就被随意破坏了。那么我们
首先建了一座房子把兵马俑给封装起来。但是我们目的全封装起来，不让别人看。所以我们开放了售票通
道，可以买要突破封装在合理的监管机制下进去参观。类也是一样，我们使用类数据和方法都封装到一下。
不相给别人看到的，我们使用protected/private把成员封装起来。开放一些共有的成员函数对成员合理的访
问。所以封装本质是一种管理。*/