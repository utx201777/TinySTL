#include <iostream>
#include <vector>
#include "Alloc.h"
#include "MyString.h"
#include "SimpleAllocate.h"
using namespace std;

int main()
{		
	TinySTL::MyString ms("abcdef");
	cout << ms << endl;
	cin >> ms;
	cout << ms << endl;
}