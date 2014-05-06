
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <queue>
#include "tcp_client.h"
#include "packet.h"

#define SENSOR 100
#define ACTUATOR 101

// thread to detect human activity
void person_detect_thread()
{
	char sensor_output;
	sensor_output = getchar();
	cout << "person detected" << endl;
}

// thread to handle command sent by server
void server_handler_thread()
{
		

}

// thread to send messages over tcp connection
void send_message_thread()
{
		
}

// thread to receive message over tcp connection
void receive_message_thread()
{

}

// thread to control actuator - turn on/off
void actuator_control_thread()
{
		
}


int main(int argc, char *argv[])
{
	if(argc<6)
	{
		cout << "not enough arguments!";
		cout << "correct usage: " << argv[0] << " <server_ip> <server_port> <mode> <group_id> <node_id>";
		exit(0);
	}

	// nodes next ot each other have the same group_id but different node_id.
	// the pair (group_id, node_id) uniquely identifies a node location
	// mode can be sensor or actuator
	int group_id = atoi(argv[4]);
	int node_id = atoi(argv[5]);
	int mode = atoi(argv[3]);

	// communication buffers
	queue<string> send_message_queue;
	mutex send_message_queue_mtx;
	queue<string> receive_message_queue;
	mutex receive_message_queue_mtx;

	// establish tcp connection to server
	tcp_client connection;
	//connection.connect_to_server(argv[1], atoi(argv[2]));

	thread server_handler(server_handler_thread);
	thread send_message(send_message_thread);
	thread receive_message(receive_message_thread);
	server_handler.join();
	send_message.join();
	receive_message.join();
	if(mode == SENSOR)
	{
		thread sensor(person_detect_thread);
		sensor.join();
	}
	else if(mode == ACTUATOR)
	{
		thread actuator_control(actuator_control_thread);
		actuator_control.join();
	}


/*
frame f;
char ch[256];
f.make(ch, 545, 66, 12);
cout << ch << endl;


int control;
int mode;
int payload;

f.parse(ch, &control, &mode, &payload);
cout << control << endl << mode << endl << payload << endl;*/
}
