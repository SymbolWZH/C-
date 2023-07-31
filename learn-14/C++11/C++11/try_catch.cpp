#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

// ʲô���쳣:�쳣����������﷨�������һ�ַ�ʽ
//C���Դ�ͳ�Ĵ������ķ�ʽ����Щ��?
//1�����ش�������ЩAPI�ӿڶ��ǰѴ�����ŵ�errno��
//2����ֹ������緢��Խ�����������ʱ������Ҳ������������exit(xx):
// ��ͳ�Ĵ�������ȱ��:
// ���һ���������ù�����ֵ�����ݣ���������ʱ���Ѵ���

int Div(int& a ,  int& b)
{
	if (b == 0)
		throw "������0����";
	if(a == 0)
		throw -1;
	if (a == 1 && b == 1)
		throw string("������0����");

	return a % b;

}
int m1()
{
	try
	{
		int n, m;
		cin >> n >> m;
		cout << Div(n, m) << endl;
	}
	catch (int err)
	{
		cout << err << endl;
	}
	catch (const string& err)
	{
		cout << err << endl;
	}
	catch (...)
	{
		cout << "δ֪�쳣" << endl;
	}
	return 0;
}

// ��˾���һ������
//Ҫ��������Լ����Լ�������쳣�����Ǳ���̳��������
//�����Ļ�����㲶���ֻ��Ҫ�������Ϳ���
class Exception
{
public:
	Exception(const char*  str, int errid)
		:_errmsg(str),_errid(errid)
	{}
	virtual string what() = 0;
protected:
	int _errid; //������
	string _errmsg;//��������
	// stack<string> _st;
};
class SqlException : public  Exception
{

public:
	SqlException(const char* str, int errid)
		:Exception(str,errid)
	{}

	virtual string what() 
	{
		return "�������" + _errmsg;
	}
};

void ServerStart()
{
	//ģ��һ�³���������һ��
	if (rand() % 11 == 0)
		throw SqlException("���ݿ�����ʧ��", 1);
	if (rand() % 7 == 0)
		throw SqlException("��������ʧ��",3);
	cout << "��������" << endl;
}
int main()
{
	for (size_t i = 0; i < 100; i++)
	{
		try
		{
			for (size_t i = 0; i < 100; i++)
			{
				ServerStart();
			}
		}
		catch (Exception& e)
		{
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "δ֪�쳣" << endl;
		}
	}
	return 0;
}

// �쳣����ȱ���ܽ�:
// �ŵ�:
// 1�������İ���������Ϣ
// 2�����T operator[](int i)��������Խ������쳣���ԺܺõĽ��
// 3��������ʱ�����淢�����󣬲�����Ҫ��㴦�������ֱ�Ӳ��񼴿�
// 4���ܶ�������ⶼ�����쳣������Ҳʹ���쳣���Ը��õ�ʹ�����ǡ�����:boost��gtest��gmock
// ȱ��:
// 1���쳣�ᵼ��ִ��������������ҵ��Է�������bug����һЩ���ѡ�
// 2��c++û��GC,�쳣���ܵ�������Դй¶���쳣��ȫ���⡣ ��Ҫѧ��ʹ��RAII�������
// 3��C++�Ŀ�������쳣��ϵ���岻̫���ã��ܶ๫˾����ѡ���Լ����塣
// 4��C++���쳣���Կ������������͵��쳣�������Ŀ��û�����ܺù淶������ô��ǳ��Ļ�
//�ң�����һ����Ҫ������̳���ϵ���쳣�淶��

// �쳣������Ի���һ�������ڱ׵Ķ���������ʵ���ճ���ϰ����С��Ŀ����̫ʹ��
// ��˾һ�㻹�ǻ�ѡ���쳣���������