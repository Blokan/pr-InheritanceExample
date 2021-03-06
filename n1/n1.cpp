#include "pch.h"
#include <iostream>
using namespace std;

//24

class B {
	int a;
public:
	B() { cout << "object of " << typeid(*this).name() << " was created\n"; }
	B(int x) :B() { a = x; }
	~B() { cout << "object of " << typeid(*this).name() << " was destroyed\n\n"; }
};

class D1 : virtual private B {
	int b;
public:
	D1(int x, int y) : B(y)
	{
		b = x;
		cout << "object of " << typeid(*this).name() << " was created\n";
	};
	~D1() { cout << "object of " << typeid(*this).name() << " was destroyed\n"; }
};

class D2 : virtual public B {
	int c;
public:
	D2(int x, int y) : B(y)
	{
		c = x;
		cout << "object of " << typeid(*this).name() << " was created\n";
	};
	~D2() { cout << "object of " << typeid(*this).name() << " was destroyed\n"; }
};

class D3 : protected D1 {
	int d;
public:

	D3(int x, int y, int z) : D1(y, z)
	{
		d = x;
		cout << "object of " << typeid(*this).name() << " was created\n";
	};
	~D3() { cout << "object of " << typeid(*this).name() << " was destroyed\n"; }
};

class D4 : virtual protected B, public D1, protected D2 {
	int e;
public:
	D4(int x, int u, int y, int z, int i, int j) : B(u), D1(y, z), D2(i, j)
	{
		e = x;
		cout << "object of " << typeid(*this).name() << " was created\n";
	};
	~D4() { cout << "object of " << typeid(*this).name() << " was destroyed\n"; }
};


int main()
{
	D3 temp0(100, 200, 300);
	cout << endl;
	D4 temp(1, 2, 3, 4, 5, 6);
}
