# TinySTL
## 空间配置器
1. 使用两级空间配置器，如果申请的空间小于128字节，使用内存池的内存分配，如果大于128字节，直接使用malloc分配`Alloc.h`
2. `SimpleAllocate.h`对`Alloc.h`进行封装，外部提供申请空间，构建，析构，释放空间的接口。其中构建使用的是`placement new`，析构直接调用析构函数

## vector
1. 使用`SimpleAllocate.h`进行空间配置，会将容量设置为元素个数的两倍，如果容量不足，重新分配，迭代器失效。
2. 提供`size()`，`empty()`，`push_back()`，`pop_back()`等接口并提供迭代器访问

## set
1. 底层使用BST实现，后面会改成AVL树或者RB树，空间配置使用`SimpleAllocate.h`
2. 提供前后访问的迭代器
3. 已经改用AVL树实现

## stack
1. 底层使用`vector`，封装只有尾部可以读写。