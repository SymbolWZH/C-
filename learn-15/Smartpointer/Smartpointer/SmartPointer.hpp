#pragma once
#include <iostream>
#include <mutex>
using namespace std;

namespace zh
{


	template<class T>
	class auto_ptr //管理资源的释放
	{
		public:
			auto_ptr(T* ptr)
				:_ptr(ptr) {}
			//1. 管理权转移 ,早期设计缺陷，一般公司都明令禁止
			//缺陷 ap2 = ap1 场景下ap1就悬空了 访问就会报错，如果不熟悉他的特性就会被坑
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
	class unique_ptr //管理资源的释放
	{
		public:
			unique_ptr(T* ptr)
				:_ptr(ptr) {}
			//2. 防拷贝 简单粗暴 推荐使用
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
	class shared_ptr //指针计数器
	{
		public:
			shared_ptr(T* ptr = nullptr)
				:_ptr(ptr)
				, _count(new int(1))
				,_mtx(new mutex)
			{}
			//2. 防拷贝 简单粗暴 推荐使用
			shared_ptr(const shared_ptr<T>& sp)
				:_ptr(sp._ptr)
				, _count(sp._count)
				, _mtx(sp._mtx)
			{
				add_ref_usecount();
			}

			//减减引用计数，如果我是最后一个管理资源的对象，则释放资源
			shared_ptr<T>& operator = (const shared_ptr<T>& sp)
			{
				if (this != &sp)
				{
					Release();
					//我开始跟你一起管理资源
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
					cout << "delete：" << _ptr << endl;
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

			// 像指针一样使用
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
			int* _count; //记录有多少个对象一起共享管理资源，最后一个析构释放资源
			mutex* _mtx;
	};

	//严格来说weak_ptr不是智能指针，因为他没有RAII资源管理机制
	// 专门解决shared ptr的循环引用问题
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
		// 像指针一样使用
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