#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include <cstdio>
#include <assert.h>
#if 0
//4. ��Ԫ
//��Ԫ��Ϊ : ��Ԫ��������Ԫ��
//��Ԫ�ṩ��һ��ͻ�Ʒ�װ�ķ�ʽ����ʱ�ṩ�˱�����������Ԫ��������϶ȣ��ƻ��˷�װ��������Ԫ���˶��á�
//4.1 ��Ԫ����
//���� : �������ǳ���ȥ����operator << ��Ȼ��������û�취��operator << ���سɳ�Ա��������Ϊcout����
//���������������thisָ������ռ��һ��������λ�á�thisָ��Ĭ���ǵ�һ������Ҳ������������ˡ�����ʵ
//��ʹ����cout��Ҫ�ǵ�һ���βζ��󣬲�������ʹ�á���������Ҫ��operator << ���س�ȫ�ֺ�������������
//�Ļ����ֻᵼ������û�취���ʳ�Ա����ô�������Ҫ��Ԫ�������operator > ͬ��

class Date
{
	friend void f(Date& d);//��Ԫ����
	friend  ostream& operator << (ostream& out, const Date& d);
	friend istream& operator >> (istream& in,  Date& d);
public:
	

private:
	int a = 0;
	int b = 1;
};
void f(Date& d)
{
	cout << d.a <<d.b << endl;
}
ostream& operator << (ostream& out,const Date& d)//��Ԫ����û��Ĭ�ϵ�
{
	out << d.a << d.b << endl;
	return out;
}
istream& operator >> (istream& in,  Date& d)//��Ԫ����û��Ĭ�ϵ�
{
	in >> d.a >> d.b;
	return in;
}
int main()
{
	Date a;
	f(a);
	// cout-> ostream
	// cin -> istream
	
	cin >> a;
	cout << a; // operator << (cout,a);
}
//class Sum
//{
//public:
//    Sum()
//    {
//        total += i;
//        ++i;
//    }
//    static void SumInIt()
//    {
//        total = 0;
//        i = 1;
//    }
//    static int GetSum()
//    {
//        return total;
//    }
//private:
//    static int total;
//    static int i;
//};
//int Sum::total = 0;
//int Sum::i = 1;
//class Solution {
//public:
//    int Sum_Solution(int n) 
//    {
//        Sum::SumInIt();
//        Sum* p = new Sum[n];
//        return Sum::GetSum();
//    }
//private:
//};
//
//
//
//
//int main()
//{
//    Solution sol;
//    cout <<sol.Sum_Solution(5) << endl;
//    cout << sol.Sum_Solution(5) << endl;
//
//	return 0;
//}


//�ٴ�����װ
//C++�ǻ����������ĳ�������������������Լ�:��װ���̳С���̬��
//C++ͨ���࣬��һ���������������Ϊ�����һ��ʹ����������Ƕ���һ���������֪�������ڸö������
//�ж��������һ�� : ͨ�������޶���ѡ���ԵĽ��䲿�ֹ��ܿ��ų���������������н����������ڶ����ڲ�
//��һЩʵ��ϸ�ڣ��ⲿ�û�����Ҫ֪����֪������Щ�����Ҳû�ã�����������ʹ�û���ά�����Ѷȣ�����
//�����鸴�ӻ���
#endif
#if 0
int globalVar = 1;
static int staticGlobalVar = 1;
void Test()
{
	static int staticVar = 1;
	int localvar = 1; 

	int num1[10] = { 1,2,3,4 };
	char char2[] = "abcd";
	char* pChar3 = char2;
	int* ptr1 = (int*)malloc(sizeof(int) * 4);
	int* ptr2 = (int*)calloc(4, sizeof(int));
	int* ptr3 = (int*)realloc(ptr2, sizeof(int) * 4);
	free(ptr1);
	free(ptr3);
}
//1.ѡ����:
//ѡ��:A.ջB.�� c.���ݶ� D.�����
//globalvar������ __   staticGlobalvar������ __
//staticvar������ __    localvar������ __
//num1 ������ __
//
//char2������ __      *char2������ __
//pChar3������ __     * pChar3������ __
//ptr1������ __		* ptr1������ __
//
//2.����� :
//sizeof(num1) = __;
//sizeof(char2) = ___;   strlen(char2) = _;
//sizeof(pChar3) = ___;   strlen(pChar) = ____;

//C++֮�ڴ����
int globalVar = 1;
static int staticGlobalVar = 1;
void Test()
{
	static int staticVar = 1;
	int localvar = 1;

	int num1[10] = { 1,2,3,4 };
	char char2[] = "abcd";
	char* pChar3 = "abcd";
	int* ptr1 = (int*)malloc(sizeof(int) * 4);
	int* ptr2 = (int*)calloc(4, sizeof(int));
	int* ptr3 = (int*)realloc(ptr2, sizeof(int) * 4);
	free(ptr1);
	free(ptr3);
}
//1.ѡ����:
//ѡ��:A.ջ B.�� C.���ݶ� D.�����
//globalvar������ __   staticGlobalvar������ __
//staticvar������ __    localvar������ __
//num1 ������ __
//
//char2������ __ * char2������ __
//pChar3������ __ * pChar3������ __
//ptr1������ __ * ptr1������ __
//
//2.����� :
//sizeof(num1) = __;
//sizeof(char2) = ___;   strlen(char2) = _;
//sizeof(pChar3) = ___;   strlen(pChar) = ____;
//
//�Ȳ�Ҫ�����濴�Լ���������һ�£����ܹ����Լ��������Լ�ѧϰ���顣
//
//֪ʶ��ܶ�һ��Ҫϸ�Ŀ�
//
//1 - 3. globalvar������ _C_   staticGlobalvar������ _C_ staticvar������ _C_ ���������
//
//ͨ������������� : ȫ�ֱ�����static������ʲô���� ?
//
//ȫ�ֱ�������̬�����Ƿ������ݶ��У�C���ԵĽǶȽо�̬����������globalvar���� C �У� staticGlobalvar����C�У� staticvar�Ǿֲ��ľ�̬����Ҳ�����ھ�̬��������Ҳ����C�У�   ���������й�ͬ�����������������ڼ䶼�� ��������ȫ�ֱ���globalvar����̬����staticGlobalvar��main����֮ǰ���ʼ������������ȫ�ֵ����Ķ���ʹ�ã��ֲ���̬����staticvar�������е�main�����ٳ�ʼ��������������Test������ֻ����Test������ʹ�á���globalvar��staticGlobalvar�����������������Բ�һ����globalvar�������ļ��пɼ�����staticGlobalvarֻ�ڵ�ǰ�ļ��ɼ�
//
//4 - 5. localvar������ _A_   num1 ������ _A_
//
//localvar�������ľֲ��������Դ���A(ջ)�еģ�num1��һ���ֲ���������������Ҳ����A(ջ)�е�
//
//6 - 11�� char2������ _A_ * char2������ _A_                 pChar3������ _A_
//
//* pChar3������ _D_                  ptr1������ _A_ * ptr1������ _B_
//
//char2��������ջ�ϵ��ַ��������abcd + '\0'����5���ֽڣ�����Ҳ����A(ջ)�еģ� * char2��ȡ��ַ����ȡ�������ַ��ĵ�ַ�����������ھֲ�����Ҳ����A(ջ)�е�, pChar3��һ��ָ�����Ҳ��һ���ֲ���������Ҳ����A(ջ)�е�, * pChar3��pChar3�����һ���ַ��������ĵ�ַ��* pChar3ָ�������ַ�����ݣ�����* pChar3��D(�����)�С�ptr1������������ǳ����׻�������һῴ���濪���˿ռ����Ի���Ϊ�ڶ��У�ptr1��int* ptrֻ�� = ǰ��������һ���ֲ�������ָ�룬����Ҳ����A(ջ)�е�, ��* ptr1ָ������ݲ��ǿ��ٳ����ģ���������B(��)��
//
//�ܽ᣺
//
//ȫ�ֱ�������̬�����Ƿ������ݶ��еģ������ľֲ��������ַ����ַ����飨char* ����ȡ��ַ��* ptr������ջ�еģ�ȡ��ַָ��ĵ�ַ�ǿ��ٳ����ľ��ڶ��У���Ȼ�ʹ��ڴ�����У�
//
//2.����� :
//sizeof(num1) = _40_;
//sizeof(char2) = _5__;   strlen(char2) = _4__;
//sizeof(pChar3) = _4��8__;   strlen(pChar) = _4___;  sizeof(ptr1) = ___;
//
//sizeof�Ǽ����ֽ�����
//
//sizeof(num1) ��num1[10] = { 1,2,3,4 }����Ȼֻ��4��ʼ����������������10������������40���ֽڡ�
//sizeof(char2)��char char2[] = "abcd"; ��4���ֽڵ��ǻ���\0������5���ֽڡ�
//strlen(char2)��strlen������\0����������4���ֽڡ�
//sizeof(pChar3) ��char * pChar3 = "abcd"; pChar3��һ��ָ�룬������4��8������32 / 64λ��
//strlen(pChar)ͬ��������\0����������4���ֽڡ�
//sizeof(ptr1)��int * ptr1 = (int*)malloc(sizeof(int) * 4); ptr1��һ��ָ�룬����Ҳ��4��8������32 / 64λ��

#endif

#if 0
//C���Ժ�C++�ж�̬�ڴ����ʽ
void Test()
{
int* p1 = (int*)malloc(sizeof(int));
free(p1);
// 1.malloc/calloc/realloc��������ʲô?
int* p2 = (int*)calloc(4, sizeof(int));
int* p3 = (int*)realloc(p2, sizeof(int) * 10);
// ������Ҫfree(p2)��?//����Ҫp2�Ŀռ��Ѿ����ݸ�p3��ֱ��free��p3����
free(p3)
}
malloc / calloc / realloc���� ?

malloc������һ���ڴ�ռ䣬calloc����һ���ڴ�ռ䲢��ʼ��Ϊ0��realloc�Ƕ����е��ڴ�ռ�������ݡ�

C + �ڴ����ʽ

C���ڴ����ʽ��C++�п��Լ���ʹ�ã�����Щ�ط�������Ϊ������ʹ�������Ƚ��鷳�����C++��������Լ����ڴ����ʽ:ͨ��new / delete�������ж�̬�ڴ����

int main()
{
	// C ����
	int* p1 = (int*)malloc(sizeof(int));
	int* p3 = (int*)malloc(sizeof(int) * 10);

	free(pl);
	free(p3);

	// C++ ������
	//int* p2 = new int;
	int* p2 = new int(10);// ����һ��int4���ֽڿռ䣬��ʼ����10
	int* p4 = new int[10];// ����10��int��40���ֽڿռ�
	delete p2;
	delete[] p4;
	return 0;
}
��Ȼc�������Ѿ�malloc��free��new��delete����������أ�

���������������ͣ����ǵ�Ч����һ���ġ�����ռ�
�����Զ������ͣ����ǵ�Ч���ǲ�һ���ġ�malloc����ռ䡢new����ռ� + ���캯����ʼ��
free�ͷſռ䣬delete�������� + �ͷſռ�
class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
}

int main()
{
	int* p1 = new int;
	int* p2 = (int*)malloc(sizeof(int));
}
�����������ͣ����ǵ�Ч����һ���ġ����ǿ����˿ռ�
�����Զ������ͣ�����˵����

class A
{
public:
	A()
	{
		_a = 0;
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
private:
	int _a;
}

int main()
{
	int* p1 = new int;
	int* p2 = (int*)malloc(sizeof(int));

	A* p2 = (A*)malloc(sizeof(A));  //����ռ�
	A* p3 = new A;                  //����ռ� + ���캯����ʼ��

	free(p3);                       //�ͷſռ�
	delete p4;                      //�������� + �ͷſռ�

	return 0;
}


#endif


#if 0
//C++�ڴ�й©��ν��
ʲô���ڴ�й©�أ�

�ڴ�й©ָ��Ϊ����������ɳ���δ���ͷ��Ѿ�����ʹ�õ��ڴ��������ڴ�й©������ָ�ڴ��������ϵ���ʧ������Ӧ�ó������ĳ���ڴ����Ϊ��ƴ���ʧȥ�˶Ըö��ڴ�Ŀ��ƣ����
������ڴ���˷ѡ�
�ڴ�й©��Σ�� : �������еĳ�������ڴ�й©��Ӱ��ܴ������ϵͳ����̨����ȵȳ����ڴ�й©�ᵼ����ӦԽ��Խ�������տ�����

������������1��G���ڴ�ռ䣬��������˻�����ԭ���ͷ�ָ��Ŀռ䣬�ͻᵼ���ڴ�й©��

int main()
{
	char* p = new char[1024 * 1024 * 1024];
	//û���ͷ� �ͻ��ڴ�й©
	//delete p;
	return 0;
}
��α����ڴ�й©
1.����ǰ�����õ���ƹ淶���������õı���淶��������ڴ�ռ����ƥ���ȥ�ͷš�ps:�������״̬��������������쳣ʱ������ע���ͷ��ˣ����ǿ��ܻ�����⡣��Ҫ��һ������ָ����������б�֤��
2.����RAII˼���������ָ����������Դ��
3.��Щ��˾�ڲ��淶ʹ���ڲ�ʵ�ֵ�˽���ڴ����⡣���׿��Դ��ڴ�й©���Ĺ���ѡ�
4.��������ʹ���ڴ�й©���߼�⡣ps; �����ܶ๤�߶��������ף������շѰ���
�ܽ�һ�� :
�ڴ�й©�ǳ����������������Ϊ����:1����ǰԤ���͡�������ָ��ȡ�2���º����͡���й©��⹤�ߡ�

��������⣺���һ���ڶ�������4G���ڴ棿
//����������x64�Ľ��̣���������ĳ�������?
#include <iostream>
using namespace std;
//x32λֻ��4g���ڴ�ռ� �������벻�� ����û���64λ��
int main()
{
	size_t n = 2;
	void* p = new char[n * 1024 * 1024 * 1024];
	cout << "new:" << p << endl;
	return 0;
}
#endif

//�����﷨(��:��������)+��Ͷ���(4����ҪĬ�ϳ�Ա����+���������)+���ͱ��:ģ��
//���һЩc�Խ���ò��û���û�н�������⡣
//1.���ǳ�ʼ��������   ���캯�� + ��������
//2.û�з�װ��˭�������޸Ľṹ������� ->�� + �����޶���
//3.�����ͬʱ��������ջ��һ��ջ��intһ��ջ��double������->ģ��
#if 0
int Add(int left, int right)
{
	return left + right;
}
template<class T>
T Add(const T& left, const T& right)
{
	return left + right;
}
int main()
{
	int a = 5, b = 10;
	double c = 20, d = 30;
	//��ʽʵ����
	Add(a, b);
	Add(c, d);
	//��ʽʵ����
	Add<int>(a, b);
	Add<double>(a, b);//����ǿת
}
#endif

#if 0 
template<class T>
class vector //��̬����������
{
public:
	vector()
	:_a(nullptr),_size(0),_capacity(0)
	{

	}
	vector(size_t n)//����
		:_a(new T[n]), _size(0), _capacity(0)
	{

	}
	~vector()
	{
		delete[] _a;
		_a = nullptr;
		_size = _capacity = 0;
	}
	void Push_Back(const T& x);//�������þ������� ���ٿ���
	
	void Pop_Back();

	size_t size()
	{
		return _size;
	}
	T& operator[](size_t& i)//���ô��� 1���޸Ĵ��ݵ�ʵ�α���swap      2�����ٿ���
	{					    //���ô�����ֵ:2���޸ķ��ض�����operator] 2�����ٿ���
		assert(i < _size);
		return _a[i];
	}
private:
	T* _a;
	size_t _size;
	size_t _capacity;
};
template<class T>
void vector<T>::Pop_Back()
{
	assert(_size > 0);
		--size;
}
template<class T>
void vector<T>::Push_Back(const T& x)
{
	//����ռ䲻����Ҫ��������
	if (_size == _capacity)
	{
		size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
		T* tmp = new T[newcapacity];
		if (_a)
		{
			memcpy(tmp, _a, sizeof(T) * _size);
			delete[] _a;
		}
		_a = tmp;
		_capacity = newcapacity;
	}
	_a[_size] = x;
	++_size;
}
#endif
//int main()
//{
//	vector<int> v;
//	v.Push_Back(1);
//	v.Push_Back(2);
//	v.Push_Back(3);
//	v.Push_Back(4);
//
//	for (size_t i = 0; i < v.size(); i++)
//	{
//		v[i] *= 2;
//		cout << v[i] << " ";
//	}
//	cout << endl;
//
//	return 0;
//}


//�ַ���ת������
int firstUniqChar(string s) {
	int count[26] = { 0 };
	for (auto ch : s)
	{
		count[ch - 'a']++;
	}
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (count[s[i] - 'a'] == 1)
			return i;
	}
	return -1;
}

int main()
{
	string s = "loveleetcode";
	firstUniqChar(s);
}