// Thread Basics

#include <thread>
#include <stdio>

class super_class
{
	int x;
	int y;
public:
	int a;
	int b;
	super_class(int x, int y, int a, int b)
	{
		x = x;
		y = y;
		a = a;
		b = b;
	}
	~super_class();
	
};


class sub_class : public super_class
{
	int x;
	int y;
public:
	int a;
	int b;
	sub_class(int x, int y, int a, int b)
	{
		x = x;
		y = y;
		a = a;
		b = b;
	}
	~sub_class();
	
};

int main(int argc, char const *argv[])
{
	
	super_class sup1 = new sup1(1,2,3,4);
	sub_class sub1 = new sub1(5,6,7,8);

	
}