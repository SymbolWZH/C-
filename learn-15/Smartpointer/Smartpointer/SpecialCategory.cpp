#define _CRT_SECURE_NO_WARNINGS
//内存泄漏
//1.什么是内存泄漏？
//内存泄漏一般是我们申请了资源，这个资源不用了 但是忘记释放或者因为异常安全等问题没有释放
//2内存泄漏的危害
//如果我们申请了内存没有释放，如果进程正常结束，那么这个内存也会释放。
//一般程序碰到内存泄露，重启后就ok了。长期运行，不能随便重启的程序，碰到内存泄露危害非常大
//比如操作系统，比如服务器上的服务，威海市：这些程序长期运行，不用的内存没有释放，内存泄漏.
//可用内存越来越少，导致服务很多操作失败(因为容器存数据，打开文件，创建套接字，发送数据等等都是需要内存的)。
//
//一般后台服务器开发，如果出现内存泄漏，都是事故
//
//3如何解决内存泄漏相关问题
//a、写c / c++代码时小心谨慎一点。
//b、不好处理的地方多用智能指针等等去管理。(事前预防)
//c、如果怀疑存在内存泄漏，或者已经出现，可以使用内存泄漏工具去检测 valgrind是一个Linux下的强大工具

//1 请设计一个类，只能在堆上创建对象
// 思路：正常创建对象一定要调用构造函数，或者拷贝构造
#include <memory>
#include <iostream>
class HeapOnly
{
public:
	static HeapOnly* GetObj()
	{
		return new HeapOnly;
	}
	HeapOnly(const HeapOnly&) = delete;
private:
	//构造私有 然后定义一个静态的方法去调用
	HeapOnly()
	{}
	

};
int mx()
{
	//HeapOnly* p = HeapOnly::GetObj();//但是会内存泄漏
	std::shared_ptr<HeapOnly> sp1(HeapOnly::GetObj());
	std::shared_ptr<HeapOnly> sp2(HeapOnly::GetObj());

	return 0;
}

//2. 请设计一个类，只能在栈上创建对象
class StackOnly
{
public:
	static StackOnly GetObj()
	{
		return StackOnly();
	}
	//禁掉operator new可以把下面用new 调用拷贝构造申请对象给禁掉
	 // StackOnly obj = StackOnly::CreateObj();
	 // StackOnly* ptr3 = new StackOnly(obj);
	void* operator new(size_t size) = delete;
	void operator delete(void* p) = delete;

private:
	StackOnly()//首先不能禁用掉构造函数
	{}
};

int mt()
{
	StackOnly so = StackOnly::GetObj();
	return 0;
}

// 3.请设计一个类，不能被继承
// C++98中构造函数私有化，派生类中调不到基类的构造函数。则无法继承
class NonInherit
{
public:
	static NonInherit GetInstance()
	{
		return NonInherit();
	}
private:
	NonInherit()
	{}
};
//C++11方法
//final关键字，final修饰类，表示该类不能被继承。
class A final
{
	// ....
};

//4.请设计一个类，只能创建一个对象(单例模式)
//之前已经学过一些设计模式
//迭代器模式 -- 基于面向对象三大特性之一的 封装设计出来的，用一个迭代器类封装以后，
//不暴露容器的结构的情况下，统一的方式访问修改容器中的数据。
// 适配器模式 -- 体现的是一种复用
//还有一些常见的设计模式如:工厂模式、装饰器模式、观察者模式、单例模式...
// 一个类只能在全局(进程中)只有一个实例对象。
//什么场景下使用 ? 比如一个进程中有一个内存池，进程中的多线程需要内存都要到这个内存池
//中取，那么这个内存池的类就可以设计单例模式。
 

//类的名称是随着你的场景给的，比如你的是内存池，那么你就定义成MemoryPool
#include <thread>
#include <vector>
#include <Windows.h>
#include <mutex>

//懒汉模式 --- 第一次获取对象时再创建对象
namespace lazy_man
{
	class Singleton
	{
	public:
		static Singleton* GetInstance()
		{
			::Sleep(1000);  //增加没加锁时出现线程不安全的条件(2个以上线程同时过了判断条件)
			//_mtx.lock();
			if (_pinst == nullptr) // 双检查
			{
				std::unique_lock<std::mutex>lock(_mtx);//加锁是为了保护第一次
				if (_pinst == nullptr)
					_pinst = new Singleton;
				//_mtx.unlock();
			}
			return _pinst;
		}
		//c++ 11
		//Singleton(const Singleton&) = delete;
		Singleton& operator=(Singleton const&) = delete;
		static void DelInstance()
		{
			//std::unique_lock<std::mutex>lock(_mtx);
			delete _pinst;
			_pinst = nullptr;
		}
	private:
		Singleton() {};

		static Singleton* _pinst;
		static std::mutex _mtx;
	};
	Singleton* Singleton::_pinst = nullptr;
	std::mutex Singleton::_mtx;
	//1.如果需要手动释放单例对象，可以调用DelInstance
	//2.如果需要程序结束 正常释放单例对象可以加入下面的设计
	class GC
	{
	public:
		~GC()
		{
			Singleton::DelInstance();
		}
	};
	static GC gc;
}

int ms()
{
//	Singleton s1;
//	Singleton s2;
	/*std::cout << Singleton::GetInstance() << std::endl;;
	std::cout << Singleton::GetInstance() << std::endl;
	std::cout << Singleton::GetInstance() << std::endl;*/

	std::vector<std::thread> vthreads;

	int n = 8;

	for (int i = 0; i < n; i++)
	{
		vthreads.push_back(std::thread([]() {

			std::cout << lazy_man::Singleton::GetInstance() << std::endl;
			}));
	}
	for (auto& e : vthreads)
	{
		e.join();
	}
	return 0;
}
// 如果这个单例对象在多线程高并发环境下频繁使用，性能要求较高而且可能不安全，那么显然使用饿汉模式来避免资源竞争，提高响应速度更好。
//饿汉模式---  一开始(main函数之前)就创建对象
namespace Hunary_man
{
	class Singleton
	{
	public:
		static Singleton* GetInstance()
		{
			return &_inst;
		}
		Singleton(const Singleton&) = delete;

	private:
		Singleton(){}
		static Singleton _inst;

	};

	Singleton Singleton::_inst;//static对象是在main函数之前创建的
}
//思考一下饿汉和懒汉优缺点是什么，如果用你会选谁?
/*
总结对比一下饿汉和懒汉的区别
1、懒汉模式需要考虑线程安全和释放的问题，实现相对更复杂，饿汉模式不存在以上问题，实现简单
2、懒汉是一种懒加载模式需要时在初始化创建对象，不会影响程序的启动。饿汉模式则相反，程序启动
阶段就创建初始化实力对象，会导致程序启动慢，影响体验。
3.如果有多个单例类，假设有依赖关系（B依赖A），要求A单例先创建初始化，B单例再创建初始化，
那么就不是饿汉，因为无法保证创建初始化的顺序，这时用懒汉我们就可以手动控制

// 总结一下：实际中懒汉模式还是更实用一些
*/
