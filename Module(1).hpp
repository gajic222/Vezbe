#ifndef MODULE_H
#define MODULE_H

#include <systemc>
#include <deque>
enum states{passive,active,exploded};

SC_MODULE(Module)
{
public:
	static int NumOfExpl;
	SC_HAS_PROCESS(Module);
	Module(sc_core::sc_module_name name, states state, sc_core::sc_event *trigger);
	void life();
protected:
	sc_core::sc_event *trigger;
	states state;
	bool endme=false;
};

#endif
