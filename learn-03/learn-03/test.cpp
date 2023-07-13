#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;


#if 0
/*类和对象*/
/*封装 1、将数据和方法定义到一起；
*	   2、 把想给你看到的数据给你看，不想给你看的封装起来。
*	   访问限定符   public公有  private私有
*/
class Stack
{
	public:
		//1.成员函数
		void Push(int x);  
		void Pop();
		void Empty();
	private:
		//2.成员变量
		int* _a;
		int _size;
		int _capacity;

};
// 1、C言中struct用来定义结构体的
typedef struct ListNode_C
{
	int _val;
	ListNode_C* _next;
	ListNode_C* _prev;
}ListNode_C;
// 2、C+中，兼容Cstruct义结构体的用法。但是同时struct可以用来定义类
typedef struct ListNode_CPP
{
	int _val;
	ListNode_CPP* _next;
	ListNode_CPP* _prev;
	//还可以定义函数->成员函数
	ListNode_CPP* CreateNode(int val);
}ListNode_CPP;
// 3、C+中使用classstruct义类的区别?-》默认的访问限定符
// 1、声明和定义的区别? 声明是一种承诺，承诺要干嘛，但是还没做，定义就是把这个事落地了。
//类外面定义
void Stack::Pop()
{

}
int main()
{
	//类实例化出对象
	Stack S1;

	// 对象中只存储成员变量，不存储成员函数?思考一下为什么?
	// 1一个类实例化出N对象，每个对象的成员变量都可以存储不同的值，但是调用的函数确是同一个
	// 如果每个对象都放成员函数，而这些成员函数确实一样的，浪费空间
	// 没有成员变量的类的大小是 1 面试题 为什么是1，而不是0。开一个字节不是为了存数据，而是占位
	cout << sizeof(S1) << endl;
	return 0;
}


/*
结构体内存对齐规则
1.第一个成员在与结构体偏移量为0的地址处。
2.其他成员变量要对齐到某个教字(对齐教)的整教倍的地址处。
注意:对齐数=编译器默认的一个对齐数与该成员大小的较小值。
VS中默认的对齐数为8
3.结构体总大小为:最大对齐数(所有变量类型最大者与默认对齐参数取最小)的整数倍。
4.如果嵌套了结构体的情况，嵌套的结构体对齐到自己的最大对齐数的整数倍处，结构体的整体大小就是所
有最大对齐数(含嵌套结构体的对齐数)的整数倍。
【面试题】
1.结构体怎么对齐?为什么要进行内存对齐
2.如何让结构体按照指定的对齐参数进行对齐
3.如何知道结构体中某个成员相对于结构体起始位置的偏移量
4.什么是大小端?如何测试某台机器是大端还是小端，有没有遇到过要考虑大小端的场景

*/
#endif

/*
实例化 - > 就是用自己定义的类型定义出对象
1、内置类型，基本类型 int / char / double
2、自定义类型，classstruct
*/

/*
//【面试题】
//1.this指针存在哪里 (也就是存在进程地址空间的哪个区域?)? 栈上的  因为他是一个形参
//2.this针可以为空吗 ?
class Date
{
public:
	//隐含的this指针谁调用就指向谁 默认在编译的时候第一个参数会在编译的时候带上
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
	cout<< _year << "年 " << _month << "月 "  << _day << "日" << endl;
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
	p->PrintA(); //这一行会引发什么?编译不通过? 程序崩溃? 正常运行?  // 崩溃
	p->Show();   //这一行会引发什么?编译不通过? 程序崩溃? 正常运行?  // 正常运行
	//成员函数存在公共的代码段，所以p>Show)这里不会去p向的对象上找 访问成员函数才回去找
	//常见寄存器的名称:eax ebx ecx..寄存器的特点就是快
}
#endif

//·1.类的6个默认成员函数
//·2.构造函数 ---》 主要完成初始化工作
//·3.析构函数 ---》 主要完成清理工作
//·4.拷贝构造函数
//·5.赋值操作符重载
//·6.默认拷贝构造与赋值运算符重载的问题
//·7.const成员函数
//。8.取地址及const地址操作符重载
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
public://显式定义->自定义
	//构造函数 -> 在对象构造时调用的函数，这个函数完成初始化工作
		// 构造函数是特殊的成员函数，需要注意的是，构造函数的虽然名称叫构造，
		// 但是需要注意的是构造函数的主要任务并不是开空间创建对象，而是初始化对象。
		// 其特征如下 :
		//1.函数名与类名相同。
		//2.无返回值。
		//3.对象实例化时编译器自动调用对应的构造函数。
		//4.构造函数可以重载。
		//5.如果类中没有显式定义构造函数，则C+编译器会自动生成一个无参的默认构造函数，一旦用户显式定义编译器将不再生成。


	/*
	无参的构造函数和全缺省的构造函数都称为默认构造函数，并且默认构造函数只能有一个。注意:无参构
	造函数、全缺省构造函数、我们没写编译器默认生成的构造函数，都可以认为是默认构造函数。
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
	// 我们没有显式定义构造函数，这里编译器生成无参默认构造函数
	// 我们没有显式定义构造函数，这里编译器生成无参默认构造函数
	// 默认生成无参构造函数
	//1、针对内置类型的成员变量没有做处理
	//2、针对自定义类型的成员变量，调用它的构造函数初始化

	//一旦用户显式定义编译器将不再生成。
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
	cout << _year << "年 " << _month << "月 " << _day << "日" << endl;
}
int main()
{
	Date d1;//调用默认构造参数 -> 1. 自己实现无参的构造函数 2.自己实现的全缺省构造参数，3. 不写编译器自动生成
	d1.Print();

	//Date d2;// Date d2 不能加括号()
	//d2.Print();

	
	return 0;
}
#endif


#if 0
//析构函数
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
		cout << _year << "年 " << _month << "月 " << _day << "日" << endl;
	}
	//析构函数是特殊的成员函数。
	//其特征如下 :
	//1.析构函数名是在类名前加上字符 ~ 。
	//2.无参数无返回值。
	//3.一个类有且只有一个析构函数。若未显式定义，系统会自动生成默认的析构函数。
	//4.对象生命周期结束时，C + 编译系统系统自动调用析构函数。
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
	//析构函数：对象生命周期到了以后，自动调用 完成对象里面的清理工作 不是完成d1和d2销毁
	//先入后出
	Date d1(2023,7,10);
//拷贝构造函数也是特殊的成员函数，其特征如下:
//1.拷贝构造函数 是构造函数的 一个重载形式。
//2.拷贝构造函数的参数只有一个且必须使用->引用<-传参，使用传值方式会引发无穷递归调用。
	//下面这两种方式都可以  拷贝函数
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

//赋值操作符重载

//C + 为了增强代码的可读性引入了运算符重载，运算符重载是具有特殊函数名的函数，也具有其返回值类型
//函数名字以及参数列表，其返回值类型与参数列表与普通的函数类似。
//函数名字为 : 关键字operator后面接需要重载的运算符符号。
//函数原型 : 返回值类型operator操作符(参数列表) 
//注意 :
//	。不能通过连接其他符号来创建新的操作符 : 比如operator@
//	。重载操作符必须有一个类类型或者枚举类型的操作数
//	。用于内置类型的操作符，其含义不能改变，例如 : 内置的整型 + ，不能改变其含义
//	。作为类成员的重载函数时，其形参看起来比操作数数目少1成员函数的
//	操作符有一个默认的形参this，限定为第一个形参
//	。.*、::、sizeof、?:、. 注意以上5个运算符不能重载。这个经常在笔试选择题中出现。

#if 0
//运算符有几个操作数，operator重载的函数就有几个参数

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
	//自定义类型是不能用运算符的，要用就得实现重载函数，自定义类型用的时候等价于调用这个重载函数
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

	d1 == d2;//编译如何调用->这里编译会转换成operator=(dld):所这里就是一个函数调用
	// operator == (d1, d2);// 但是我们一般不会这样写，因为这样可读性不好
	d1 > d2;
	return 0;
}
#endif 

#if 0
//实现一个完善的日期类
class Date
{
public:
	int _Getmonths(int year,int month)
	{
		static int MonthDays[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		//是二月且是闰年返回 29
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
			cout << "非法日期" << endl;
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
		return !(*this == d);// 复用上面的来实现
	}
	bool operator <=(const Date& d)
	{
		
		return *this < d || *this == d; // 复用上面的来实现
	}
	bool operator >(const Date& d)
	{
		return !(*this <= d);// 复用上面的来实现
	}
	bool operator >=(const Date& d)
	{
		return !(*this < d);// 复用上面的来实现

	}
	//复用+=事件
	Date operator +(int day)
	{
		Date ret(*this); // 用d1 拷贝构造一个ret
		ret += day;
		return ret;
	}
	Date& operator +=(int day)//返回自己需要带引用
	{
		if (day < 0)
		{
			return *this -= -day;
		}
		_day += day;
		while (_day > _Getmonths(_year, _month))
		{
			// 如果日期的天不合法，就需要往月进
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
	//复用-=事件
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
	//++d1 =》 d1.operator++(&d1)
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
	//d1++  =》 d1.operator++(&d1，0)
	Date operator ++(int)
	{
		Date ret(*this);
		*this += 1;
		return ret;//返回加之前的值
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
		return ret;//返回加之前的值
	}
	//计算相差天数
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

	// 是否要重载一个运算符，看的是这个运算符是否对这个类的对象有意义
	/*Date d4 = d2 + 100;
	d4.Print();*/



}
#endif
//1、我们不实现时，编译器生成的
//默认构造函数和析构函数。针对
//成员变量 : 内置类型就不处理，
//自定义类型会调这个成员对象的构造和
//析构。
//2、我们不实现时，编译器生成拷贝构造
//和operator = ，会完成按字节的值拷贝(浅拷贝
//也就是说有些类，我们是不需要去实现拷贝构造
//和operator = 的，因为编译器默认生成就可以用。
//比如 : Date是这样

// const Date * p ->*p 指向的对象
// Date const * p2 ->*p2 指向的对象
// Date* const p ->p 指针本身
//const在*之前指向的对象 在*之后指向本身
class Date
{
public:
	Date(int year = 0,int month = 1,int day=1)
		:year(year),month(month),day(day)//使用初始化列表进行成员变量初始化比在构造函数体内使用赋值语句效率更高，并且可以用于初始化const成员变量或引用类型成员变量。
	{}
	

private:
	int year;
	int month;
	int day;
};

