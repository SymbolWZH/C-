#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
namespace zh
{
	template<class T>
class vector
{
public:
	typedef T* iterator;
	typedef T* const_iterator;
	vector()
		:_start(nullptr), _finish(nullptr), _endofstorage(nullptr)
	{

	}
	/*vector(const vector<T>& v)
	{ 
		_start = new T[v.capacity];
		_finish = _start;
		_endofstorage = _start + v.capacity();

		for (size_t i = 0; i < v.size(); i++)
		{
			*_finish = v[i];
			++_finish;
		}
		
	}*/
	//v2(v1)
	vector( vector<T>& v)
	:_start(nullptr), _finish(nullptr), _endofstorage(nullptr)
	{
		
		reserve(v.capacity());
		for (const auto&e : v)
		{
			push_back(e);
		}

	}
	iterator begin()
	{
		return _start;
	}
	iterator end()
	{
		return _finish;
	}
	const_iterator begin() const
	{
		return _start;
	}
	const_iterator end() const
	{
		return _finish;
	}
	T& operator[](size_t i)
	{
		assert(i < size());
		return _start[i];
	}
	//v1 = v3
	/*vector<T>& operator = (const vector<T>&v)
	{
		if (this != &v)
		{
			delete[] _start;
			_start = new T[v.capacity()];
			memcpy(_start, v._start, sizeof(T) * v.size());
		}
		return *this;
	}*/
	//v1 = v3
	vector<T>& operator = ( vector<T>& v)
	{
		swap(v);
		return *this;
	}
	void swap(vector<T>& v)
	{
		::swap(_start, v._start);
		::swap(_finish, v._finish);
		::swap(_endofstorage, v._endofstorage);
	}
	~vector()
	{
		delete[] _start;
		_start = _finish = _endofstorage = nullptr;
	}
	const T& operator[](size_t i) const
	{
		assert(i < size());
		return _start[i];
	}
	void reserve(size_t n) 
	{
		if (n > capacity())
		{
			size_t sz = size();
			T* tmp = new T[n];
			if (_start)
			{
				//memcpy(tmp, _start, sizeof(T) * size());//���ֽڿ��� ǳ����
				for (size_t i = 0; i < sz; i++)
				{
					tmp[i] = _start[i]; //���õ���<T>��operator= ���
				}
				delete[] _start;
			}
			_start = tmp;
			_finish = tmp + sz;
			_endofstorage = tmp + n;
		}
	}
	void resize(size_t n, const T& val = T())
	{
		if (n < size())
		{
			_finish = _start + n;
		}
		else
		{
			if (n > capacity())
			{
				reserve(n);
			}
			while (_finish < _start + n)
			{
				*_finish = val;
				++_finish;
			}
		}
	}
	void pop_back()
	{
		/*assert(_start < _finish);
		--_finish;*/
		erase(_finish - 1);
	}
	void erase(iterator pos)
	{
		assert(pos < _finish);

		iterator it = pos;
		while (it <_finish)
		{
			*it = *(it + 1);
			++it;
		}
		--_finish;
	}
	void insert( iterator pos,const T&x)
	{
		assert(pos <= _finish);
		if (_finish == _endofstorage)
		{
			size_t sz = pos - _start;
			size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
			reserve(newcapacity);
			//�������ԭ����pos��ʧЧ�ˣ�������Ҫ���¼���λ��
			pos = _start + sz;
		}
		
		iterator end = _finish - 1;
		while (end >= pos)
		{
			*(end + 1) = *end;
			--end;
		}
		*pos = x; 
		++_finish;
	}
	void push_back(const T& x)
	{
		/*if (_finish == _endofstorage)
		{
			size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
			reserve(newcapacity);
		}
		*_finish = x;
		++_finish;*/
		insert(_finish,x);
	}
	size_t size()
	{
		return _finish - _start;
	}
	size_t capacity()
	{
		return _endofstorage - _start;
	}
private:
	iterator _start;//��һ��λ��
	iterator _finish;//���һ��λ����һ��
	iterator _endofstorage;//start+ capacity
};

void test_iterator()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);

	vector<int>::iterator it = v.begin();

	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
}
void print_vector(const vector<int>& v)
{
	vector<int>::const_iterator it = v.begin();

	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
}

//Ϊʲô����list
//����vector��ȱ����ڵ�
//vectorȱ�� :
//1��ͷ�����в��Ĳ���ɾ��Ч�ʵ͡�0(N), ��Ϊ��ҪŲ�����ݡ�
//2���������ݿռ䲻����Ҫ���ݡ�������Ҫ���¿ռ䡢�������ݡ��ͷžɿռ䣬�Ḷ���ܴ�Ĵ��ۡ�
//�ŵ� :
//1��֧���±��������ʡ� ��ӵľͺܺõ�֧�����򡢶��ֲ��ҡ����㷨�ȵȡ�

//list��������Ϊ�˽��vectorȱ��
//�ŵ�
//1��listͷ�����м���벻����ҪŲ�����ݣ�Ч�ʸߡ�0(1)
//2��list���������������ڵ㣬����Ҫ���ݡ�
//ȱ��
//1����֧��������ʡ�
//����ʵ��ʹ����vectorlist�ศ��ɵ���������