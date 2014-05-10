#include "threads.h"

using namespace std;

void threads::worker()
	{
		cout<<"In worker thread" << endl;
	}

void threads::sender()
	{
		cout << "In sender thread" << endl;
	}
	
void threads::receiver()
	{
		cout << "In receiver thread" << endl;
	}	

void threads::actuator_action()
	{
		cout << "actuator_action thread" << endl;
	}

void threads::person_detect()
	{
		cout << "person_detect thread" << endl;
	}
	