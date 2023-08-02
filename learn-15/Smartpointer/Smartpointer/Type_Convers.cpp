#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
//类型转换
class Ac
{
public:
	virtual void f()
	{}
	int _a;
};
class Bc :public Ac
{
public:
	int _b;
};

void f_cast(Ac* pa)
{
	// 如果区分pa是指向父类，还是子类对象?
	// 如果pa是指向子类对象，则转换成功，
	// 如果pa指向父类对象则转换失败返回nullptr
	Bc* pb = dynamic_cast<Bc*>(pa);
	if (pb != nullptr)
	{
		cout << "转换成功 pa指向子类对象" << endl;
		pb->_a = 1;
		pb->_b = 2;
	}
	else
	{
		cout << "转换失败 pa指向父类对象" << endl;

	}
}
using namespace std;
int ma()
{
	int i = 0;
	double d = 8.88;
	i = d;//类型转换 c语言支持相近类型的隐士类型转换(相近类型，也就是意义相似的类型)
	cout << i << endl;


	int* p = nullptr;
	p = (int*)i; //c语言支持类型相近的强制类型转换 (不相近类型，也就是意义差别很大的类型)
	cout << p << endl;

	//C++兼容C语言留下来的隐式转换和显示转换  但是C++觉得C语言做得不规范，C++想规范一下
	//标准C++为了加强类型转换的可视性，引入了四种命名的强制类型转换操作符：
	//static_cast、reinterpret_cast、const_cast、dynamic_cast

	//1.static_cast
	d = static_cast<double>(i);     // 对应的C语言隐式类型的转换     （相近类型）
	p = reinterpret_cast<int*> (i);   // 对应的C语言大部分强制类型转换 （不相近类型）
	cout << d << endl;
	cout << p << endl;

	const int ci  = 10;//加上volatile就是20
	int* pi = const_cast<int*>(&ci);//对应c语言强制类型转换中去掉const属性的(不相近类型)
	*pi = 20;
	cout << ci << endl;//10
	// 这里打印是10是因为ci存储的内存被改了，但是ci被放进了寄存器，
	//这里去寄存器中取，还是10.本质这是由于编译器对const对象存取优化机制导致
	cout << *pi << endl;//20


	// C++中子类对象可以赋值给父类的对象、指针、引用，这个过程中会发生切片
	//这个是语法天然支持的 这个叫向上转换

	//如果是父类的指针或者引用，传给子类的指针，这个过程叫向下转换
	//这个过程有可能成功要看具体情况
	// 最后需要注意的是:dynamic_cast向下转换只能针对继承中的多态类型(父类必须包含虚函数)

	/*  dynamic_cast是通过到pa指向对象的虚表上方找到标识对象的信息
		如果是A，就不让转，返回空
		如果是B，可以转，正常返回对象地址
		所以要求A必须是多态类型
	*/
	Ac a; Bc b;
	Ac* pa = &a;
	Bc* pb = &b;
	pa = &b;
	f_cast(pa);

	//// 总结一下:尽量少用类型转换，如果要用尽量规范一点，且知道转换后会有什么影响
	return 0;
}