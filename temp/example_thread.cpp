// Thread Basics
#include <thread>
#include <iostream>
#include "classes.h"

using namespace std;

int main(int argc, char const *argv[])
{
	super_class sup1(1,2,3,4);
	cout << "Printing values of super_class: " << sup1.call_me() << endl;// sup1.b << endl;
}