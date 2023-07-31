#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <thread> 
#include <mutex>
#include <atomic>
#include <vector>
#include <condition_variable>
using namespace std;
//c++�߳̿�
// windows �Լ���һ��API      �� : CreateThread
//Linux ʹ��posix��pthread    �� : pthread_create
// C++98�У��������д���̵߳ĳ��򣬼�������Windows���ܣ�Ҳ������Linux����ô��ô��?
//#ifdef _WIN32
//	CreateThread(....)
//#else 
//	pthread_create(.....)

//C++11 �߳̿�
// �ص�:��ƽ̨����������װ����(ÿ���߳���һ�������)
// ʵ��ԭ��;��װ��ʱʹ�����������룬Ҳ����˵���ĵײ㻹�Ƿֱ�����˲���ƽ̨���߳�API
#if 0
mutex mtx;
atomic< int> x = 0;//֧������/�����ԭ��++��-- ���Բ��ü���

void Add(int n)
{
	/*mtx.lock();//����
	for (int i = 0; i < n; i++)
	{
		++x;
	}
	
	mtx.unlock();*/

	
	for (int i = 0; i < n; i++)//����
	{
		//mtx.lock(); //t2���г�ȥ��t1�ͽ����ˣ����ϾͰ�t2�л���
		++x;//t1
		//mtx.unlock();
		// ˼��Ϊʲô���л���һЩ?��Ϊ������������̫С�ˣ�ʱ�䶼�����л�������
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
		for (int i = 0; i < n; i++)//����
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
	cin >> m >> n;// m���̶߳�x��n��
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



//��չ��ҵ�̳߳�
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
			unique_lock<mutex> lock(mtx);	//���� 
			cv.wait(lock, [&flag]()->bool {return flag; });
			//�������false��waitʲôҲ������һֱ�ȴ� 
			//���ҳ��������Զ����������ý��� 
			cout << "�߳�1" << " " << i << endl;
			
			flag = false;   //�߳�2�ٳ�δ��������ʱflagΪfalse��һֱwait�� 
			cv.notify_one();//�߳�2�����Ժ�֪ͨ�߳�2ִ�� 
		}
		});
	thread t2([&]() {
		for (int i = 2; i < N; i += 2)
		{
			unique_lock<mutex> lock(mtx);
			cv.wait(lock, [&flag]()->bool {return !flag; });//��ʱflagΪfalse����flagΪtrue����ִ�� 
			cout << "�߳�2" << " " << i << endl;
			
			flag = true;//��ȥ֪ͨһ���߳� 
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