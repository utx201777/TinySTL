#include <iostream>
#include "MyVector.h"
#include "MySet.h"

int main()
{	
	TinySTL::MyVector<int> v;
	for (int i = 0; i < 10; ++i)
		v.push_back(i);
	for (int i = 0; i < 10; ++i)
		printf("%d ", v[i]);
	printf("\n");
	TinySTL::MySet<int> s;
	s.insert(12);
	s.insert(4);
	s.insert(20);
	s.insert(15);
	for (auto it = s.begin(); it != s.end(); ++it)
		printf("%d ", *it);
	printf("%d\n", s.size());
	s.erase(15);	
	for (auto it = s.begin(); it != s.end(); ++it)
		printf("%d ", *it);
	printf("%d\n", s.size());
	printf("%d %d %d\n", s.exist(4), s.exist(6), s.exist(20));	
}