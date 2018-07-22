#pragma once

#include "SimpleAllocate.h"
#include "BSTree.h"

namespace TinySTL
{
	template<class T>
	class MySet
	{
	public:
		typedef T value_type;
		typedef BSTree<T> * bstree_ptr;
		typedef BSTree<T> bstree;
		typedef typename BSTree<T>::iterator iterator;
		typedef typename BSTree<T>::size_type size_type;
	protected:
		bstree_ptr tree;
	public:
		MySet() :tree(new bstree()) {}
		size_type size()
		{
			return tree->size();
		}
		bool empty()
		{
			return tree->empty();
		}
		iterator begin()
		{
			return tree->begin();
		}
		iterator end()
		{
			return tree->end();
		}
		iterator find(value_type value)
		{
			return tree->find(value);
		}
		bool erase(value_type value)
		{
			return tree->erase(value);
		}
		bool insert(value_type value)
		{
			return tree->insert(value);
		}
	};
}