#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <thread> 
#include <mutex>
#include <atomic>
#include <vector>
#include <condition_variable>
using namespace std;
//c++线程库
// windows 自己的一套API      如 : CreateThread
//Linux 使用posix的pthread    如 : pthread_create
// C++98中，如果你想写多线程的程序，即可以在Windows下跑，也可以在Linux，那么怎么办?
//#ifdef _WIN32
//	CreateThread(....)
//#else 
//	pthread_create(.....)

//C++11 线程库
// 特点:跨平台、面向对象封装的类(每个线程是一个类对象)
// 实现原理;封装库时使用了条件编译，也就是说他的底层还是分别调用了不用平台的线程API
#if 0
mutex mtx;
atomic< int> x = 0;//支持整形/浮点的原子++、-- 可以不用加锁

void Add(int n)
{
	/*mtx.lock();//串行
	for (int i = 0; i < n; i++)
	{
		++x;
	}
	
	mtx.unlock();*/

	
	for (int i = 0; i < n; i++)//并行
	{
		//mtx.lock(); //t2刚切出去，t1就解锁了，马上就把t2切回来
		++x;//t1
		//mtx.unlock();
		// 思考为什么串行还快一些?因为这里锁的粒度太小了，时间都花到切换上下文
	}

}

int main()
{
	thread f1(Add,1000000);
	thread b1(Add,1000000);

	f1.join();
	b1.join();
	
	cout << x << endl;
	return 0;
}
#endif

#if 0
int x = 0;
struct Add
{
	void operator()(int n)
	{
		for (int i = 0; i < n; i++)//并行
		{
			++x;//t1
		}
	}
};
int main()
{
	Add Add;
	thread t1(Add,1000);
	thread t2(Add,1000);

	cout << t1.get_id() << endl;
	cout << t2.get_id() << endl;


	t1.join();
	t2.join();

}
#endif



int x1()
{
	atomic<int>x = 0;
	auto add = [&x](int n) {
		for (int i = 0; i < n; i++)
		{
			++x;
		}
	};

	thread t1(add, 1000);
	thread t2([&x](int n) {for (int i = 0; i < n; i++){++x;}}, 1000);

	cout << t1.get_id() << endl;
	cout << t2.get_id() << endl;


	t1.join();
	t2.join();
	return 0;
}

int x2()
{
	atomic<int>x = 0;
	int m, n;
	cin >> m >> n;// m个线程对x加n次
	vector<thread> vthreads;

	for (int i = 0; i < m; i++)
	{
		vthreads.push_back(thread([&x](int count) {
			for (int i = 0; i < count; i++)
				++x;
			}, n));
	}

	for (auto& t : vthreads)
	{
		cout << t.get_id() << ".jion()" << endl;
		t.join();
	}
	cout << x << endl;
	return 0;
}



//拓展作业线程池
struct tack
{
	template<class Fn>
	tack(Fn) {};
};
class thread_pool
{
public:
	thread_pool( int n = 8)
		:vthreads(n){}
	
private:
	vector<thread> vthreads;
};

mutex mtx;
void f2()
{
	int N = 100;
	condition_variable cv;
	int flag = true;

	thread t1([&]() {
		for (int i = 1; i < N; i += 2)
		{
			unique_lock<mutex> lock(mtx);	//加锁 
			cv.wait(lock, [&flag]()->bool {return flag; });
			//如果返回false，wait什么也不做，一直等待 
			//并且出作用域，自动析构，不用解锁 
			cout << "线程1" << " " << i << endl;
			
			flag = false;   //线程2迟迟未创建，此时flag为false，一直wait， 
			cv.notify_one();//线程2创建以后，通知线程2执行 
		}
		});
	thread t2([&]() {
		for (int i = 2; i < N; i += 2)
		{
			unique_lock<mutex> lock(mtx);
			cv.wait(lock, [&flag]()->bool {return !flag; });//此时flag为false，！flag为true，可执行 
			cout << "线程2" << " " << i << endl;
			
			flag = true;//再去通知一号线程 
			cv.notify_one();
		}
		});
	t1.join();
	t2.join();

}
//int main()
//{
//
//	f2();
//	return 0;
//}