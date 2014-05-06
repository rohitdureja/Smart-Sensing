// Thread Basics

#include "classes.h"

using namespace std;

super_class::super_class(int x, int y, int a, int b)
{
	x = x;
	y = y;
	a = a;
	b = b;
}

super_class::~super_class()
{
	
}

int super_class::call_me()
{
	return y;
}

/*
sub_class::sub_class(int x, int y, int a, int b)
{
	x = x;
	y = y;
	a = a;
	b = b;
}

*/
