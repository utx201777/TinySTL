#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <cstdlib>
#include <cstdio>

namespace TinySTL{

/*
1. 按照字节为单位分配空间，回收空间
2. 维护一个内存池和一个链表
3. 分配空间超过一定大小调用系统申请空间
4. 较小现在链表上查看是否有空间
5. 如果没有，则向内存池申请空间，一次申请多块，会挂在在链表上
6. 如果内存池空间不够申请，但至少可以申请一块，则全部返回，并将多余的挂在链表上
7. 如果内存池一块都申请不了，则把剩余内存挂在链表上别的位置，然后像系统申请空间
8. 如果系统申请成功，直接返回
9. 如果申请失败，则遍历链表，看看还有没有可用空间，将这些空间作为内存池
*/
	class alloc{
	private:
		enum EAlign{ ALIGN = 8};		// 小型区块的上调边界
		enum EMaxBytes{ MAXBYTES = 128};// 小型区块的上限，超过的区块由malloc分配
		enum ENFreeLists{ NFREELISTS = (EMaxBytes::MAXBYTES / EAlign::ALIGN)};
		enum ENObjs{ NOBJS = 20};		// 每次增加的节点数
	private:
		// 链表节点
		union obj
		{
			union obj *next;
			char client[1];
		};

		static obj *free_list[ENFreeLists::NFREELISTS];
	private:
		static char *start_free;	// 内存池起始位置
		static char *end_free;		// 内存池结束位置
		static size_t heap_size;	// 池子容量
	private:
		//将bytes上调至8的倍数
		static size_t ROUND_UP(size_t bytes)
		{
			return ((bytes + EAlign::ALIGN - 1) & ~(EAlign::ALIGN - 1));
		}
		//根据区块大小，决定使用第n号free-list，n从0开始计算
		static size_t FREELIST_INDEX(size_t bytes)
		{
			return (((bytes)+EAlign::ALIGN - 1) / EAlign::ALIGN - 1);
		}
		//返回一个大小为n的对象，并可能加入大小为n的其他区块到free-list
		static void *refill(size_t n);
		//配置一大块空间，可容纳nobjs个大小为size的区块
		//如果配置nobjs个区块有所不便，nobjs可能会降低
		static char *chunk_alloc(size_t size, size_t& nobjs);

	public:
		static void *allocate(size_t bytes);
		static void deallocate(void *ptr, size_t bytes);
		static void *reallocate(void *ptr, size_t old_sz, size_t new_sz);
	};
}

#endif