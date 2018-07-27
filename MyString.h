#pragma once

#include <cstring>
#include <iostream>

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
		MyString(const char * str = nullptr)
		{
			if (str == nullptr)
			{
				data = new char[1];
				data[0] = '\0';
			}
			else
			{
				data = new char[strlen(str) + 1];
				strcpy(data, str);		// 会拷贝
			}
		}
		MyString(MyString &s)
		{
			data = new char[strlen(s.data) + 1];
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
			char * tmp_data = new char[strlen(data) + strlen(s.data) + 1];
			strcpy(tmp_data, data);
			strcpy(tmp_data + strlen(data), s.data);
			tmp.data = tmp_data;
			return tmp;
		}		
		~MyString()
		{
			delete[]data;
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
		char * data = new char[MAXSIZE];
		infs.getline(data, MAXSIZE);
		MyString tmp;
		tmp.data = s.data;		// 释放前面的
		s.data = new char[strlen(data) + 1];
		strcpy(s.data, data);
		delete []data;
		return infs;
	}
}
