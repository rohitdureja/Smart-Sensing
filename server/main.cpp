#include "nodes.h"
#include<map>
#include<string>

extern map<int,Sensor> S_map;
extern map<int,Actuator> A_map;

using namespace std;

int main()
{
	string s1 = "192.168.1.1";
	string s2 = "192.168.1.24";
	string s3 = "192.168.1.10";
	string s4 = "192.168.1.2";
	string s5 = "192.168.1.4";

	Sensor S1(s1);
	Sensor S2(s2);
	Sensor S3(s3);

	Actuator A1(s4);
	Actuator A2(s5);

	S_map[extract_key(s1)].add_act(extract_key(s4));
	S_map[extract_key(s2)].add_act(extract_key(s4));
	S_map[extract_key(s3)].add_act(extract_key(s5));
	S_map[extract_key(s1)].add_N(extract_key(s3));

	return 0;
}
