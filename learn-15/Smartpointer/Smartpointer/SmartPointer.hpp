#pragma once
#include <iostream>
#include <mutex>
using namespace std;

namespace zh
{


	template<class T>
	class auto_ptr //������Դ���ͷ�
	{
		public:
			auto_ptr(T* ptr)
				:_ptr(ptr) {}
			//1. ����Ȩת�� ,�������ȱ�ݣ�һ�㹫˾�������ֹ
			//ȱ�� ap2 = ap1 ������ap1�������� ���ʾͻᱨ���������Ϥ�������Ծͻᱻ��
			auto_ptr(auto_ptr<T>& ap)
				:_ptr(ap._ptr)
			{
				ap._ptr = nullptr;
			}

			~auto_ptr()
			{
				if (_ptr)
				{
					delete _ptr;
					_ptr = nullptr;
				}
			}
			auto_ptr<T>& operator = (const auto_ptr<T>& ap)
			{
				if (this != &ap)
				{
					if (_ptr)
						delete _ptr;

					_ptr = ap._ptr;
					ap._ptr = nullptr;
				}
				return *this;
			}
			T& operator*()
			{
				return *_ptr;
			}
			T* operator->()
			{
				return _ptr;
			}
		private:
			T* _ptr;
	};


	template<class T>
	class unique_ptr //������Դ���ͷ�
	{
		public:
			unique_ptr(T* ptr)
				:_ptr(ptr) {}
			//2. ������ �򵥴ֱ� �Ƽ�ʹ��
			unique_ptr(auto_ptr<T>& up) = delete;
			unique_ptr<T>& operator = (const unique_ptr<T>& up) = delete;


			~unique_ptr()
			{
				if (_ptr)
				{
					delete _ptr;
					_ptr = nullptr;
				}
			}

			T& operator*()
			{
				return *_ptr;
			}
			T* operator->()
			{
				return _ptr;
			}
		private:
			T* _ptr;
	};



	template<class T>
	class shared_ptr //ָ�������
	{
		public:
			shared_ptr(T* ptr = nullptr)
				:_ptr(ptr)
				, _count(new int(1))
				,_mtx(new mutex)
			{}
			//2. ������ �򵥴ֱ� �Ƽ�ʹ��
			shared_ptr(const shared_ptr<T>& sp)
				:_ptr(sp._ptr)
				, _count(sp._count)
				, _mtx(sp._mtx)
			{
				add_ref_usecount();
			}

			//�������ü���������������һ��������Դ�Ķ������ͷ���Դ
			shared_ptr<T>& operator = (const shared_ptr<T>& sp)
			{
				if (this != &sp)
				{
					Release();
					//�ҿ�ʼ����һ�������Դ
					_ptr = sp._ptr;
					_count = sp._count;
					_mtx = sp._mtx;
					add_ref_usecount();

				}

				return *this;
			}
			void add_ref_usecount()
			{
				_mtx->lock();
				++(*_count);
				_mtx->unlock();

			}
			void Release()
			{
				_mtx->lock();
				bool flag = false;
			
				if (--(*_count) == 0 && _ptr)
				{
					cout << "delete��" << _ptr << endl;
					delete _ptr;
					_ptr = nullptr;

					delete _count;
					_count = nullptr;
					flag = true;
				}
				_mtx->unlock();
				if (flag)
				{
					delete _mtx;
					_mtx = nullptr;
				}
			}

			int use_count()
			{
				return *_count;

			}
			~shared_ptr()
			{
				Release();
			}

			// ��ָ��һ��ʹ��
			T& operator*()
			{
				return *_ptr;
			}
			T* operator->()
			{
				return _ptr;
			}
			T* get_ptr() const
			{
				return _ptr;
			}
		private:
			T* _ptr;
			int* _count; //��¼�ж��ٸ�����һ���������Դ�����һ�������ͷ���Դ
			mutex* _mtx;
	};

	//�ϸ���˵weak_ptr��������ָ�룬��Ϊ��û��RAII��Դ�������
	// ר�Ž��shared ptr��ѭ����������
	template<class T>
	class weak_ptr
	{
	public:
		weak_ptr() = default;
		weak_ptr(const shared_ptr<T>& sp)
			:_ptr(sp.get_ptr())
		{}
		weak_ptr<T>& operator = (const shared_ptr<T>& sp)
		{
			_ptr = sp.get_ptr();
			return *this;
		}
		// ��ָ��һ��ʹ��
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
		
	private:
		T* _ptr;
	};

}