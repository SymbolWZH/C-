#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;


#if 0
/*��Ͷ���*/
/*��װ 1�������ݺͷ������嵽һ��
*	   2�� ������㿴�������ݸ��㿴��������㿴�ķ�װ������
*	   �����޶���   public����  private˽��
*/
class Stack
{
	public:
		//1.��Ա����
		void Push(int x);  
		void Pop();
		void Empty();
	private:
		//2.��Ա����
		int* _a;
		int _size;
		int _capacity;

};
// 1��C����struct��������ṹ���
typedef struct ListNode_C
{
	int _val;
	ListNode_C* _next;
	ListNode_C* _prev;
}ListNode_C;
// 2��C+�У�����Cstruct��ṹ����÷�������ͬʱstruct��������������
typedef struct ListNode_CPP
{
	int _val;
	ListNode_CPP* _next;
	ListNode_CPP* _prev;
	//�����Զ��庯��->��Ա����
	ListNode_CPP* CreateNode(int val);
}ListNode_CPP;
// 3��C+��ʹ��classstruct���������?-��Ĭ�ϵķ����޶���
// 1�������Ͷ��������? ������һ�ֳ�ŵ����ŵҪ������ǻ�û����������ǰ����������ˡ�
//�����涨��
void Stack::Pop()
{

}
int main()
{
	//��ʵ����������
	Stack S1;

	// ������ֻ�洢��Ա���������洢��Ա����?˼��һ��Ϊʲô?
	// 1һ����ʵ������N����ÿ������ĳ�Ա���������Դ洢��ͬ��ֵ�����ǵ��õĺ���ȷ��ͬһ��
	// ���ÿ�����󶼷ų�Ա����������Щ��Ա����ȷʵһ���ģ��˷ѿռ�
	// û�г�Ա��������Ĵ�С�� 1 ������ Ϊʲô��1��������0����һ���ֽڲ���Ϊ�˴����ݣ�����ռλ
	cout << sizeof(S1) << endl;
	return 0;
}


/*
�ṹ���ڴ�������
1.��һ����Ա����ṹ��ƫ����Ϊ0�ĵ�ַ����
2.������Ա����Ҫ���뵽ĳ������(�����)�����̱��ĵ�ַ����
ע��:������=������Ĭ�ϵ�һ����������ó�Ա��С�Ľ�Сֵ��
VS��Ĭ�ϵĶ�����Ϊ8
3.�ṹ���ܴ�СΪ:��������(���б��������������Ĭ�϶������ȡ��С)����������
4.���Ƕ���˽ṹ��������Ƕ�׵Ľṹ����뵽�Լ������������������������ṹ��������С������
����������(��Ƕ�׽ṹ��Ķ�����)����������
�������⡿
1.�ṹ����ô����?ΪʲôҪ�����ڴ����
2.����ýṹ�尴��ָ���Ķ���������ж���
3.���֪���ṹ����ĳ����Ա����ڽṹ����ʼλ�õ�ƫ����
4.ʲô�Ǵ�С��?��β���ĳ̨�����Ǵ�˻���С�ˣ���û��������Ҫ���Ǵ�С�˵ĳ���

*/
#endif

/*
ʵ���� - > �������Լ���������Ͷ��������
1���������ͣ��������� int / char / double
2���Զ������ͣ�classstruct
*/

/*
//�������⡿
//1.thisָ��������� (Ҳ���Ǵ��ڽ��̵�ַ�ռ���ĸ�����?)? ջ�ϵ�  ��Ϊ����һ���β�
//2.this�����Ϊ���� ?
class Date
{
public:
	//������thisָ��˭���þ�ָ��˭ Ĭ���ڱ����ʱ���һ���������ڱ����ʱ�����
	//void Init(Date* this , int year = 2000 ,int month = 0 ,int day = 1)
	void Init(int year = 2000 ,int month = 0 ,int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
		//this->_year = year;
		//this->_month = month;
		//this->_day = day;
	}
	void Print();

private:
	int _year;
	int _month;
	int _day;
};
void Date::Print()
{
	cout<< _year << "�� " << _month << "�� "  << _day << "��" << endl;
}
*/

//int main()
//{
//
//	Date d1;
//	d1.Init();
//	d1.Print();
//	d1.Init(2023,7,10); // d1.Init(&d1,2023,7,10);
//	d1.Print();         // d1.Print(&d1);    
//	return 0;
//}

#if 0
class A
{
public:
	void PrintA()
	{
		cout <</* this-> */ _a << endl;

	}
	
	void Show()
	{
		cout << "Show()" << endl;
	}

	private:
		int _a;
};
int main()
{
	A* p = NULL;
	p->PrintA(); //��һ�л�����ʲô?���벻ͨ��? �������? ��������?  // ����
	p->Show();   //��һ�л�����ʲô?���벻ͨ��? �������? ��������?  // ��������
	//��Ա�������ڹ����Ĵ���Σ�����p>Show)���ﲻ��ȥp��Ķ������� ���ʳ�Ա�����Ż�ȥ��
	//�����Ĵ���������:eax ebx ecx..�Ĵ������ص���ǿ�
}
#endif

//��1.���6��Ĭ�ϳ�Ա����
//��2.���캯�� ---�� ��Ҫ��ɳ�ʼ������
//��3.�������� ---�� ��Ҫ���������
//��4.�������캯��
//��5.��ֵ����������
//��6.Ĭ�Ͽ��������븳ֵ��������ص�����
//��7.const��Ա����
//��8.ȡ��ַ��const��ַ����������
class Time
{
	public:
		Time() {
			hour = 0;
			second = 0;
			moinute = 0;
			cout <<"time()" << endl;
		
		}
	

	private:
		int hour;
		int second;
		int moinute;
};
#if 0
class Date
{
public://��ʽ����->�Զ���
	//���캯�� -> �ڶ�����ʱ���õĺ��������������ɳ�ʼ������
		// ���캯��������ĳ�Ա��������Ҫע����ǣ����캯������Ȼ���ƽй��죬
		// ������Ҫע����ǹ��캯������Ҫ���񲢲��ǿ��ռ䴴�����󣬶��ǳ�ʼ������
		// ���������� :
		//1.��������������ͬ��
		//2.�޷���ֵ��
		//3.����ʵ����ʱ�������Զ����ö�Ӧ�Ĺ��캯����
		//4.���캯���������ء�
		//5.�������û����ʽ���幹�캯������C+���������Զ�����һ���޲ε�Ĭ�Ϲ��캯����һ���û���ʽ������������������ɡ�


	/*
	�޲εĹ��캯����ȫȱʡ�Ĺ��캯������ΪĬ�Ϲ��캯��������Ĭ�Ϲ��캯��ֻ����һ����ע��:�޲ι�
	�캯����ȫȱʡ���캯��������ûд������Ĭ�����ɵĹ��캯������������Ϊ��Ĭ�Ϲ��캯����
	*/
	/*Date(int year = 2000, int month = 0, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}*/
	/*Date()
	{
		_year = 0;
		_month = 1;
		_day = 1;
	}*/
	// ����û����ʽ���幹�캯������������������޲�Ĭ�Ϲ��캯��
	// ����û����ʽ���幹�캯������������������޲�Ĭ�Ϲ��캯��
	// Ĭ�������޲ι��캯��
	//1������������͵ĳ�Ա����û��������
	//2������Զ������͵ĳ�Ա�������������Ĺ��캯����ʼ��

	//һ���û���ʽ������������������ɡ�
	void Init(int year = 2000, int month = 0, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
		//this->_year = year;
		//this->_month = month;
		//this->_day = day;
	}
	void Print();

private:
	int _year;
	int _month;
	int _day;
	
	Time t;
};
void Date::Print()
{
	cout << _year << "�� " << _month << "�� " << _day << "��" << endl;
}
int main()
{
	Date d1;//����Ĭ�Ϲ������ -> 1. �Լ�ʵ���޲εĹ��캯�� 2.�Լ�ʵ�ֵ�ȫȱʡ���������3. ��д�������Զ�����
	d1.Print();

	//Date d2;// Date d2 ���ܼ�����()
	//d2.Print();

	
	return 0;
}
#endif


#if 0
//��������
class Date
{
public:
	
	Date(int year = 2000, int month = 0, int day = 1)
	{
		
		cout << "Date(int year = 2000, int month = 0, int day = 1)" << endl;
		_year = year;
		_month = month;
		_day = day;
	}
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	void Print()
	{
		cout << _year << "�� " << _month << "�� " << _day << "��" << endl;
	}
	//��������������ĳ�Ա������
	//���������� :
	//1.������������������ǰ�����ַ� ~ ��
	//2.�޲����޷���ֵ��
	//3.һ��������ֻ��һ��������������δ��ʽ���壬ϵͳ���Զ�����Ĭ�ϵ�����������
	//4.�����������ڽ���ʱ��C + ����ϵͳϵͳ�Զ���������������
	~Date() {
		cout <<  " ~Date()" << endl;
	}

private:
	int _year;
	int _month;
	int _day;
};
class Stack
{
public:
	Stack(int n = 10)
	{
		_a = (int*)malloc(sizeof(int) * n);
		_size = 0;
		_capacity = n;
	}
	
	~Stack()
	{
		free(_a);
		_a = nullptr;
		_size = _capacity = 0;
		cout << _a << endl;
	}
private:
	int* _a;
	int _size;
	int _capacity;
};
int main()
{
	//���������������������ڵ����Ժ��Զ����� ��ɶ�������������� �������d1��d2����
	//������
	Date d1(2023,7,10);
//�������캯��Ҳ������ĳ�Ա����������������:
//1.�������캯�� �ǹ��캯���� һ��������ʽ��
//2.�������캯���Ĳ���ֻ��һ���ұ���ʹ��->����<-���Σ�ʹ�ô�ֵ��ʽ����������ݹ���á�
	//���������ַ�ʽ������  ��������
	Date d2(d1);
	Date d3 = d1;
	d1.Print();
	d2.Print();
	d3.Print();


	Stack s1;
	Stack s2;
	return 0;
}
#endif

//��ֵ����������

//C + Ϊ����ǿ����Ŀɶ�����������������أ�����������Ǿ������⺯�����ĺ�����Ҳ�����䷵��ֵ����
//���������Լ������б��䷵��ֵ����������б�����ͨ�ĺ������ơ�
//��������Ϊ : �ؼ���operator�������Ҫ���ص���������š�
//����ԭ�� : ����ֵ����operator������(�����б�) 
//ע�� :
//	������ͨ���������������������µĲ����� : ����operator@
//	�����ز�����������һ�������ͻ���ö�����͵Ĳ�����
//	�������������͵Ĳ��������京�岻�ܸı䣬���� : ���õ����� + �����ܸı��京��
//	����Ϊ���Ա�����غ���ʱ�����βο������Ȳ�������Ŀ��1��Ա������
//	��������һ��Ĭ�ϵ��β�this���޶�Ϊ��һ���β�
//	��.*��::��sizeof��?:��. ע������5��������������ء���������ڱ���ѡ�����г��֡�

#if 0
//������м�����������operator���صĺ������м�������

class Date
{
public:

	Date(int year = 2000, int month = 0, int day = 1)
	{

		cout << "Date(int year = 2000, int month = 0, int day = 1)" << endl;
		_year = year;
		_month = month;
		_day = day;
	}
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	//�Զ��������ǲ�����������ģ�Ҫ�þ͵�ʵ�����غ������Զ��������õ�ʱ��ȼ��ڵ���������غ���
	bool operator == (const Date& d)
	{
		return _year == d._year
			&& _month == d._month
			&& _day == d._day;
	}
	bool operator > (const Date& d)
	{
		if (_year > d._year)
			return true;
		else if (_year == d._year && _month == d._month)
			return true;
		else if (_year == d._year && _month == d._month && _day == d._day)
			return true;
		

			return false;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1(2020, 5, 12);
	Date d2(2020, 5, 13);

	d1 == d2;//������ε���->��������ת����operator=(dld):���������һ����������
	// operator == (d1, d2);// ��������һ�㲻������д����Ϊ�����ɶ��Բ���
	d1 > d2;
	return 0;
}
#endif 

#if 0
//ʵ��һ�����Ƶ�������
class Date
{
public:
	int _Getmonths(int year,int month)
	{
		static int MonthDays[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		//�Ƕ����������귵�� 29
		if (month == 2 && (year % 4 && year % 100 != 0) || year % 400 == 0)
			return 29;

		return MonthDays[month];
	}
	Date(int year = 0,int month = 1,int day = 1)
	{
		if (year >= 0 && month >= 1 && day >= 1 && day <= _Getmonths(year, month))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "�Ƿ�����" << endl;
		}
	}
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
	bool operator == (const Date& d)
	{
		return _year == d._year && _month == d._month && _day == d._day;;
	}
	inline bool operator <(const Date& d)
	{
		if (_year < d._year)
			return true;
		else if (_year == d._year && _month < d._month)
			return true;
		else if (_year == d._year && _month == d._month && _day < d._day)
			return true;

		return false;
	}
	bool operator != (const Date& d)
	{
		return !(*this == d);// �����������ʵ��
	}
	bool operator <=(const Date& d)
	{
		
		return *this < d || *this == d; // �����������ʵ��
	}
	bool operator >(const Date& d)
	{
		return !(*this <= d);// �����������ʵ��
	}
	bool operator >=(const Date& d)
	{
		return !(*this < d);// �����������ʵ��

	}
	//����+=�¼�
	Date operator +(int day)
	{
		Date ret(*this); // ��d1 ��������һ��ret
		ret += day;
		return ret;
	}
	Date& operator +=(int day)//�����Լ���Ҫ������
	{
		if (day < 0)
		{
			return *this -= -day;
		}
		_day += day;
		while (_day > _Getmonths(_year, _month))
		{
			// ������ڵ��첻�Ϸ�������Ҫ���½�
			_day -= _Getmonths(_year, _month);
			++_month;

			if (_month == 13)
			{
				++_year;
				_month = 1;
			}
		}
		return *this;
	}
	//����-=�¼�
	Date operator -(int day)
	{
		Date ret(*this);
		ret._day -= day;
		return ret;
	}

	Date& operator -=(int day)
	{
		if (day < 0)
		{
			return *this += -day;
		}
			_day -= day;
			while (_day <= 0)
			{
				--_month;
				if (_month == 0)
				{
					--_year;
					_month = 12;
				}
				_day += _Getmonths(_year, _month);
			}
			return *this;
	}
	//++d1 =�� d1.operator++(&d1)
	Date& operator ++()
	{
		/*if (_day == _Getmonths(_year, _month))
		{
			_day = 1;
			++_month;
		}
		else if (_day == _Getmonths(_year, _month) && _month == 12)
		{
			++_year;
			_month = 1;
			_day = 1;
		}
		else
			_day += 1;*/
		* this += 1;
		return *this;
	}
	//d1++  =�� d1.operator++(&d1��0)
	Date operator ++(int)
	{
		Date ret(*this);
		*this += 1;
		return ret;//���ؼ�֮ǰ��ֵ
	}
	// --d1   d1.operator--(&d1)
	Date& operator --()
	{
		*this -= 1;
		return *this;
	}
	//--d1   d1.operator--(&d1,0)
	Date operator --(int)
	{
		Date ret(*this);
		*this -= 1;
		return ret;//���ؼ�֮ǰ��ֵ
	}
	//�����������
	int operator-(const Date& d)
	{
		int flag = 1;
		Date max = *this;
		Date min = d;
		if (*this == d)
			return  0;
		
		if (*this < d)
		{
			max = d;
			min = *this;
			flag = -1;
		}
		int totalDay = 0;
		while (min != max)
		{
			++min;
			++totalDay;
		}
		return totalDay * flag;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	/*Date d1;
	d1.Print();*/
	Date d1(2019, 4, 11);
	Date d2(2020, 4, 11);
	cout << (d1 - d1) << endl;
	cout << (d2 - d1) << endl;

	//Date d3(0, 0, 0);

	//d3.Print();


	/*cout << (d1 < d2) << endl;
	cout << (d1 <= d2) << endl;

	cout << (d1 > d2) << endl;
	cout << (d1 >= d2) << endl;

	cout << (d1 == d2) << endl;
	cout << (d1 != d2) << endl;*/

	// �Ƿ�Ҫ����һ������������������������Ƿ�������Ķ���������
	/*Date d4 = d2 + 100;
	d4.Print();*/



}
#endif
//1�����ǲ�ʵ��ʱ�����������ɵ�
//Ĭ�Ϲ��캯�����������������
//��Ա���� : �������;Ͳ�����
//�Զ������ͻ�������Ա����Ĺ����
//������
//2�����ǲ�ʵ��ʱ�����������ɿ�������
//��operator = ������ɰ��ֽڵ�ֵ����(ǳ����
//Ҳ����˵��Щ�࣬�����ǲ���Ҫȥʵ�ֿ�������
//��operator = �ģ���Ϊ������Ĭ�����ɾͿ����á�
//���� : Date������

// const Date * p ->*p ָ��Ķ���
// Date const * p2 ->*p2 ָ��Ķ���
// Date* const p ->p ָ�뱾��
//const��*֮ǰָ��Ķ��� ��*֮��ָ����
class Date
{
public:
	Date(int year = 0,int month = 1,int day=1)
		:year(year),month(month),day(day)//ʹ�ó�ʼ���б���г�Ա������ʼ�����ڹ��캯������ʹ�ø�ֵ���Ч�ʸ��ߣ����ҿ������ڳ�ʼ��const��Ա�������������ͳ�Ա������
	{}
	

private:
	int year;
	int month;
	int day;
};

