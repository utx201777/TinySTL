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
}