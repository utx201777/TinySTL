#pragma once

#include "SimpleAllocate.h"
#include "AVLTree.h"
#include "BSTree.h"

namespace TinySTL
{
	template<class T>
	class MySet
	{
	public:
		typedef T value_type;
		typedef AVLTree<T> tree_type;
		typedef tree_type * tree_ptr;
		typedef typename tree_type::iterator iterator;
		typedef typename tree_type::size_type size_type;
		typedef SimpleAllocate<tree_type> alloc;
	protected:
		tree_ptr tree;
	public:
		MySet()
		{
			tree = alloc::allocate(1);
			alloc::construct(tree, tree_type());
		}
		~MySet()
		{
			alloc::destroy(tree);
			alloc::deallocate(tree, 1);
		}
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
		void insert(value_type value)
		{
			tree->insert(value);
		}
	};
}