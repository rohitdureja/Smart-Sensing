#include "nodes.h"

#include <string>
#include <map>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

extern Server_Main Server;

using namespace std;

int main()
{
	/*struct sockaddr_in s1;
	string s2 = "192.168.1.24";
	string s3 = "192.168.1.10";
	string s4 = "192.168.1.2";
	string s5 = "192.168.1.4";

	Sensor S1(s1);
	Sensor S2(s2);
	Sensor S3(s3);

	Actuator A1(s4);
	Actuator A2(s5);

	Server.S_map[extract_key(s1)].add_act(extract_key(s4));
	Server.S_map[extract_key(s2)].add_act(extract_key(s4));
	Server.S_map[extract_key(s3)].add_act(extract_key(s5));
	Server.S_map[extract_key(s1)].add_N(extract_key(s3));
*/
	return 0;
}
