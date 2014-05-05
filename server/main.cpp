#include "nodes.h"
#include<map>
#include<string>

using namespace std;

int main()
{
	map<int, Sensor> sensor_map;
	map<int, Actuator> act_map;

	string s1 = "192.168.1.1";
	string s2 = "192.168.1.24";
	string s3 = "192.168.1.10";
	string s4 = "192.168.1.2";
	string s5 = "192.168.1.4";

	Sensor S1(s1,sensor_map);
	Sensor S2(s2, sensor_map);
	Sensor S3(s3, sensor_map);

	Actuator A1(s4, act_map);
	Actuator A2(s5, act_map);

	sensor_map[extract_key(s1)].add_act(extract_key(s4));
	sensor_map[extract_key(s2)].add_act(extract_key(s4));
	sensor_map[extract_key(s3)].add_act(extract_key(s5));
	sensor_map[extract_key(s1)].add_N(extract_key(s3));

	return 0;
}
