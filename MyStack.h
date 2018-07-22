#pragma once
#include "MyVector.h"
namespace TinySTL
{
	template<class T, class Container = MyVector<T>>
	class MyStack
	{
	public:
		typedef typename Container::value_type value_type;
		typedef typename Container::reference reference;
		typedef typename Container::size_type size_type;
		typedef Container container_type;
	private:
		container_type container;
	public:
		explicit MyStack():container(container_type()) {}
		bool empty()
		{
			return container.empty();
		}
		size_type size()
		{
			return container.size();
		}
		value_type top()
		{
			return container.back();
		}
		void push(const value_type & value)
		{
			container.push_back(value);
		}
		void pop()
		{
			container.pop_back();
		}
	};
}