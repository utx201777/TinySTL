#pragma once
#include "AVLTree_Node.h"

namespace TinySTL
{
	template<class T>
	class AVLTree
	{
	public:
		typedef T value_type;
		typedef AVLTree_Node_Iterator<T> iterator;
		typedef typename iterator::node_type node_type;
		typedef typename iterator::node_type* node_ptr;
		typedef typename iterator::node_type*& node_ptr_reference;
		typedef size_t size_type;
		typedef SimpleAllocate<node_type> alloc;
	protected:
		node_ptr head;
		size_type size_;
		node_ptr_reference root()
		{
			return head->_right;
		}
	public:
		// head的right存储的是根节点，left存储的是begin节点，end节点为空结点
		AVLTree()
		{
			head = new node_type();
			size_ = 0;
		}
		~AVLTree()
		{
			delete head;
		}
		size_type size()
		{
			return size_;
		}
		bool empty()
		{
			return size() == 0;
		}
		iterator begin()
		{
			return iterator(head->_left);
		}
		iterator end()
		{
			return iterator(nullptr);
		}
		void insert(value_type value)
		{
			insertAVLTree<T>(root(), head, value);
			auto r = root();
			while (r != nullptr && r->_left != nullptr)
				r = r->_left;
			head->_left = r;		// 更新begin()
			++size_;			
		}
		void erase(value_type value)
		{
			deleteAVLNode<T>(root(), head, value);
			auto r = root();
			if (r == nullptr)
				head->_left = nullptr;			// 已经没有节点了
			while (r != nullptr && r->_left != nullptr)
				r = r->_left;
			head->_left = r;
			--size_;			
		}
		iterator find(value_type value)
		{
			auto res = findNode<T>(root(), value);
			if (res == nullptr)
				return iterator(end());
			return iterator(res);
		}
	};
}
