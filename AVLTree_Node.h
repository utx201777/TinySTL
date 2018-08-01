#pragma once
#include "SimpleAllocate.h"

namespace TinySTL
{
	template<class T>
	struct AVLTree_Node
	{
		typedef T value_type;
		typedef size_t size_type;
		typedef AVLTree_Node<T> * node_ptr;
		int height;
		value_type key;		
		node_ptr _left;
		node_ptr _right;
		node_ptr _parent;
		AVLTree_Node()
		{
			_left = nullptr;
			_right = nullptr;
			_parent = nullptr;
		}
	};

	template<class T>
	int Height(AVLTree_Node<T> *r)
	{
		if (r==nullptr)
			return -1;
 		return r->height;
	}

	template<class T>
	T max(T a, T b)
	{
		if (a > b)
			return a;
		return b;
	}

	template<class T>
	T abs(T a)
	{
		if (a < 0)
			return -a;
		return a;
	}
	template<class T>
	AVLTree_Node<T> * singleRotateLeft(AVLTree_Node<T>* root);

	template<class T>
	AVLTree_Node<T> * singleRotateRight(AVLTree_Node<T>*root);

	template<class T>
	AVLTree_Node<T>* doubleRotateLeft(AVLTree_Node<T>*root);

	template<class T>
	AVLTree_Node<T>* doubleRotatoRight(AVLTree_Node<T>*root);

	template<class T>
	AVLTree_Node<T>* insertAVLTree(AVLTree_Node<T> *&root, AVLTree_Node<T> *parent, T value);

	template<class T>
	AVLTree_Node<T>* findMin(AVLTree_Node<T> * root);

	template<class T>
	AVLTree_Node<T>* Fix(AVLTree_Node<T> *root);

	template<class T>
	AVLTree_Node<T>* deleteAVLNode(AVLTree_Node<T> *&root, AVLTree_Node<T>*parent, T value);

	template<class T>
	void MidTraverse(AVLTree_Node<T> *root);

	template<class T>
	AVLTree_Node<T> *findNode(AVLTree_Node<T> *root, T value);

	template<class T>
	AVLTree_Node<T>* findNext(AVLTree_Node<T>*root);

	template<class T>
	AVLTree_Node<T>* findPre(AVLTree_Node<T>*root);

	template<class T>
	AVLTree_Node<T> * singleRotateLeft(AVLTree_Node<T>* root)
	{
		typedef AVLTree_Node<T> * node_ptr;
		node_ptr tmp = root->_left;	// 旋转的部分
		root->_left = tmp->_right;
		tmp->_right->_parent = root;	
		tmp->_right = root;
		root->_parent = tmp;
		root->height = max<int>(Height(root->_left), Height(root->_right))+1;
		tmp->height = max<int>(Height(tmp->_left), Height(tmp->_right))+1;
		return tmp;
	}

	template<class T>
	AVLTree_Node<T> * singleRotateRight(AVLTree_Node<T>*root)
	{
		typedef AVLTree_Node<T> * node_ptr;
		node_ptr tmp = root->_right;
		root->_right = tmp->_left;
		tmp->_left->_parent = root;
		tmp->_left = root;
		root->_parent = tmp;
		root->height = max<int>(Height(root->_left), Height(root->_right))+1;
		tmp->height = max<int>(Height(tmp->_left), Height(tmp->_right))+1;
		return tmp;
	}

	template<class T>
	AVLTree_Node<T>* doubleRotateLeft(AVLTree_Node<T>*root)
	{		
		root->_left = singleRotateRight(root->_left);
		root->_left->_parent = root;
		return singleRotateLeft(root);
	}

	template<class T>
	AVLTree_Node<T>* doubleRotatoRight(AVLTree_Node<T>*root)
	{
		root->_right = singleRotateLeft(root->_right);
		root->_right->_parent = root;
		return singleRotateRight(root);
	}

	template<class T>
	AVLTree_Node<T>* insertAVLTree(AVLTree_Node<T> *&root, AVLTree_Node<T> *parent, T value)
	{		
		if (root == nullptr)
		{			
			root = new AVLTree_Node<T>();
			root->key = value;
			root->_parent = parent;
		}
		else
		{
			if (root->key > value)
			{
				root->_left = insertAVLTree(root->_left, root, value);
				root->_left->_parent = root;
				if (Height(root->_left) - Height(root->_right) >= 2)
				{
					if (root->_left->key < value)
					{					
						root = doubleRotateLeft(root);
						root->_parent = parent;
					}
					else
					{
						root = singleRotateLeft(root);
						root->_parent = parent;
					}
				}				
			}
			else if (root->key < value)
			{
				root->_right = insertAVLTree(root->_right, root, value);
				root->_right->_parent = root;
				if (Height(root->_right) - Height(root->_left) >= 2)
				{
					if (root->_right->key < value)
					{
						root = doubleRotatoRight(root);
						root->_parent = parent;
					}
					else
					{
						root = singleRotateRight(root);
						root->_parent = parent;
					}
				}
			}
			else
				return root;
		}
		root->height = max<int>(Height(root->_left), Height(root->_right)) + 1;
		return root;
	}

	template<class T>
	AVLTree_Node<T>* findMin(AVLTree_Node<T> * root)
	{
		if (root != nullptr)
		{
			while (root->_left != nullptr)
				root = root->_left;
		}
		return root;
	}

	template<class T>
	AVLTree_Node<T>* Fix(AVLTree_Node<T>* root)
	{
		if (Height(root->_left) > Height(root->_right))
		{
			//左儿子的左儿子的高度大于左儿子的右儿子的高度, 执行左单旋转, 否则执行左-右双旋转
			if (Height(root->_left->_left) > Height(root->_left->_right))
				root = singleRotateLeft(root);
			else if (Height(root->_left->_left) < Height(root->_left->_right))
				root = doubleRotatoRight(root);
		}
		else if (Height(root->_left) < Height(root->_right))
		{
			//右儿子的右儿子的高度大于右儿子的左儿子的高度, 执行右单旋转, 否则执行右-左双旋转
			if (Height(root->_right->_right) > Height(root->_right->_left))
				root = singleRotateRight(root);
			else if (Height(root->_right->_right) < Height(root->_right->_left))
				root = doubleRotatoRight(root);
		}
		return root;
	}

	template<class T>
	AVLTree_Node<T>* deleteAVLNode(AVLTree_Node<T> *&root, AVLTree_Node<T>*parent, T value)
	{		
		AVLTree_Node<T> * ptr;
		if (root == nullptr)
			return nullptr;
		// 找到当前节点
		if (root->key == value)
		{
			if (root->_left && root->_right)
			{
				ptr = findMin(root->_right);
				root->key = ptr->key;
				root->_right = deleteAVLNode(root->_right, root, root->key);				
			}
			else
			{
				ptr = root;
				if (root->_left != nullptr)
				{
					root = root->_left;
					root->_parent = parent;
				}					
				else if (root->_right != nullptr)
				{
					root = root->_right;
					root->_parent = parent;
				}
				else
				{
					root = nullptr;
					// 这时候需要把root置nullptr，否则指向的内存以及被释放了会出错
				}
				delete ptr;
				ptr = nullptr;
			}			
		}
		else
		{
			if (root->key < value)
				root->_right = deleteAVLNode(root->_right, root, value);
			else
				root->_left = deleteAVLNode(root->_left, root, value);
		}
		if (root)
		{
			root->height = max<int>(Height(root->_left), Height(root->_right)) + 1;
			if (abs<int>(Height(root->_left) - Height(root->_right))>=2)
			{
				root = Fix(root);
				root->_parent = parent;
				root->height = max<int>(Height(root->_left), Height(root->_right)) + 1;
			}
		}
		return root;
	}

	template<class T>
	void MidTraverse(AVLTree_Node<T> *root)
	{
		if (root == nullptr)
			return;
		MidTraverse(root->_left);
		cout << root->key << " ";
		MidTraverse(root->_right);
	}

	template<class T>
	AVLTree_Node<T> *findNode(AVLTree_Node<T> *root, T value)
	{
		if (root == nullptr)
			return nullptr;
		if (value == root->key)
			return root;
		if (value < root->key)
			return findNode(root->_left, value);
		else
			return findNode(root->_right, value);
	}

	template<class T>
	AVLTree_Node<T>* findNext(AVLTree_Node<T>*root)
	{
		if (root == nullptr)
			return root;
		if (root->_right != nullptr)
		{
			// 找到最左节点
			root = root->_right;
			while (root->_left)
				root = root->_left;
			return root;
		}
		else
		{
			// 找到是父节点的左子节点的第一个
			while (root->_parent && root->_parent->_right == root)
				root = root->_parent;
			return root->_parent;
		}
	}

	template<class T>
	AVLTree_Node<T>* findPre(AVLTree_Node<T>*root)
	{
		if (root == nullptr)
			return root;
		if (root->_left != nullptr)
		{
			// 找到最右节点
			root = root->_left;
			while (root->_right)
				root = root->_right;
			return root;
		}
		else
		{
			while (root->_parent && root->_parent->_left == root)
				root = root->_parent;
			return root->_parent;
		}
	}

	template<class T>
	struct AVLTree_Node_Iterator
	{
		typedef T value_type;
		typedef AVLTree_Node<T> * node_ptr;
		typedef AVLTree_Node<T> node_type;
		AVLTree_Node_Iterator<T> operator++(int);		// 后置
		AVLTree_Node_Iterator<T> operator++();
		AVLTree_Node_Iterator<T> operator--(int);
		AVLTree_Node_Iterator<T> operator--();
		AVLTree_Node_Iterator(node_ptr it) :ptr(it) {}
		node_ptr ptr;
		bool operator ==(const AVLTree_Node_Iterator<T> & a)
		{
			return ptr == a.ptr;
		}
		bool operator !=(const AVLTree_Node_Iterator<T> & a)
		{
			return ptr != a.ptr;
		}
		value_type operator*()
		{
			return ptr->key;
		}
	};


	template<class T>
	AVLTree_Node_Iterator<T> AVLTree_Node_Iterator<T>::operator++(int)
	{
		auto res = ptr;
		ptr = findNext(ptr);
		return AVLTree_Node_Iterator<T>(res);
	}

	template<class T>
	AVLTree_Node_Iterator<T> AVLTree_Node_Iterator<T>::operator++()
	{
		ptr = findNext(ptr);
		return *this;
	}

	template<class T>
	AVLTree_Node_Iterator<T> AVLTree_Node_Iterator<T>::operator--(int)
	{
		auto res = ptr;
		ptr = findPre(ptr);
		return AVLTree_Node_Iterator<T>(res);
	}

	template<class T>
	AVLTree_Node_Iterator<T> AVLTree_Node_Iterator<T>::operator--()
	{
		ptr = findPre(ptr);
		return *this;
	}
}