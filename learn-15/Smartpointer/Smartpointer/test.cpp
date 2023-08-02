#define _CRT_SECURE_NO_WARNINGS
#include "SmartPointer.hpp"

//RAII（Resource Acquisition Is Initialization）是一种利用对象生命周期来控制程序资源（如内
//存、文件句柄、网络连接、互斥量等等）的简单技术。
//在对象构造时获取资源，接着控制对资源的访问使之在对象的生命周期内始终保持有效，最后在
//对象析构的时候释放资源。借此，我们实际上把管理一份资源的责任托管给了一个对象。这种做
//法有两大好处：
//不需要显式地释放资源。
//采用这种方式，对象所需的资源在其生命期内始终保持有效
int Div()
{
	int a, b;
	cin >> a >> b;
	if (!b)
		throw invalid_argument("除0错误");

	return a / b;
}
void f1()
{
	int* p = new int;
	int* p1 = new int;
	zh::auto_ptr<int> sp(p);//智能指针
	zh::auto_ptr<int> p2 = sp;

	cout << Div() << endl;

	delete p;
}

int m1()
{
	try
	{
		f1();

	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}

//智能指针的坑
int m2()
{

	//int* p1 = new int;
	//int* p2 = p1;
	//zh::auto_ptr<int> sp1(new int);
	//zh::auto_ptr<int> sp2 = sp1;//这里会调用两次析构同一个指针


	zh::shared_ptr<int> spl(new int);
	zh::shared_ptr<int> sp2(spl);
	zh::shared_ptr<int> sp3(new int);
	zh::shared_ptr<int> sp4(sp3);
	zh::shared_ptr<int> sp5(sp3);
	spl = sp4;

	return 0;
}
// shared_ptr的拷贝赋值时线程安全问题

	//shared ptr的拷贝赋值时线程安全问题
	//shared ptr是否是线程安全的，答 : 注意这里问题的shared ptr对象拷贝和析构++/--引用计数是否是安全的  库的实现是安全的
#include <thread>
int m3()
{
	zh::shared_ptr<int> sp(new int);
	cout << sp.use_count() << endl;
	int n = 100000;

	std::thread t1([&]() {
		for (int i = 0; i < n; i++)
		{
			zh::shared_ptr<int> sp1(sp);

		}

		});
	std::thread t2([&]() {
		for (int i = 0; i < n; i++)
		{
			zh::shared_ptr<int> sp2(sp);

		}

		});

	t1.join();
	t2.join();

	return 0;
}

struct ListNode
{
	int val;
	/*ListNode* _next;
	ListNode* _prev;*/
	/*zh::shared_ptr<ListNode>  _spnext;
	zh::shared_ptr<ListNode>  _spprev;*/

	zh::weak_ptr<ListNode>  _spnext;
	zh::weak_ptr<ListNode>  _spprev;

	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
};
int m4()
{
	/*ListNode* n1 = new ListNode;
	ListNode* n2 = new ListNode;*/

	zh::shared_ptr<ListNode> spn1(new ListNode);
	zh::shared_ptr<ListNode> spn2(new ListNode);
	spn1->_spnext = spn2;
	spn2->_spprev = spn1;

	cout << spn1.use_count() << endl;
	cout << spn2.use_count() << endl;

	return 0;
}

//智能指针的历史
//C++没有gc(垃圾回收期)，申请的资源需要释放是一个问题，尤其是碰到异常安全问题，特别难处理
//稍不注意就会出现内存泄露。内存泄露到导致程序可用的内存越来越少，程序中很多操作都是需要内存的。
//那么会导致程序基本处于瘫痪状态，所以我们尽量要杜绝内存泄露问题。
//所以就发展处了基于RAI思想的智能指针，但是由于没有gc的坑，引入智能指针
//而智能指针经历了十几年发展的坑爹血泪史
//第一阶段 :
//C++98中首次推出了auto ptr，但是auto_ptr的设计存在重大缺陷，不建议使用。
//第二阶段 :
//C++官方在接下来的十几年中没有作为，有一帮牛人就生气了，觉得C++库太简陋了，所以自己
//搞一个非官方社区，写了一个库叫boost。boost库中就重新写了智能指针。注意boost库中其他很多其他实现的东西
//scoped ptr / scoped array防拷贝版本
//shared_ptr / shared_array引用计数版本
//weak_ptr
//第三阶段 :
//C++11中引入智能指针, 参考boost的实现，微改了一下。其实C++11其他类似右值引用移动语句等等也是参考boost
//unique_ptr(参考的scoped_ptr搞的)
//shared ptr
//weak_ptr
#include <memory>
#include <cstdlib>
class A
{
public:
	~A()
	{
		cout << "~A()";
	}
private:
};
template<class T>
struct DeleteArray
{
	void operator()(T* pa)
	{
		cout << "delete " << endl;

		delete[] pa;
	}
};
struct Free
{
	void operator()(void* pa)
	{
		cout << "free " << endl;

		free(pa);
	}
};
//定制删除器
struct Flocse
{
	void operator()(FILE* pa)
	{
		cout << "fclose " << endl;
		fclose(pa);
	}
};
int m5()
{
	std::shared_ptr<A> spl(new A);
	std::shared_ptr<A> sp2(new A[10], DeleteArray<A>());
	std::shared_ptr<A> sp3((A*)malloc(sizeof(A)), Free());
	std::shared_ptr<FILE> sp4(fopen("test.txt", "w"),Flocse());
	/*std::shared_ptr<FILE> sp5(fopen("test.txt", "w"), [](FILE* p)
		{fclose(p); });*/
	return 0;
}
//智能指针时RAII思想的一种应用的体现
//本质RAII就是借助构造函数和析构函数来搞事情,因为构造函数和析构函数的特点都是自动调用

//使用RAII的思想设计的锁管理守卫  c++11 实现的函数  lock_guard  unique_lock
template<class Lock>
class LockGuard
{
public:
	LockGuard(Lock& lock)
		:_lk(lock)
	{
		cout << "lock" << endl;

		_lk.lock();
	}
	~LockGuard()
	{
		cout << "~unlock" << endl;

		_lk.unlock();
	}
	LockGuard(LockGuard<Lock>&) = delete;
	LockGuard<Lock>& operator = (LockGuard<Lock>&) = delete;
private:
	Lock& _lk;//需要用引用 因为mutex不允许被拷贝
};
void f()
{
	mutex mtx;
	LockGuard<mutex> lg(mtx);
	cout << Div() << endl;
}

int m6()
{
	try
	{
		f();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}