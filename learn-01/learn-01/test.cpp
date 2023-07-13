#define _CRT_SECURE_NO_WARNINGS
#include <iostream>//c++的输入输出流库
//在日常练习中，不在乎跟库命名冲突
using namespace std; // C++库所有的东西都是放到std命名空间中的
//工程项目中通常比较推荐这种用
//using std::cout;
//using std::endl;

namespace N
{
	int a = 0;
	int b = 20;
	int Add(int left, int right)
	{
		return left + right;
	}
	int Sub(int left, int right)
	{
		return left - right;
	}
}
//命名空间的使用有三种方式:
//1·加命名空间名称及作用域限定符
int main()
{
	printf("%d\n",N::a);
	return 0;
}
//2 使用using 将命名空间中成员引入
using N::b;
int main()
{
	printf("%d\n", N::a);
	printf("%d\n", b);
}
////3 使用using namespace将命名空间名称引入
using namespace N;
int main()
{
	//cout 自动识别类型  类型重载
	cout << "hello world\n" << endl;//cout输出流对象  endl输入一个换行符
	double d = 1.1;
	cin  >> d;//cin输入流对象 雷士scanf
	cout << "hello world\n" << d<<endl;
	printf("%d\n", a);
	printf("%d\n", b);
}

//缺省参数概念
//缺省参数是声明或定义函数时为函数的参数指定一个默认值。在调用该函数时，如果没有指定实参则采用该
//默认值，否则使用指定的实参。
void Func(int a = 0)
{
	cout << a << endl;
}
//4.2缺省参数分类
//·全缺省参数
void TestFunc(int a = 10, int b = 20, int c = 30)
{

	cout << "a =" << a << endl;
	cout << "b =" << b << endl;
	cout << "c=" << c << endl;
}

//·半缺省参数 缺省部分参数   缺省参数必须连续从右往左
//  没有缺省的 参数必须传递
void TestFunc1(int a,int b = 10, int c = 20)
{

	cout << "a=" << a <<endl;
	cout << "b =" << b << endl;
	cout << "c =" << c << endl;
}
//函数重载 函数名相同，参数不同(类型or个数or顺序不同)
//返回值没有要求 但是只是返回值不同 不能构成重载
/*重载:面试问题:
1、什么函数重载
2、C + 是如何支持函数重载的 ? 为什么C言不支持？*/
/*1. 预处理 ->
* 2. 编译 ->
* 3. 汇编
* 4. 链接
*/
int Add(int left, int right)
{
	return left + right;
}
double Add(double left, double right)
{
	return left + right;
}
long Add(long left, long right)
{
	return left + right;
}
#if 0
5.3 externC
有时候在C++工程中可能需要将某些函数按照C的风格来编译，在函数前加extern"C"意思是告诉编译器，
将该函数按照C语言规则来编译。比如 : tcmalloc是google用C++实现的一个项目，他提供tcmallc()和tcfree
两个接口来使用，但如果是C就就没办法使用，那么他就使用externC来解决。
示例在.c文件中实现正常声明 double Add(double left, double right);
在.h文件中实现时  extern "C" double Add(double left, double right);
#endif

#if 0 
6. 引用
6.1引用概念
引用不是新定义一个变量，而是给已存在变量取了一个别名，编译器不会为引用变量开辟内存空间，它和它
引用的变量共用同一块内存空间。
比如 : 李逵，在家称为"铁牛"，江湖上人称"黑旋风"
int a = 1;
int& ra = a;//raa引用，引用也就是别名，a再取了一个名称
ra = 2;
cout << ra << endl;//2
cout << &ra << endl;//00EFFC78

int& b;
2 引用特性
1.引用在定义时必须初始化
2.一个变量可以有多个引用
3.引用一旦引用一个实体，再不能引用其他实体
int a = 1;
//int& b;
//引用必须在定义时初始化
int& c = a;
int d = 2;
c = d;// 分析:这里是c成了d引用?no还是将d值给cok


const int a = 0:
// int& b =a:// b的类型是int，编译不通过，原因:a是只读，b的类型是int，也就是可读可写的。
const int& b = a :
	int c = 1; I
	int& d = c;
const int& e = c// 行不行?可以->c只是可读可写，e变成别名只读
// 总结:引用取别名时，变量访问的权限可以缩小，不能放大
#endif


int main()
{
	Func();//没有传参使用参数默认值
	Func(10);

	//调用时，如果要传参必须从左往右依次传参
	TestFunc();
	TestFunc(10);      //全缺省可以转入任意个实参
	TestFunc(10, 20);
	TestFunc(10, 20,30);
	
	return 0;
}

