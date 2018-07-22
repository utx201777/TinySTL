#pragma once
#include "SimpleAllocate.h"

namespace TinySTL
{
	template<class T>
	class MyVector
	{
	public:
		typedef T value_type;
		typedef size_t size_type;
		typedef value_type * pointer;
		typedef value_type * iterator;
		typedef value_type & reference;
	protected:
		typedef SimpleAllocate<T> alloc;
		iterator start;
		iterator finish;
		iterator end_of_storage;	// 存储区的结尾
		void fill_initialize(size_type n, const value_type & value)
		{
			start = alloc::allocate(2 * n);
			uninitialized_fill_n(start, n, value);
			finish = start + n;
			end_of_storage = start + 2 * n;		// 构建2n的大小
		}
	public:
		MyVector()
		{
			start = alloc::allocate(2);
			finish = start;
			end_of_storage = start + 2;
		}
		MyVector(size_type n, const T& value)
		{
			fill_initialize(n, value);
		}
		explicit MyVector(size_type n)
		{
			fill_initialize(n, T());
		}
		iterator begin()
		{
			return start;
		}
		iterator end()
		{
			return finish;
		}
		size_type size()
		{
			return size_type(end() - begin());
		}
		bool empty()
		{
			return size() == 0;
		}
		size_type capacity()
		{
			return size_type(end_of_storage - begin());
		}
		reference front()
		{
			return *begin();
		}
		reference back()
		{
			return *(end() - 1);
		}
		void push_back(const value_type& x)
		{
			if (finish != end_of_storage)
			{
				alloc::construct(finish++, x);
			}
			else
			{
				int new_capacity = capacity() * 2;
				auto new_start = alloc::allocate(new_capacity);
				uninitialized_copy(start, finish, new_start);		// 拷贝
				auto p = start;
				while (p != finish)									// 析构
					alloc::destroy(p++);
				alloc::deallocate(start, finish - start);			// 释放原来的内存
				start = new_start;
				finish = start + new_capacity / 2;
				end_of_storage = start + new_capacity;
				push_back(x);		// 再调用push_back
			}
		}

		// 重载随机[]运算符
		reference operator [](unsigned idx)
		{
			return *(begin() + idx);
		}

		void pop_back()
		{
			if (finish != start)
				alloc::destroy(--finish);
		}
		void clear()
		{
			while (finish != start)
				alloc::destroy(--finish);
		}
		~MyVector()
		{
			auto p = start;
			while (p != finish)									// 析构
				alloc::destroy(p++);
			alloc::deallocate(start, finish - start);
		}
	};
}
