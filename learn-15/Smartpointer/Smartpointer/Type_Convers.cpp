#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
//����ת��
class Ac
{
public:
	virtual void f()
	{}
	int _a;
};
class Bc :public Ac
{
public:
	int _b;
};

void f_cast(Ac* pa)
{
	// �������pa��ָ���࣬�����������?
	// ���pa��ָ�����������ת���ɹ���
	// ���paָ���������ת��ʧ�ܷ���nullptr
	Bc* pb = dynamic_cast<Bc*>(pa);
	if (pb != nullptr)
	{
		cout << "ת���ɹ� paָ���������" << endl;
		pb->_a = 1;
		pb->_b = 2;
	}
	else
	{
		cout << "ת��ʧ�� paָ�������" << endl;

	}
}
using namespace std;
int ma()
{
	int i = 0;
	double d = 8.88;
	i = d;//����ת�� c����֧��������͵���ʿ����ת��(������ͣ�Ҳ�����������Ƶ�����)
	cout << i << endl;


	int* p = nullptr;
	p = (int*)i; //c����֧�����������ǿ������ת�� (��������ͣ�Ҳ����������ܴ������)
	cout << p << endl;

	//C++����C��������������ʽת������ʾת��  ����C++����C�������ò��淶��C++��淶һ��
	//��׼C++Ϊ�˼�ǿ����ת���Ŀ����ԣ�����������������ǿ������ת����������
	//static_cast��reinterpret_cast��const_cast��dynamic_cast

	//1.static_cast
	d = static_cast<double>(i);     // ��Ӧ��C������ʽ���͵�ת��     ��������ͣ�
	p = reinterpret_cast<int*> (i);   // ��Ӧ��C���Դ󲿷�ǿ������ת�� ����������ͣ�
	cout << d << endl;
	cout << p << endl;

	const int ci  = 10;//����volatile����20
	int* pi = const_cast<int*>(&ci);//��Ӧc����ǿ������ת����ȥ��const���Ե�(���������)
	*pi = 20;
	cout << ci << endl;//10
	// �����ӡ��10����Ϊci�洢���ڴ汻���ˣ�����ci���Ž��˼Ĵ�����
	//����ȥ�Ĵ�����ȡ������10.�����������ڱ�������const�����ȡ�Ż����Ƶ���
	cout << *pi << endl;//20


	// C++�����������Ը�ֵ������Ķ���ָ�롢���ã���������лᷢ����Ƭ
	//������﷨��Ȼ֧�ֵ� ���������ת��

	//����Ǹ����ָ��������ã����������ָ�룬������̽�����ת��
	//��������п��ܳɹ�Ҫ���������
	// �����Ҫע�����:dynamic_cast����ת��ֻ����Լ̳��еĶ�̬����(�����������麯��)

	/*  dynamic_cast��ͨ����paָ����������Ϸ��ҵ���ʶ�������Ϣ
		�����A���Ͳ���ת�����ؿ�
		�����B������ת���������ض����ַ
		����Ҫ��A�����Ƕ�̬����
	*/
	Ac a; Bc b;
	Ac* pa = &a;
	Bc* pb = &b;
	pa = &b;
	f_cast(pa);

	//// �ܽ�һ��:������������ת�������Ҫ�þ����淶һ�㣬��֪��ת�������ʲôӰ��
	return 0;
}