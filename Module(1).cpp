#include "Module.hpp"
#include <cstdlib>
#include <ctime>

using namespace sc_core;
using namespace std;

int Module::NumOfExpl = 0;

Module::Module(sc_core::sc_module_name name, states state, sc_core::sc_event *trigger):state(state),trigger(trigger)
{
	srand(time(NULL));
 	SC_THREAD(life);
}

void Module::life()
{
	while(!endme)
	{
		if(state==passive)
		{	
		//	cout<<"Waiting for trigger, -"<< name()<<" @"<<sc_core::sc_time_stamp() <<std::endl;
			wait(*trigger);
			int one_chance = rand()%100;
			if(one_chance==42)
				state=active;
		}
		else if(state==active)
		{
		//	cout<<"Waiting to explode,  -"<< name()<<" @"<<sc_core::sc_time_stamp() <<std::endl;
			int delay = rand()%9;
			wait(1+delay,sc_core::SC_NS);
			trigger->notify(sc_core::SC_ZERO_TIME);
			state=exploded;	
		}
		else
		{	
			std::cout<<"Goodbye cruel world, -"<< name()<<" @"<<sc_core::sc_time_stamp() <<std::endl;
			endme=true;
			NumOfExpl++;	
		}
	
	}	
}

