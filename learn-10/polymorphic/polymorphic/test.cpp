#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
/*
virtual�ؼ��֣��������γ�ԭ������Ϊ������麯������д�������̬������֮һ��
���������μ̳��У�ȥ�����̳У������������Ͷ����ԡ�
�����ط�ʹ����ͬһ���ؼ��֣��������ǻ���֮��û��һ�����*/
using namespace std;
#if 0
//��̬����������
//1. �麯������д
//2. ��������ָ���������ȥ�����麯��
//�����̬:��ָ������йأ�ָ���ĸ�������þ��������麯��
//�������̬ : �����ö���������йأ�������ʲô���õľ���˭���麯��

//�麯����д����������:
//1.Э��(�������������麯������ֵ���Ͳ�ͬ)
//��������д�����麯��ʱ��������麯������ֵ���Ͳ�ͬ���������麯�����ػ�������ָ��������á�
//�������麯����������������ָ���������ʱ����ΪЭ�䡣(�˽�)
class Person
{
public :
	virtual Person* ButTicket()
	{
		cout << " Person::��Ʊ ȫ��" << endl; 
		return nullptr;
	}
};
class Student:public Person
{
public:
	/*ע��:����д����������ʱ����������麯���ڲ���virtua1�ؼ���ʱ����ȻҲ���Թ�����д(��Ϊ�̳к�����
�麯�����̳������������������ɱ����麯������)�����Ǹ���д�����Ǻܹ淶������������ʹ��*/
	virtual Student* ButTicket() //Student*Э��
	{ 
		cout << " Student::��Ʊ ���" << endl;
		return nullptr;
	}
};

void Func(Person& p)//������ָ���������
{
	p.ButTicket();
}
int main()
{
	Person ps;
	Student st;

	//ps.ButTicket();
	//st.ButTicket();

	Func(ps);
	Func(st);

	return 0;
}


//2.4 C++11 override��final
//��������Կ�����C++�Ժ�����д��Ҫ��Ƚ��ϸ񣬵�����Щ�����������������ܻᵼ�º�������ĸ����д
//�����޷��������أ������ִ����ڱ����ڼ��ǲ��ᱨ���ģ�ֻ���ڳ�������ʱû�еõ�Ԥ�ڽ������debug
//��ò���ʧ����� : C++11�ṩ��override��final�����ؼ��֣����԰����û�����Ƿ���д��
//1.final : �����麯������ʾ���麯�������ٱ��̳�
//������ ���������Ƿ���Ҫ������麯����

class Person {
public:
	//virtual void Drive() = 0;// ����Ҫʵ�֣����麯��
	// 1�����麯�������ã�ǿ������ȥ�����д
	// 2����ʾ���������   �����������ʵ��û�ж�Ӧ��ʵ��
	virtual ~Person()/* finalһ����Ա�������Ա�����Ϊfinal������ζ�����������������б���д�򸲸ǡ�*/ { cout << "~Person()" << endl; }
	//// ���������ĺ������ᱻ�����destructor
};
class Student :public Person {
public:
	virtual void Drive(){}
	virtual ~Student() override/*��������麯���Ƿ���д������麯��*/ { cout << "~student()" << endl; }
	//// ���������ĺ������ᱻ�����destructor
};

int main()
{
	Person* p = new Person;
	delete p;

	Person* p1 = new Student;
	delete p1;
	
	return 0;
}
#endif
//���ء�����(��д)������(�ض���)�ĶԱ�
//���أ�       1.����������ͬһ������ 
//             2.������ / ������ͬ

//��д(����)   1.���������ֱ��ڻ�����������������  
//		       2. ������ / ���� / ����ֵ��������ͬ(Э������)
//      	   3.���������������麯��
//�����д��Ϊ����д����ʵ��

//�ض���(����) 1.���������ֱ��ڻ�����������������
//	           2.��������ͬ
//	           3.����������������ͬ��������������д�����ض���


//3.2�ӿڼ̳к�ʵ�ּ̳�
//��ͨ�����ļ̳���һ��ʵ�ּ̳У�������̳��˻��ຯ��������ʹ�ú������̳е��Ǻ�����ʵ�֡��麯����
//�̳���һ�ֽӿڼ̳У�������̳е��ǻ����麯���Ľӿڣ�Ŀ����Ϊ����д����ɶ�̬���̳е��ǽӿڡ���
//�������ʵ�ֶ�̬����Ҫ�Ѻ���������麯����

//��̬���ʵ�ֵ�ָ��˭�͵���˭���麯�� ?
//��̬��������ʱ��ָ��Ķ��������в���Ҫ���õ��麯���ĵ�ַ�����е��á�

class A
{
public:
	virtual void func1() { cout << "A func1 : " << endl; }
	virtual void func2() { cout << "A func1 : " << endl; }

};
class B :public A
{
public:
	virtual void func1() { cout << "B func1 : " << endl; }
	virtual void func3() { cout << "B func3 : " << endl; }
	virtual void func4() { cout << "B func3 : " << endl; }

};
typedef	void(*VF_PTR)();
void PrintVFTable(VF_PTR* pTable)
{
	for (size_t i = 0; pTable[i]!= 0; i++)
	{
		printf("Vtable : %d : %p->", i, pTable[i]);
		cout << endl;
	}
	
}

int main()
{
	A a;
	B b;
	PrintVFTable((VF_PTR*)(*(int*)&a));
	PrintVFTable((VF_PTR*)(*(int*)&b));
	return 0;
}