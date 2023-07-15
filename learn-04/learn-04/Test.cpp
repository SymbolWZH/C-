#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include <cstdio>
#include <assert.h>
#if 0
//4. 友元
//友元分为 : 友元函数和友元类
//友元提供了一种突破封装的方式，有时提供了便利。但是友元会增加耦合度，破坏了封装，所以友元不宜多用。
//4.1 友元函数
//问题 : 现在我们尝试去重载operator << ，然后发现我们没办法将operator << 重载成成员函数。因为cout的输
//出流对象和隐含的this指针在抢占第一个参数的位置。this指针默认是第一个参数也就是左操作数了。但是实
//际使用中cout需要是第一个形参对象，才能正常使用。所以我们要将operator << 重载成全局函数。但是这样
//的话，又会导致类外没办法访问成员，那么这里就需要友元来解决。operator > 同理。

class Date
{
	friend void f(Date& d);//友元函数
	friend  ostream& operator << (ostream& out, const Date& d);
	friend istream& operator >> (istream& in,  Date& d);
public:
	

private:
	int a = 0;
	int b = 1;
};
void f(Date& d)
{
	cout << d.a <<d.b << endl;
}
ostream& operator << (ostream& out,const Date& d)//友元函数没有默认的
{
	out << d.a << d.b << endl;
	return out;
}
istream& operator >> (istream& in,  Date& d)//友元函数没有默认的
{
	in >> d.a >> d.b;
	return in;
}
int main()
{
	Date a;
	f(a);
	// cout-> ostream
	// cin -> istream
	
	cin >> a;
	cout << a; // operator << (cout,a);
}
//class Sum
//{
//public:
//    Sum()
//    {
//        total += i;
//        ++i;
//    }
//    static void SumInIt()
//    {
//        total = 0;
//        i = 1;
//    }
//    static int GetSum()
//    {
//        return total;
//    }
//private:
//    static int total;
//    static int i;
//};
//int Sum::total = 0;
//int Sum::i = 1;
//class Solution {
//public:
//    int Sum_Solution(int n) 
//    {
//        Sum::SumInIt();
//        Sum* p = new Sum[n];
//        return Sum::GetSum();
//    }
//private:
//};
//
//
//
//
//int main()
//{
//    Solution sol;
//    cout <<sol.Sum_Solution(5) << endl;
//    cout << sol.Sum_Solution(5) << endl;
//
//	return 0;
//}


//再次理解封装
//C++是基于面向对象的程序，面向对象有三大特性即:封装、继承、多态。
//C++通过类，将一个对象的属性与行为结合在一起，使其更符合人们对于一件事物的认知，将属于该对象的所
//有东西打包在一起 : 通过访问限定符选择性的将其部分功能开放出来与其他对象进行交互，而对于对象内部
//的一些实现细节，外部用户不需要知道，知道了有些情况下也没用，反而增加了使用或者维护的难度，让整
//个事情复杂化。
#endif
#if 0
int globalVar = 1;
static int staticGlobalVar = 1;
void Test()
{
	static int staticVar = 1;
	int localvar = 1; 

	int num1[10] = { 1,2,3,4 };
	char char2[] = "abcd";
	char* pChar3 = char2;
	int* ptr1 = (int*)malloc(sizeof(int) * 4);
	int* ptr2 = (int*)calloc(4, sizeof(int));
	int* ptr3 = (int*)realloc(ptr2, sizeof(int) * 4);
	free(ptr1);
	free(ptr3);
}
//1.选择题:
//选项:A.栈B.堆 c.数据段 D.代码段
//globalvar在哪里 __   staticGlobalvar在哪里 __
//staticvar在哪里 __    localvar在哪里 __
//num1 在哪里 __
//
//char2在哪里 __      *char2在哪里 __
//pChar3在哪里 __     * pChar3在哪里 __
//ptr1在哪里 __		* ptr1在哪里 __
//
//2.填空题 :
//sizeof(num1) = __;
//sizeof(char2) = ___;   strlen(char2) = _;
//sizeof(pChar3) = ___;   strlen(pChar) = ____;

//C++之内存管理
int globalVar = 1;
static int staticGlobalVar = 1;
void Test()
{
	static int staticVar = 1;
	int localvar = 1;

	int num1[10] = { 1,2,3,4 };
	char char2[] = "abcd";
	char* pChar3 = "abcd";
	int* ptr1 = (int*)malloc(sizeof(int) * 4);
	int* ptr2 = (int*)calloc(4, sizeof(int));
	int* ptr3 = (int*)realloc(ptr2, sizeof(int) * 4);
	free(ptr1);
	free(ptr3);
}
//1.选择题:
//选项:A.栈 B.堆 C.数据段 D.代码段
//globalvar在哪里 __   staticGlobalvar在哪里 __
//staticvar在哪里 __    localvar在哪里 __
//num1 在哪里 __
//
//char2在哪里 __ * char2在哪里 __
//pChar3在哪里 __ * pChar3在哪里 __
//ptr1在哪里 __ * ptr1在哪里 __
//
//2.填空题 :
//sizeof(num1) = __;
//sizeof(char2) = ___;   strlen(char2) = _;
//sizeof(pChar3) = ___;   strlen(pChar) = ____;
//
//先不要往下面看自己尝试着做一下，看能够做对几个，对自己学习检验。
//
//知识点很多一定要细心看
//
//1 - 3. globalvar在哪里 _C_   staticGlobalvar在哪里 _C_ staticvar在哪里 _C_ 考察点如下
//
//通常考察的面试题 : 全局变量和static变量有什么区别 ?
//
//全局变量，静态变量是放在数据段中（C语言的角度叫静态区），所以globalvar放在 C 中， staticGlobalvar放在C中， staticvar是局部的静态变量也是属于静态变量所以也放在C中，   他们三个有共同点是整个程序运行期间都在 ，区别是全局变量globalvar，静态变量staticGlobalvar在main函数之前会初始化且作用域是全局的在哪都能使用，局部静态变量staticvar会在运行到main函数再初始化且作用域是在Test函数中只能在Test函数中使用。而globalvar和staticGlobalvar的区别在于链接属性不一样，globalvar是所有文件中可见，而staticGlobalvar只在当前文件可见
//
//4 - 5. localvar在哪里 _A_   num1 在哪里 _A_
//
//localvar是声明的局部变量所以存在A(栈)中的，num1是一个局部声明的数组所以也存在A(栈)中的
//
//6 - 11， char2在哪里 _A_ * char2在哪里 _A_                 pChar3在哪里 _A_
//
//* pChar3在哪里 _D_                  ptr1在哪里 _A_ * ptr1在哪里 _B_
//
//char2是声明在栈上的字符数组放入abcd + '\0'开了5个字节，所以也存在A(栈)中的， * char2是取地址所以取得是首字符的地址，这个数组存在局部所以也存在A(栈)中的, pChar3是一个指针变量也是一个局部变量所以也存在A(栈)中的, * pChar3中pChar3存的是一个字符串常量的地址，* pChar3指向这个地址的内容，所以* pChar3在D(代码段)中。ptr1在哪里在哪里非常容易混淆，大家会看后面开辟了空间所以会以为在堆中，ptr1是int* ptr只是 = 前面声明的一个局部变量的指针，所以也存在A(栈)中的, 而* ptr1指向的内容才是开辟出来的，所以是在B(堆)中
//
//总结：
//
//全局变量，静态变量是放在数据段中的，声明的局部变量、字符、字符数组（char* ）、取地址（* ptr）存在栈中的，取地址指向的地址是开辟出来的就在堆中，不然就存在代码段中，
//
//2.填空题 :
//sizeof(num1) = _40_;
//sizeof(char2) = _5__;   strlen(char2) = _4__;
//sizeof(pChar3) = _4、8__;   strlen(pChar) = _4___;  sizeof(ptr1) = ___;
//
//sizeof是计算字节数的
//
//sizeof(num1) 中num1[10] = { 1,2,3,4 }；虽然只有4初始化，但是它开辟了10个整型所以是40个字节。
//sizeof(char2)中char char2[] = "abcd"; 是4个字节但是还有\0所以是5个字节。
//strlen(char2)中strlen是遇到\0结束所以是4个字节。
//sizeof(pChar3) 中char * pChar3 = "abcd"; pChar3是一个指针，所以是4或8，区分32 / 64位。
//strlen(pChar)同样是遇到\0结束所以是4个字节。
//sizeof(ptr1)中int * ptr1 = (int*)malloc(sizeof(int) * 4); ptr1是一个指针，所以也是4或8，区分32 / 64位。

#endif

#if 0
//C语言和C++中动态内存管理方式
void Test()
{
int* p1 = (int*)malloc(sizeof(int));
free(p1);
// 1.malloc/calloc/realloc的区别是什么?
int* p2 = (int*)calloc(4, sizeof(int));
int* p3 = (int*)realloc(p2, sizeof(int) * 10);
// 这里需要free(p2)吗?//不需要p2的空间已经扩容给p3了直接free掉p3就行
free(p3)
}
malloc / calloc / realloc区别 ?

malloc是申请一个内存空间，calloc申请一个内存空间并初始化为0，realloc是对已有的内存空间进行扩容。

C + 内存管理方式

C言内存管理方式在C++中可以继续使用，但有些地方就无能为力而且使用起来比较麻烦，因此C++又提出了自己的内存管理方式:通过new / delete作符进行动态内存管理

int main()
{
	// C 函数
	int* p1 = (int*)malloc(sizeof(int));
	int* p3 = (int*)malloc(sizeof(int) * 10);

	free(pl);
	free(p3);

	// C++ 操作符
	//int* p2 = new int;
	int* p2 = new int(10);// 申请一个int4个字节空间，初始化成10
	int* p4 = new int[10];// 申请10个int的40个字节空间
	delete p2;
	delete[] p4;
	return 0;
}
既然c语言中已经malloc和free，new和delete的意义何在呢？

对于上面内置类型，他们的效果是一样的。申请空间
对于自定义类型，他们的效果是不一样的。malloc申请空间、new申请空间 + 构造函数初始化
free释放空间，delete析构函数 + 释放空间
class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
}

int main()
{
	int* p1 = new int;
	int* p2 = (int*)malloc(sizeof(int));
}
上面内置类型，他们的效果是一样的。都是开辟了空间
对于自定义类型，举例说明，

class A
{
public:
	A()
	{
		_a = 0;
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
private:
	int _a;
}

int main()
{
	int* p1 = new int;
	int* p2 = (int*)malloc(sizeof(int));

	A* p2 = (A*)malloc(sizeof(A));  //申请空间
	A* p3 = new A;                  //申请空间 + 构造函数初始化

	free(p3);                       //释放空间
	delete p4;                      //析构函数 + 释放空间

	return 0;
}


#endif


#if 0
//C++内存泄漏如何解决
什么是内存泄漏呢？

内存泄漏指因为疏忽或错误造成程序未能释放已经不再使用的内存的情况。内存泄漏并不是指内存在物理上的消失，而是应用程序分配某段内存后，因为设计错误，失去了对该段内存的控制，因而
造成了内存的浪费。
内存泄漏的危害 : 长期运行的程序出现内存泄漏，影响很大，如操作系统，后台服务等等出现内存泄漏会导致响应越来越慢，最终卡死。

比如我申请了1个G的内存空间，如果忘记了或其他原因释放指向的空间，就会导致内存泄漏。

int main()
{
	char* p = new char[1024 * 1024 * 1024];
	//没有释放 就会内存泄漏
	//delete p;
	return 0;
}
如何避免内存泄漏
1.工程前期良好的设计规范，养成良好的编码规范，申请的内存空间记着匹配的去释放。ps:这个理想状态。但是如果碰上异常时，就算注意释放了，还是可能会出问题。需要下一条智能指针来管理才有保证。
2.采用RAII思想或者智能指针来管理资源。
3.有些公司内部规范使用内部实现的私有内存管理库。这套库自带内存泄漏检测的功能选项。
4.出问题了使用内存泄漏工具检测。ps; 不过很多工具都不够靠谱，或者收费昂贵。
总结一下 :
内存泄漏非常常见，解决方案分为两种:1、事前预防型。如智能指针等。2、事后查错型。如泄漏检测工具。

相关面试题：如何一次在堆上申请4G的内存？
//将程序编译成x64的进程，运行下面的程序试试?
#include <iostream>
using namespace std;
//x32位只有4g的内存空间 所以申请不了 必须得换成64位的
int main()
{
	size_t n = 2;
	void* p = new char[n * 1024 * 1024 * 1024];
	cout << "new:" << p << endl;
	return 0;
}
#endif

//基础语法(如:函数重载)+类和对象(4个重要默认成员函数+运算符重载)+泛型编程:模板
//解决一些c言解决得不好或者没有解决的问题。
//1.忘记初始化和销毁   构造函数 + 析构函数
//2.没有封装，谁都可以修改结构体的数据 ->类 + 访问限定符
//3.如果想同时定义两个栈，一个栈存int一个栈都double做不到->模板
#if 0
int Add(int left, int right)
{
	return left + right;
}
template<class T>
T Add(const T& left, const T& right)
{
	return left + right;
}
int main()
{
	int a = 5, b = 10;
	double c = 20, d = 30;
	//隐式实例化
	Add(a, b);
	Add(c, d);
	//显式实例化
	Add<int>(a, b);
	Add<double>(a, b);//可以强转
}
#endif

#if 0 
template<class T>
class vector //动态增长的数组
{
public:
	vector()
	:_a(nullptr),_size(0),_capacity(0)
	{

	}
	vector(size_t n)//带参
		:_a(new T[n]), _size(0), _capacity(0)
	{

	}
	~vector()
	{
		delete[] _a;
		_a = nullptr;
		_size = _capacity = 0;
	}
	void Push_Back(const T& x);//能用引用就用引用 减少拷贝
	
	void Pop_Back();

	size_t size()
	{
		return _size;
	}
	T& operator[](size_t& i)//引用传参 1、修改传递的实参比如swap      2、减少拷贝
	{					    //引用传返回值:2、修改返回对象如operator] 2、减少拷贝
		assert(i < _size);
		return _a[i];
	}
private:
	T* _a;
	size_t _size;
	size_t _capacity;
};
template<class T>
void vector<T>::Pop_Back()
{
	assert(_size > 0);
		--size;
}
template<class T>
void vector<T>::Push_Back(const T& x)
{
	//如果空间不够需要进行增容
	if (_size == _capacity)
	{
		size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
		T* tmp = new T[newcapacity];
		if (_a)
		{
			memcpy(tmp, _a, sizeof(T) * _size);
			delete[] _a;
		}
		_a = tmp;
		_capacity = newcapacity;
	}
	_a[_size] = x;
	++_size;
}
#endif
//int main()
//{
//	vector<int> v;
//	v.Push_Back(1);
//	v.Push_Back(2);
//	v.Push_Back(3);
//	v.Push_Back(4);
//
//	for (size_t i = 0; i < v.size(); i++)
//	{
//		v[i] *= 2;
//		cout << v[i] << " ";
//	}
//	cout << endl;
//
//	return 0;
//}


//字符串转成整型
int firstUniqChar(string s) {
	int count[26] = { 0 };
	for (auto ch : s)
	{
		count[ch - 'a']++;
	}
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (count[s[i] - 'a'] == 1)
			return i;
	}
	return -1;
}

int main()
{
	string s = "loveleetcode";
	firstUniqChar(s);
}