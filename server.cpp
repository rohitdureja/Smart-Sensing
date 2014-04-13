#include<iostream>
#include<string>
#include<utility>
#include<map>

using namespace std;

class node
{
public:
	int id;
	string ip;
/*
	size_t N_NB;
	node *NB;
	int actuator;
public:
	node(size_t n)
	{
		N_NB = n;
		NB = new node[N_NB];
	}*/
};

int main()
{
	map<int,node> T_nodes;
	int N;
	cout << "Enter the number of total nodes";
	cin >> N;
	for(int i = 0; i<N;++i){
		node NN;
		cout<<"\nenter the id: ";
		cin>>NN.id;
		cout<<"\nenter the ip: ";
		cin>>NN.ip;
		T_nodes[NN.id]=NN;
	}
	cout << "\nMap size: " << T_nodes.size() << endl;
   	map<int,node>::iterator ii;
	for(ii=T_nodes.begin(); ii!=T_nodes.end(); ++ii)
   	{
       		cout <<"\n"<< (*ii).first << ": " << (*ii).second.ip << endl;
   	}
	int idn;
	cout << "\nEnter the id to find: ";
	cin >> idn;
	ii=T_nodes.find(idn);
	if(ii!=T_nodes.end())
		cout <<"Node " << (*ii).first << "found with ip: "<< (*ii).second.ip;
	else cout<< "Node not found";	
	cin.get();
	return 0;
}
