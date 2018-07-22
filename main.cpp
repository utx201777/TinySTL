#include <iostream>
#include "MyVector.h"
#include "MySet.h"
#include "MyStack.h"
#include <vector>
#include <set>
#include <cstdarg>
using namespace std;

class Test
{
public:	
	int a;
	int b;
	Test(int a, int b)
	{
		this->a = a;
		this->b = b;
	}
	Test(int a, int b, int c,int d)
	{
		this->a = a;
		this->b = b;
	}
	Test(const Test & t)
	{
		this->a = t.a;
		this->b = t.b;
		cout << "拷贝构造函数调用\n";
	}
};

ostream & operator<<(ostream & onfs, const Test & t)
{
	onfs << t.a << ":" << t.b << endl;
	return onfs;
}

int main()
{
	TinySTL::MySet<int> s;
	s.insert(1);
	s.insert(5);
	s.insert(2);
	for (auto it = s.begin(); it != s.end(); ++it)
		cout << *it << " ";
	cout<<":"<<s.size()<<endl;
	s.erase(2);
	for (auto it = s.begin(); it != s.end(); ++it)
		cout << *it << " ";
	cout << ":" << s.size() << endl;
	s.insert(-4);
	s.insert(4);
	s.insert(20);
	for (auto it = s.begin(); it != s.end(); ++it)
		cout << *it << " ";
	cout << ":" << s.size() << endl;
}