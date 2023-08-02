#define _CRT_SECURE_NO_WARNINGS
#include "SmartPointer.hpp"

//RAII��Resource Acquisition Is Initialization����һ�����ö����������������Ƴ�����Դ������
//�桢�ļ�������������ӡ��������ȵȣ��ļ򵥼�����
//�ڶ�����ʱ��ȡ��Դ�����ſ��ƶ���Դ�ķ���ʹ֮�ڶ��������������ʼ�ձ�����Ч�������
//����������ʱ���ͷ���Դ����ˣ�����ʵ���ϰѹ���һ����Դ�������йܸ���һ������������
//��������ô���
//����Ҫ��ʽ���ͷ���Դ��
//�������ַ�ʽ�������������Դ������������ʼ�ձ�����Ч
int Div()
{
	int a, b;
	cin >> a >> b;
	if (!b)
		throw invalid_argument("��0����");

	return a / b;
}
void f1()
{
	int* p = new int;
	int* p1 = new int;
	zh::auto_ptr<int> sp(p);//����ָ��
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

//����ָ��Ŀ�
int m2()
{

	//int* p1 = new int;
	//int* p2 = p1;
	//zh::auto_ptr<int> sp1(new int);
	//zh::auto_ptr<int> sp2 = sp1;//����������������ͬһ��ָ��


	zh::shared_ptr<int> spl(new int);
	zh::shared_ptr<int> sp2(spl);
	zh::shared_ptr<int> sp3(new int);
	zh::shared_ptr<int> sp4(sp3);
	zh::shared_ptr<int> sp5(sp3);
	spl = sp4;

	return 0;
}
// shared_ptr�Ŀ�����ֵʱ�̰߳�ȫ����

	//shared ptr�Ŀ�����ֵʱ�̰߳�ȫ����
	//shared ptr�Ƿ����̰߳�ȫ�ģ��� : ע�����������shared ptr���󿽱�������++/--���ü����Ƿ��ǰ�ȫ��  ���ʵ���ǰ�ȫ��
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

//����ָ�����ʷ
//C++û��gc(����������)���������Դ��Ҫ�ͷ���һ�����⣬�����������쳣��ȫ���⣬�ر��Ѵ���
//�Բ�ע��ͻ�����ڴ�й¶���ڴ�й¶�����³�����õ��ڴ�Խ��Խ�٣������кܶ����������Ҫ�ڴ�ġ�
//��ô�ᵼ�³����������̱��״̬���������Ǿ���Ҫ�ž��ڴ�й¶���⡣
//���Ծͷ�չ���˻���RAI˼�������ָ�룬��������û��gc�Ŀӣ���������ָ��
//������ָ�뾭����ʮ���귢չ�Ŀӵ�Ѫ��ʷ
//��һ�׶� :
//C++98���״��Ƴ���auto ptr������auto_ptr����ƴ����ش�ȱ�ݣ�������ʹ�á�
//�ڶ��׶� :
//C++�ٷ��ڽ�������ʮ������û����Ϊ����һ��ţ�˾������ˣ�����C++��̫��ª�ˣ������Լ�
//��һ���ǹٷ�������д��һ�����boost��boost���о�����д������ָ�롣ע��boost���������ܶ�����ʵ�ֵĶ���
//scoped ptr / scoped array�������汾
//shared_ptr / shared_array���ü����汾
//weak_ptr
//�����׶� :
//C++11����������ָ��, �ο�boost��ʵ�֣�΢����һ�¡���ʵC++11����������ֵ�����ƶ����ȵ�Ҳ�ǲο�boost
//unique_ptr(�ο���scoped_ptr���)
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
//����ɾ����
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
//����ָ��ʱRAII˼���һ��Ӧ�õ�����
//����RAII���ǽ������캯��������������������,��Ϊ���캯���������������ص㶼���Զ�����

//ʹ��RAII��˼����Ƶ�����������  c++11 ʵ�ֵĺ���  lock_guard  unique_lock
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
	Lock& _lk;//��Ҫ������ ��Ϊmutex����������
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