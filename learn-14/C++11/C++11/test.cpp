#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <initializer_list>
using namespace std;

#if 0 
//�б��ʼ������������Ҫ�ܿ�����ʵ��������õ�Ҳ���ࡣ
class Point
{
public:
	Point(int x = 0, int y = 0) :_x(x), _y(y) {}
private:
	int _x;
	int _y;
};
int main()
{
	//c++ 11
	int y{ 2 };
	vector<int> v1{ 1,2,3,4,5 };
	vector<int> v2 = { 1,2,3,4,5 };

	list<int> l1{ 1,2,3,4,5 };
	list<int> l2 = { 1,2,3,4,5 };

	map<string, int> m1{ {"ƻ��",1},{"����",2},{"�㽶",3}};
	map<string, int> m2 = { {"ƻ��",1},{"����",2},{"�㽶",3} };

	Point p1(1, 2);
	Point p2{ 1, 2 };
	Point p3 = { 1, 2 };

	auto il1 = { 1,2,3 };
	initializer_list<int> il2 = { 1,2,3 };

	return 0;
}
#endif
#if 0
// �����Ƶ�  ����RTTI  run time type Identification
int main()
{
	int a = 10;
	int  b = 20;//���b��double typeid c ����double ��ͬ�����ͻ�����ߵ�����ת��
	auto c = a + b;
	cout << typeid(c).name() << endl;//����Ƶ����������� int

	string s;
	cout << typeid(s).name() << endl;//����Ƶ����������� int
	decltype(s) e; //�ؼ���decltype����������������Ϊ���ʽָ�������͡�
	cout << typeid(e).name() << endl;//����Ƶ����������� int

}
#endif
//final��override(�˽�)
//����һ���������ؼ��ֱַ��������ʲô?
//final�����࣬��ͱ���������࣬���ܱ��̳�
//final�����������麯��������麯�����ܱ���д
//override��������д�麯��������Ƿ������д����������д���������򱨴�

//����
// C++98����
//string/vector/list/deque/map/set/bitset + stack/queue/priority_queue
//C++11������
//array(��������) : ʵ�����õĺ��٣�ȱ��; ���� + �洢���ݵĿռ���ջ��, ջ�Ŀռ䱾���Ͳ���
//forword list(������) :ʵ�����õ��٣�ȱ��:��֧��β��βɾ + insert����Ҳ���ڵ�ǰλ�õĺ���
//unordered map / unordered set : �Ƽ�ʹ�ã���Ϊ���ǵ�Ч�ʸ���map / set

//Ĭ�ϳ�Ա��������
class A
{
public:
	A() = default;//ָ����ʾȥ����Ĭ�ϵĹ��캯��

	A(const A& a) = delete;//���������
	A& operator = (const A& a) = delete;

	

private:
	int _a = 10;
};


//��ֵ���ú��ƶ����壨�ص㣩
// C++98����������õĸ�����þ͸�һ������ȡ������
// C++98 ��ֵ����
// C++11 ��ֵ����
//��������ֵ���ã�������ֵ���ã����Ƕ��Ǹ�����ȡ������
//������ֵ������Ҫ�Ǹ���ֵȡ��������ֵ������Ҫ�Ǹ���ֵȡ������


//��߾�����ֵ?�ұߵľ�����ֵ? ע�������һ��C�﷨�����µĿӣ��������ƺ�����һ����
//�������Ҳ��Ƿ�����ߵ�ֵҲ��һ����ֵ���ұߵ�ֵ��һ������ֵ
//int x1 = 10; int x2 = x1:int x3 = x1+x2;����xl����ֵ��10����ֵ��x2����ֵ  x1+x2�Ǳ��ʽ����ֵ
//�����޸ľͿ�����Ϊ����ֵ����ֵͨ���Ǳ���
// ��ֵͨ���ǳ��������ʽ���ߺ�������ֵ(��ʱ����)
//int main()
//{
//	// ��ֵ���õĶ���
//	int a = 0;
//	int& b = a;
//	int x = 1, y = 2;
//	// ��ֵ���ò�����������ֵ��const��ֵ���ÿ���
//	//int& e = 10;
//	//int& f=x+ y;
//	const int& e = 10;
//	const int& f = x + y;
//	//��ֵ���ò���������ֵ�����ǿ�������move����ֵ
//	//int&& m = a;
//
//	//��ֵ����ֵ��Ϊ����������������
//	int&& m = move(a);
//	
//	return 0;
//}
//C++11�ֽ���ֵ����Ϊ:����ֵ�ͽ���ֵ
// ����ֵ:�������͵ĳ���������ʱ����  ���������Ч�� ���ٿ���
//����ֵ:�Զ������͵���ʱ����
//����:���������(vector / list / map / set...)�������Լ�������ֵ�������������ƶ��������ƶ���ֵ
#if 0
class String
{
public:
	String(const char* str = "")
	{
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}
	//s2(s1)
	String(const String& s)
	{
		 cout << "String(const String& s)-���" << endl;
		_str = new char[strlen(s._str) + 1];
		strcpy(_str, s._str);
	}
	//s3��ֵ-����ֵ
	String( String&& s)
		:_str(nullptr)
	{
		//����������һ������ֵ�������㶼Ҫ���ˣ��ҵ�Ŀ���Ǹ�����һ����Ŀռ䣬һ����ֵ
		//�������Ŀ��ƺ�ֻ����
		cout << "String( String&& s)�ƶ�����--Ч�ʸ�" << endl;
		swap(_str, s._str);
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* newchar = new char[strlen(s._str) + 1];
			strcpy(newchar, _str);
			delete _str;
			_str = newchar;
		}
		return *this;

	}//��ֵ
	String& operator=(String&& s)
	{
		swap(_str, s._str);
		return *this;
	}
	~String()
	{
		delete _str;
	}
private:
	char* _str;
};

String f(const char* str)
{
	String tmp(str);
	return tmp;//���ﷵ��ʵ����tmp��������ʱ����
}
//��ʵ�в��ɱ�����ڴ�ֵ���صĳ�������ֵ���صĿ������ض������ʱ����
//���vectorֻʵ�ֲ���Ϊconst��ֵ�����������ô����Ĵ��۾ͺܴ�
//
//vector(const vector<T>& v)->���
// �������vectorʵ���˲�����ֵ���õ��ƶ���������ô����Ч�ʾͻ�ܸ�
// vector(vector<T>&& v)->�ƶ�����
// ����:��ֵ���ñ���û̫�����壬��ֵ���õ�ʵ�����ƶ�������ƶ���ֵ
// ��ô��Խ��պ�����ֵ���ض���(��ֵ)�ȵȳ������������Ч��
int main()
{
	String s1("hello world");
	String s2(s1); //��������ֵ
	//String s3(String("��ʱ����-��ֵ")); 
	String s3(f("��ʱ����-��ֵ"));//��������ֵ	- ����ֵ(����ֵ���㣬�����Ҿ�������)
	String s4(move(s1));
	return 0;
}
#endif
// �ܽ�
// ��ֵ������������������ֵ���ٿ����ı������������ƶ�������ƶ���ֵ
// ��ֵ���ú���ֵ���ñ��ʵ����ö��Ǽ��ٿ�������ֵ���ñ��ʿ�����Ϊ���ֲ���ֵ���ò���ĵط�,�����ศ���
// ��ֵ����:������Ǵ��ι����кͷ���ֵ�����еĿ���
// ������: void push(T x) -> void push(const T& x)������Ǵ��ι����м��ٿ���
// ������ֵ:T f2() -> T& f2()����ķ���ֵ�����еĿ���
// ps:����Ҫע�����������ƣ�������ض���������������˾Ͳ����ô����ã������ֵ�����޷�������ȴ�C++11��ֵ���ý��
//��ֵ����:������Ǵ��κ�push/insert�����ڲ��������ƶ��������ռ��ϵ�����.
//+ ��ֵ���ؽ��շ���ֵ�Ŀ���
// ������: void push(T&& x) �����push�ڲ�����ʹ�ÿ�������x�������ռ��ϣ������ƶ������ȥ
//������ֵ : T f2() : �����������ý���f2()���ض���Ŀ�����T ret = f2(), ���������ֵ���õ��ƶ����죬�����˿���


#if 0
//����ת��
void Fun(int& x) { cout << "��ֵ����" << endl; }
void Fun(const int& x) { cout << "const ��ֵ����" << endl; }
void Fun(int&& x) { cout << "��ֵ����" << endl; }
void Fun(const int&& x) { cout << "const ��ֵ����" << endl; }
// ģ���е�&&��������ֵ���ã������������ã�����ܽ�����ֵ���ܽ�����ֵ��
// ģ�����������ֻ���ṩ���ܹ�����ͬʱ������ֵ���ú���ֵ���õ�������
// �����������͵�Ψһ���þ��������˽��յ����ͣ�����ʹ���ж��˻�������ֵ��
// ����ϣ���ܹ��ڴ��ݹ����б���������ֵ������ֵ������, ����Ҫ����������ѧϰ������ת��
template<typename T>
void PerfectForward(T&& t)
{
	//Fun(t);//��ֵ���û�ڶ���֮��Ĳ������ݹ��������Զ�ʧ
	//����ת��
	Fun(std::forward<T>(t));
}
int main()
{
	PerfectForward(10);// ��ֵ
	int a;
	PerfectForward(a);// ��ֵ
	PerfectForward(std::move(a)); // ��ֵ
	const int b = 8;
	PerfectForward(b);// const ��ֵ
	PerfectForward(std::move(b)); // const ��ֵ
	return 0;
}
#endif

//lambda���ʽ�﷨
//lambda���ʽ��д��ʽ��[capture - list](parameters) mutable -> return-type{ statement
//}
//1. lambda���ʽ������˵��
//[capture - list] : ��׽�б����б����ǳ�����lambda�����Ŀ�ʼλ�ã�����������[]��
//�жϽ������Ĵ����Ƿ�Ϊlambda��������׽�б��ܹ���׽�������еı�����lambda
//����ʹ�á�
//(parameters)�������б�����ͨ�����Ĳ����б�һ�£��������Ҫ�������ݣ������
//��ͬ()һ��ʡ��
//mutable��Ĭ������£�lambda��������һ��const������mutable����ȡ���䳣��
//�ԡ�ʹ�ø����η�ʱ�������б���ʡ��(��ʹ����Ϊ��)��
//->returntype������ֵ���͡���׷�ٷ���������ʽ���������ķ���ֵ���ͣ�û�з���
//ֵʱ�˲��ֿ�ʡ�ԡ�����ֵ������ȷ����£�Ҳ��ʡ�ԣ��ɱ������Է������ͽ�����
//����
//{
//	statement
//}�������塣�ڸú������ڣ����˿���ʹ��������⣬������ʹ�����в���
//���ı�����
//ע�⣺
//��lambda���������У������б�ͷ���ֵ���Ͷ��ǿ�ѡ���֣�����׽�б�ͺ��������Ϊ
//�ա����C++11����򵥵�lambda����Ϊ��[]{}; ��lambda�����������κ����顣


//lamber���ʽ��ʵ���庯���ڴ����������
int v()
{
	//��򵥵�lambda���ʽ����lambda���ʽû���κ�����
	//û�в�����û�з���ֵ
	[] {};

	// ʡ�Բ����б�ͷ���ֵ���ͣ�����ֵ�����ɱ������Ƶ�Ϊint
	int a = 3, b = 4;
	//[��׽�б�](����)->����ֵ����{������}
	//auto add = [](int x1, int x2)->int {return x1 + x2; };
	//auto add = [a, b]()->int {return a + b; };
	// ʡ���˷���ֵ���ͣ��޷���ֵ����
	//auto fun1 = [&](int c) {b = a + c; };
	//fun1(10);
		cout << a << " " << b << endl;
		auto swap = [](int&a, int &b) {
			int c = a;
			a = b,
			b = c;
		};
		swap(a, b);
	//��׽�б���ǲ�׽����һ��������Ķ���
	// ��ֵ��׽[a]��׽a[a,b]��׽a��b[=]��׽ͬһ�������е����ж���
	// �����ò�׽[&a]��׽a [&a,&b]��׽a��b[&]��׽ͬһ�������е����ж���
	// �����ֶ������Ƶ�lambda����
	//auto fun2 = [=, &b](int c)->int {return b += a + c; };
	//cout << fun2(10) << endl;

	//// ���Ʋ�׽x
	//int x = 10;
	//auto add_x = [x](int a) mutable { x *= 2; return a + x; };
	//cout << add_x(10) << endl;
	return 0;

}