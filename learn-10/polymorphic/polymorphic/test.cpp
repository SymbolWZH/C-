#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
/*
virtual关键字，可以修饰成原函数，为了完成虚函数的重写，满足多态的条件之一。
可以在菱形继承中，去完成虚继承，解决数据冗余和二义性。
两个地方使用了同一个关键字，但是他们互相之间没有一点关联*/
using namespace std;
#if 0
//多态的两个条件
//1. 虚函数的重写
//2. 父类对象的指针或者引用去调用虚函数
//满足多态:跟指向对象有关，指向哪个对象调用就是他的虚函数
//不满足多态 : 跟调用对象的类型有关，类型是什么调用的就是谁的虚函数

//虚函数重写的两个例外:
//1.协变(基类与派生类虚函数返回值类型不同)
//派生类重写基类虚函数时，与基类虚函数返回值类型不同。即基类虚函数返回基类对象的指针或者引用。
//派生类虚函数返回派生类对象的指针或者引用时，称为协变。(了解)
class Person
{
public :
	virtual Person* ButTicket()
	{
		cout << " Person::买票 全价" << endl; 
		return nullptr;
	}
};
class Student:public Person
{
public:
	/*注意:在重写基类虚两数时，派生类的虚函数在不加virtua1关键字时，虽然也可以构成重写(因为继承后基类的
虚函数被继承下来了在派生类依旧保持虚函数属性)，但是该种写法不是很规范，不建议这样使用*/
	virtual Student* ButTicket() //Student*协变
	{ 
		cout << " Student::买票 半价" << endl;
		return nullptr;
	}
};

void Func(Person& p)//必须是指针或者引用
{
	p.ButTicket();
}
int main()
{
	Person ps;
	Student st;

	//ps.ButTicket();
	//st.ButTicket();

	Func(ps);
	Func(st);

	return 0;
}


//2.4 C++11 override和final
//从上面可以看出，C++对函数重写的要求比较严格，但是有些情况下由于疏忽，可能会导致函数名字母次序写
//反而无法构成重载，而这种错误在编译期间是不会报出的，只有在程序运行时没有得到预期结果才来debug
//会得不偿失，因此 : C++11提供了override和final两个关键字，可以帮助用户检测是否重写。
//1.final : 修饰虚函数，表示该虚函数不能再被继承
//面试题 析构函数是否需要定义成虚函数？

class Person {
public:
	//virtual void Drive() = 0;// 不需要实现，纯虚函数
	// 1、纯虚函数的作用，强制子类去完成重写
	// 2、表示抽象的类型   抽象就是在现实中没有对应的实体
	virtual ~Person()/* final一个成员函数可以被声明为final，这意味着它不能在派生类中被重写或覆盖。*/ { cout << "~Person()" << endl; }
	//// 析构函数的函数名会被处理成destructor
};
class Student :public Person {
public:
	virtual void Drive(){}
	virtual ~Student() override/*检查子类虚函数是否重写父类的虚函数*/ { cout << "~student()" << endl; }
	//// 析构函数的函数名会被处理成destructor
};

int main()
{
	Person* p = new Person;
	delete p;

	Person* p1 = new Student;
	delete p1;
	
	return 0;
}
#endif
//重载、覆盖(重写)、隐藏(重定义)的对比
//重载：       1.两个函数在同一作用域 
//             2.函数名 / 参数不同

//重写(覆盖)   1.两个函数分别在基类和派生类的作用域  
//		       2. 函数名 / 参数 / 返回值都必须相同(协变例外)
//      	   3.两个函数必须是虚函数
//概念：重写是为了重写函数实现

//重定义(隐藏) 1.两个函数分别在基类和派生类的作用域
//	           2.函数名相同
//	           3.两个基类和派生类的同名函数不构成重写就是重定义


//3.2接口继承和实现继承
//普通函数的继承是一种实现继承，派生类继承了基类函数，可以使用函数，继承的是函数的实现。虚函数的
//继承是一种接口继承，派生类继承的是基类虚函数的接口，目的是为了重写，达成多态，继承的是接口。所
//以如果不实现多态，不要把函数定义成虚函数。

//多态如何实现的指向谁就调用谁的虚函数 ?
//多态是在运行时到指向的对象的虚表中查找要调用的虚函数的地址来进行调用。

class A
{
public:
	virtual void func1() { cout << "A func1 : " << endl; }
	virtual void func2() { cout << "A func1 : " << endl; }

};
class B :public A
{
public:
	virtual void func1() { cout << "B func1 : " << endl; }
	virtual void func3() { cout << "B func3 : " << endl; }
	virtual void func4() { cout << "B func3 : " << endl; }

};
typedef	void(*VF_PTR)();
void PrintVFTable(VF_PTR* pTable)
{
	for (size_t i = 0; pTable[i]!= 0; i++)
	{
		printf("Vtable : %d : %p->", i, pTable[i]);
		cout << endl;
	}
	
}

int main()
{
	A a;
	B b;
	PrintVFTable((VF_PTR*)(*(int*)&a));
	PrintVFTable((VF_PTR*)(*(int*)&b));
	return 0;
}