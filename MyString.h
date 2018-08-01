#pragma once

#include <cstring>
#include <iostream>
#include "SimpleAllocate.h"
namespace TinySTL
{
	const unsigned MAXSIZE = 10000;
	class MyString
	{
	public:
		typedef char value_type;
		typedef value_type * pointer;
		typedef value_type * iterator;
		typedef value_type & reference;
		typedef SimpleAllocate<value_type> alloc;
		MyString(const char * str = nullptr)
		{
			if (str == nullptr)
			{
				data = alloc::allocate(1);
				data[0] = '\0';
			}
			else
			{				
				data = alloc::allocate(strlen(str) + 1);
				strcpy(data, str);		// 会拷贝
			}
		}
		MyString(MyString &s)
		{
			data = alloc::allocate(strlen(s.data) + 1);			
			strcpy(data, s.data);
		}
		value_type operator[](unsigned index)
		{
			return data[index];
		}
		iterator begin()
		{
			return data;
		}
		iterator end()
		{
			return &data[strlen(data)];
		}
		MyString & operator=(MyString &s)
		{
			if (this != &s)
			{
				MyString tmp(s);
				auto tmp_s = tmp.data;
				tmp.data = data;		// 生成一个临时对象，会将原来的地址释放
				data = tmp_s;
			}
			return *this;
		}
		MyString operator + (MyString &s)
		{
			MyString tmp;
			char * tmp_data = alloc::allocate(strlen(data) + strlen(s.data) + 1);
			strcpy(tmp_data, data);
			strcpy(tmp_data + strlen(data), s.data);
			tmp.data = tmp_data;
			return tmp;
		}
		MyString operator+(const char * str)
		{
			MyString tmp(str);
			return *this + tmp;
		}
		~MyString()
		{			
			SimpleAllocate<char>::deallocate(data, strlen(data) + 1);
		}
		friend std::ostream &operator<<(std::ostream & onfs, const MyString & s);
		friend std::istream &operator >> (std::istream & infs, MyString &s);
	private:
		char * data;
	};

	std::ostream &operator<<(std::ostream & onfs, const MyString & s)
	{
		onfs << s.data;
		return onfs;
	}
	std::istream &operator >> (std::istream & infs, MyString &s)
	{
		typedef char value_type;
		typedef SimpleAllocate<value_type> alloc;
		char * data = alloc::allocate(MAXSIZE);
		infs.getline(data, MAXSIZE);
		MyString tmp;
		tmp.data = s.data;		// 释放前面的
		s.data = alloc::allocate(strlen(data) + 1);
		strcpy(s.data, data);
		alloc::deallocate(data, MAXSIZE);
		return infs;
	}
}
