#define _CRT_SECURE_NO_WARNINGS
#include <iostream>//c++�������������
//���ճ���ϰ�У����ں�����������ͻ
using namespace std; // C++�����еĶ������Ƿŵ�std�����ռ��е�
//������Ŀ��ͨ���Ƚ��Ƽ�������
//using std::cout;
//using std::endl;

namespace N
{
	int a = 0;
	int b = 20;
	int Add(int left, int right)
	{
		return left + right;
	}
	int Sub(int left, int right)
	{
		return left - right;
	}
}
//�����ռ��ʹ�������ַ�ʽ:
//1���������ռ����Ƽ��������޶���
int main()
{
	printf("%d\n",N::a);
	return 0;
}
//2 ʹ��using �������ռ��г�Ա����
using N::b;
int main()
{
	printf("%d\n", N::a);
	printf("%d\n", b);
}
////3 ʹ��using namespace�������ռ���������
using namespace N;
int main()
{
	//cout �Զ�ʶ������  ��������
	cout << "hello world\n" << endl;//cout���������  endl����һ�����з�
	double d = 1.1;
	cin  >> d;//cin���������� ��ʿscanf
	cout << "hello world\n" << d<<endl;
	printf("%d\n", a);
	printf("%d\n", b);
}

//ȱʡ��������
//ȱʡ�������������庯��ʱΪ�����Ĳ���ָ��һ��Ĭ��ֵ���ڵ��øú���ʱ�����û��ָ��ʵ������ø�
//Ĭ��ֵ������ʹ��ָ����ʵ�Ρ�
void Func(int a = 0)
{
	cout << a << endl;
}
//4.2ȱʡ��������
//��ȫȱʡ����
void TestFunc(int a = 10, int b = 20, int c = 30)
{

	cout << "a =" << a << endl;
	cout << "b =" << b << endl;
	cout << "c=" << c << endl;
}

//����ȱʡ���� ȱʡ���ֲ���   ȱʡ��������������������
//  û��ȱʡ�� �������봫��
void TestFunc1(int a,int b = 10, int c = 20)
{

	cout << "a=" << a <<endl;
	cout << "b =" << b << endl;
	cout << "c =" << c << endl;
}
//�������� ��������ͬ��������ͬ(����or����or˳��ͬ)
//����ֵû��Ҫ�� ����ֻ�Ƿ���ֵ��ͬ ���ܹ�������
/*����:��������:
1��ʲô��������
2��C + �����֧�ֺ������ص� ? ΪʲôC�Բ�֧�֣�*/
/*1. Ԥ���� ->
* 2. ���� ->
* 3. ���
* 4. ����
*/
int Add(int left, int right)
{
	return left + right;
}
double Add(double left, double right)
{
	return left + right;
}
long Add(long left, long right)
{
	return left + right;
}
#if 0
5.3 externC
��ʱ����C++�����п�����Ҫ��ĳЩ��������C�ķ�������룬�ں���ǰ��extern"C"��˼�Ǹ��߱�������
���ú�������C���Թ��������롣���� : tcmalloc��google��C++ʵ�ֵ�һ����Ŀ�����ṩtcmallc()��tcfree
�����ӿ���ʹ�ã��������C�;�û�취ʹ�ã���ô����ʹ��externC�������
ʾ����.c�ļ���ʵ���������� double Add(double left, double right);
��.h�ļ���ʵ��ʱ  extern "C" double Add(double left, double right);
#endif

#if 0 
6. ����
6.1���ø���
���ò����¶���һ�����������Ǹ��Ѵ��ڱ���ȡ��һ������������������Ϊ���ñ��������ڴ�ռ䣬������
���õı�������ͬһ���ڴ�ռ䡣
���� : ���ӣ��ڼҳ�Ϊ"��ţ"���������˳�"������"
int a = 1;
int& ra = a;//raa���ã�����Ҳ���Ǳ�����a��ȡ��һ������
ra = 2;
cout << ra << endl;//2
cout << &ra << endl;//00EFFC78

int& b;
2 ��������
1.�����ڶ���ʱ�����ʼ��
2.һ�����������ж������
3.����һ������һ��ʵ�壬�ٲ�����������ʵ��
int a = 1;
//int& b;
//���ñ����ڶ���ʱ��ʼ��
int& c = a;
int d = 2;
c = d;// ����:������c����d����?no���ǽ�dֵ��cok


const int a = 0:
// int& b =a:// b��������int�����벻ͨ����ԭ��:a��ֻ����b��������int��Ҳ���ǿɶ���д�ġ�
const int& b = a :
	int c = 1; I
	int& d = c;
const int& e = c// �в���?����->cֻ�ǿɶ���д��e��ɱ���ֻ��
// �ܽ�:����ȡ����ʱ���������ʵ�Ȩ�޿�����С�����ܷŴ�
#endif


int main()
{
	Func();//û�д���ʹ�ò���Ĭ��ֵ
	Func(10);

	//����ʱ�����Ҫ���α�������������δ���
	TestFunc();
	TestFunc(10);      //ȫȱʡ����ת�������ʵ��
	TestFunc(10, 20);
	TestFunc(10, 20,30);
	
	return 0;
}

