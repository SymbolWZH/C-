#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;
#if 0 
//继承  ：核心是类之间的复用	
/*
1.1继承的概念
继承(inheritance)机制是面向对象程序设计使代码可以复用的最重要的手段，
它允许程序员在保持原有类特性的基础上
进行扩展，增加功能，这样产生新的类，称派生类。
继承呈现了面向对象程序设计的层次结构，体现了由简单到复杂的认知过程。
以前我们接触的复用都是函数复用，继承是类设计层次的复用。
*/
class Person
{
public:
	void Print() 
	{
		cout << "name:" << name << endl;
		cout << "age:" << age << endl;
	}
protected://受保护的
	string name = "peter";//姓名
	int age = 18;//年龄
};
//继承后父类的Person的成员(成员函数+成员变量)都会变成子类的一部分
//。这里体现出了Student和Teacher复用

class Student/*派生类或子类*/ : public/*继承方式*/ Person/*基类*/
{
public:
	void print()
	{
		
		//类中的私有和保护在当前类没差别
		//在继承的后的子类中有差别，private的在子类中不可见
		cout << name << endl;
	}
protected:
	int stuid;//学号
};
class Teacher : public Person
{
protected:
	int jobid;//工号
};

/*
1.2.3继承基类成员访问方式的变化
类成员/继承方式-----------public继承---------------protected继承----------private继承
基类的public成员      派生类的public成员       派生类的protected成员      派生类的private成员
基类的protected成员   派生类的protected成员    派生类的protected成员      派生类的private成员
基类的private成员     在派生类中不可见         在派生类中不可见           在派生类中不可见*/
int main()
{
	Student s;
	Teacher t;
	s.print();
	t.Print();


	return 0;
}

/*
总结:
1.基类private成员在派生类中无论以什么方式继承都是不可见的。这里的不可见是指基类的私有成员还是
被继承到了派生类对象中，但是语法上限制派生类对象不管在类里面还是类外面都不能去访问它。
2.基类private成员在派生类中是不能被访问，如果基类成员不想在类外直接被访问，但需要在派生类中能
访问，就定义为protected，可以看出保护成员限定符是因继承才出现的。
3.实际上面的表格我们进行一下总结会发现，基类的私有成员在子类都是不可见。基类的其他成员在子类的
访问方式==Min(成员在基类的访问限定符，继承方式)，public>protected>private.
4.使用关键字class时默认的继承方式是private，使用struct时默认的继承方式是public，不过最好显示的写
出继承方式。
5.在实际运用中一般使用都是public继承，几乎很少使用protetced/private继承，也不提倡使用
protetced/private继承，因为protetced/private继承下来的成员都只能在派生类的类里面使用，实际中
扩展维护性不强。

*/
#endif



#if 0
/*
2.基类和派生类对象赋值转换
·派生类对象可以赋值给基类的对象/基类的指针/基类的引用。这里有个形象的说法叫切片或者切割。
审意把派生类中父类那部分切来赋值过去。
·基类对象不能赋值给派生类对象
。基类的指针可以通过强制类型转换赋值给派生类的指针。但是必须是基类的指针是指向派生类对象时才是
安全的。这里基类如果是多态类型，可以使用RTTI(Run-TimeType Information)的dynamic cast来进行
识别后进行安全转换。

*/

class Person
{
public:
	~Person() {};
protected://受保护的
	string name = "peter";//姓名
	string  sex ;//性别
	int age;
};
class Student/*派生类或子类*/ : public/*继承方式*/ Person/*基类*/
{
public:
	int stuid;//学号
	////子类的析构函数和父类的析构函数构成隐藏，因为他们的名字会被编译器统一处理
	~Student() {
		Person::~Person();//不需要显式调用 结束后会自动调用父类
	};
protected:
	
};

int main()
{
	Person p;
	Student s;
	//子类和父类之间的赋值兼容规则
	// 1. 子类对象可以赋值给赋值对象/指针/引用
	p = s;
	Person* ptr = &s;
	Person& ref = s;

	return 0;
}
#endif

#if 0
/*
3.继承中的作用域
1.在继承体系中基类和派生类都有独立的作用域。
2.当子类和父类中有同名成员，子类成员将屏蔽父类的同名成员直接访问，这种情况叫隐藏，也叫重定义。
(在子类成员函数中，可以使用基类::基类成员显示访问)
3.需要注意的是如果是成员函数的隐藏，只需要函数名相同就构成隐藏。
4.注意在实际中在继承体系里面最好不要定义同名的成员。
*/
//Student的_num和Person的_num构成隐藏关系，
//可以看出这样代码虽然能跑，但是非常容易混淆
class Person
{
protected:
	string _name = "小李子";// 姓名
	int _num = 111;// 身份证号
};
class Student : public Person
{
public:
	void Print()
	{
		cout << "姓名:" << _name << endl;
		cout << "同名需要访问父类加命名空间:" << Person::_num << endl; 
		cout << "学号:" << _num << endl;

	}
protected:
	int _num = 999;// 学号
};
int main()
{
	Student s;
	s.Print();// 999 优先访问自己的类里面找
	return 0;
}

#endif


//如何设计一个不能被继承的类 把他私有化构造函数

//class A
//{
//private:
//	A(){}
//};
//
//class B :public A
//{};

class C{};
class D
{
	C c;//C和D的关系就是组合 组合的类耦合度更低 继承的类是一种高耦合
};
//面试题:C++的缺陷有哪些 ? 多继承就是一个问题 - 》菱形继承 - 》虚继承 - 》底层结构的对象模型非常复杂，且有一定效率损失
//什么是菱形继承 ? 菱形继承问题是什么 ? 如何解决 ? ->虚继承->解决原理是什么 ?
//1.什么是菱形继承 ? 菱形继承的问题是什么 ?
//2.什么是菱形虚拟继承 ? 如何解决数据冗余和二义性的
//3.继承和组合的区别 ? 什么时候用继承 ? 什么时候用组合 ?