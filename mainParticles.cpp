#include <systemc>
#include <string>
#include "Module.hpp"
using namespace std;


int sc_main(int argc, char* argv[])
{
        Module *particle[1000];	
        sc_core::sc_event trigger;
	particle[0]= new Module("particle_no_0", active, &trigger);
	for(int i=1;i<1000;i++)
	{
		string str("particle_no_");
		string num=to_string(i);
		str=str+num;

		particle[i]=new Module(str.c_str(), passive, &trigger);
	}

	sc_start(100, sc_core::SC_NS);
	delete particles[0];
	std::cout << "Simulation finished at " << sc_core::sc_time_stamp() << std::endl;
	std::cout << "Number of exploded particles is "<< Module::NumOfExpl<<std::endl;
	return 0;
}
