#include "nodes.h"
#include "packet.h"


//global object to allow signal handling 
Server_Main Server;

//global function to get map key from address

int extract_key(struct sockaddr_in addr){

	char *ip = inet_ntoa(addr.sin_addr);
	int port = ntohs(addr.sin_port);
	
	char *k;
	k = strtok(ip,".");
	for(int i=0;i<3;++i)
		k = strtok(NULL,".");
	return (atoi(k)+port);
}

//Actuator constructor to initialize actuator and store in map at specific key
//Setting parameters of timer

Actuator::Actuator(struct sockaddr_in addr){
	
	address = addr;
	status = false;
	key = extract_key(address);

	//setting up the timer
	sigemptyset(&timeup.sa_mask);
	timeup.sa_handler = TimerHandler;
	// set up sigaction to catch signal
	if (sigaction(key, &timeup, NULL) == -1) {
		perror("sigaction failed");
		exit(EXIT_FAILURE);
	}

//making frame to put in send queue
	frame f(2,1,key,address);
	
//function in udp_server.cpp
	Server.th1.send_message(&f);	

//storing in Actuator map
	Server.A_map[key]=*this;
}

//setting actuator on with a specific timeout

void Actuator::set_status(int time_out){
	status = true;
	
//timer to reset actuator status in time_out seconds
	tid = SetTimer(time_out);

//making frame to put on send_queue
	frame f(2,5,time_out,address);
		Server.th1.send_message(&f);

//noting time at which event is done.
	event_time = time(NULL);
}

//reset actuator called by signal handler function attached to timer
void Actuator::reset(){
	status = false;
}

//getting status of actuator
bool Actuator::get_status(){
	return status;
}

//checking time left for the actuator to reset
double Actuator::get_time(){
	if (status)
		return (difftime(time(NULL), event_time));
	return 0;
}

//get address of the actuator
struct sockaddr_in Actuator::get_addr(){
	return address;
}

//timer handler function to be called by signal
void Actuator::TimerHandler(int signo){
	Server.A_map[signo].reset();
}

//setting timer with time_out in seconds
timer_t Actuator::SetTimer(int time_out){

	static struct sigevent sigev;
	static timer_t tid;
	static struct itimerspec itval;
	static struct itimerspec oitval;
	int signo = key;

// Create the POSIX timer to generate signo
	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = signo;
	sigev.sigev_value.sival_ptr = &tid;

	if (timer_create(CLOCK_REALTIME, &sigev, &tid) == 0) {
		itval.it_value.tv_sec = time_out;
		itval.it_value.tv_nsec = 0;
		itval.it_interval.tv_sec = 0;
		itval.it_interval.tv_nsec = 0;

		if (timer_settime(tid, 0, &itval, &oitval) != 0) {
			perror("time_settime error!");
		}
	}
	else {
		perror("timer_create error!");
		return NULL;
	}
	return tid;
}
//-------------------------------------------------------------------------

//Sensor constructor to initialize and store in map.
Sensor::Sensor(struct sockaddr_in addr){
	address = addr;
	key = extract_key(address);

	Server.S_map[key] = *this;

//making frame to put in send queue
	frame f(1,1,key,address);
	
//function in tcp_server.cpp
		Server.th1.send_message(&f);	
}

//function called to set actuator attached to self or the neighbours depending on the timeoutleft
void Sensor::set_self(){

	//if its actuator is already set by a neighbour node just increase the time_out to 5
	//else set the neighbours as this is the node through which intersection is entered

	if(Server.A_map[act_key].get_status()){
		if (Server.A_map[act_key].get_time()<=60)
			Server.A_map[act_key].set_status(300);
		else set_neighbours(60);
	}
	else set_neighbours(60);
}

//setting neighbour sensors' actuators at specific time_out
void Sensor::set_neighbours(int time_out){
	if (neighbour_keys.empty())
		return;
	list<int>::iterator i;
	for (i = neighbour_keys.begin(); i != neighbour_keys.end(); ++i){
		Server.A_map[Server.S_map[*i].get_act()].set_status(time_out);
	}
}

//getting key of the sensor object
int Sensor::get_key(){
	return key;
}

//getting key of the actuator near the sensor
int Sensor::get_act(){
	return act_key;
}

//getting address of the sensor object stored in the map
struct sockaddr_in Sensor::get_addr(){
	return address;
}

//add neighbour sensors' key to private neighbour list called only during localizing
void Sensor::add_neighbour(int n_key){
	neighbour_keys.push_back(n_key);
}

//adding actuator to sensor's members called only during localizing
void Sensor::add_act(int a_key){
	act_key = a_key;
}
//-----------------------------------------------------------------------------------------------------

//global object method functions

void Server_Main::set_localize(){

//iterators for maps	
	map<int,Sensor>::iterator i;
	map<int,Sensor>::iterator j;
	map<int,Actuator>::iterator k;

//message frame to be put in send_queue
	frame f;

	struct sockaddr_in addr_t;
	struct sockaddr_in addr_r;

	//iterating through sensor map setting one sensor in transmitting mode at a time
	for(i = S_map.begin();i!=S_map.end();++i)
	{
		//addr_t specifies sensor node to be in transmitter mode
		addr_t = i->get_addr();

		//sending message type 2 to sensor in transmitting mode
		//sending message type 3 to sensors in receiving mode
		for(j = S_map.begin();j!=S_map.end();++j)
		{
			//transmitter sensor should not receive self address and mode
			if(i->first!=j->first)
			{
				//making frame to be sent
				f.msg_set(1,2,j->first,addr_t);
				
				//send frame to send queue with addr_t as address
	Server.th1.send_message(&f);				

				//addr_r specifies sensor node in receiver mode message type 3
				addr_r = j->get_addr();
				
				//make frame to be sent 
				f.msg_set(1,3,i->first,addr_r);
				
				//send frame to send queue with addr_r as address
					Server.th1.send_message(&f);
				
			}
		}

		//sending message type 2 to sensor in transmitting mode
		//sending message type 3 to actuators in receiving mode
		for(k = A_map.begin();k!=A_map.end();++k)
		{
			f.msg_set(2,2,k->first,addr_t);
			
			//send frame to send queue with addr_t as address
				Server.th1.send_message(&f);
			
			//addr_r specifies actuator node in receiver mode
			addr_r = k->get_addr();
			f.msg_set(2,3,i->first,addr_r);
			
			//send frame to send queue with addr_t as address
				Server.th1.send_message(&f);
		}

		//waiting for transmission complete message from sensor in transmitting  mode
		Server.th1.receive_message(f);
		while(!(f.get_addr()==addr_t && f.get_mtype()==2)){
			Server.th1.receive_message(f);
		}			
	}

//asking clients to be start sending required neighbour keys after	localization
	for(i=S_map.begin();i!=S_map.end();++i){
		f.msg_set(1,4,0,i->get_addr());
		Server.th1.send_message(f);
	}

	for(k=A_map.begin();k!=A_map.end();++k){
		f.msg_set(1,4,0,k->get_addr());
		Server.th1.send_message(f);
	}
}

// start server service to sensor and actuator nodes
void Server_Main::start_service(){
	frame f;
	int mytype;
	int ntype;
	int payload;
	struct sockaddr_in address;
	while(true)
	{
		Server.th1.receive_message(f);
		mtype=f.get_mtype();
		ntype=f.get_ntype();
		payload=f.get_payload();
		address=f.get_addr();
		switch(mtype) {
			// 4: getting neighbor information from each node.
			case 4: if(ntype==1) //sensor
						S_map[extract_key(address)].add_neighbour(payload);
					if(ntype==2) //actuator
						S_map[payload].add_act(extract_key(address));
					break;
			//5: detect activity on sensors
			case 5:	if(ntype==1)
						S_map[extract_key(address)].set_self();
					break;
		}
	}
}

// called initially. disscovers all senesors and actuators on the sensor grid
void Server_Main::network_discovery() {
	frame f;
	int mytype;
	int ntype;
	int payload;
	struct sockaddr_in address;

	for(int i =0;i<MAX_NODES;++i)
	{
		Server.th1.receive_message(f);
		mtype=f.get_mtype();
		ntype=f.get_ntype();
		payload=f.get_payload();
		address=f.get_addr();
		switch(mtype) {
			case 1: if(ntype==1) //sensor
						Sensor (address);	
					if(ntype==2) //actuator
						Actuator (address);
					break;
		}
	}
}